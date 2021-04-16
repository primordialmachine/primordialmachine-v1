/**
 * @author Michael Heilmann (<michaelheilmann@primordialmachine.com>)
 * @copyright Copyright (c) 2021 Michael Heilmann. All rights reservied.
 */
#include "Images.h"


#include <string.h>
#include <malloc.h>
#include <png.h>
#include "Machine.h"


static uint8_t getBytesPerPixel(Machine_Images_PixelFormat self) {
  switch (self) {
  case Machine_Images_PixelFormat_RGB:
    return 3;
  case Machine_Images_PixelFormat_RGBA:
    return 4;
  case Machine_Images_PixelFormat_BGR:
    return 3;
  case Machine_Images_PixelFormat_BGRA:
    return 4;
  case Machine_Images_PixelFormat_GRAYSCALE:
    return 1;
  default:
    Machine_setStatus(Machine_Status_InvalidArgument);
    Machine_jump();
  };
}

struct Machine_Images_Image {
  int width;
  int height;
  Machine_Images_PixelFormat pixelFormat;
  void* pixels;
};

int Machine_Images_Image_getSize(Machine_Images_Image* self, int* width, int* height) {
  *width = self->width;
  *height = self->height;
  return 0;
}

Machine_Images_PixelFormat Machine_Images_Image_getPixelFormat(Machine_Images_Image* self) {
  return self->pixelFormat;
}

void *Machine_Images_Image_getPixels(Machine_Images_Image* self) {
  return self->pixels;
}

static int referenceCount = 0;

int Machine_Images_startup() {
  if (referenceCount == INT_MAX) {
    return 1;
  }
  else if (referenceCount == 0) {
    /* ~ */
    referenceCount++;
    return 0;
  }
  else {
    referenceCount++;
    return 0;
  }
}

void Machine_Images_shutdown() {
  if (0 == --referenceCount) {
    /* ~ */
  }
}

void Machine_Images_Image_finalize(Machine_Images_Image* image) {
  if (image->pixels) {
    free(image->pixels);
    image->pixels = NULL;
  }
  Machine_Images_shutdown();
}

int Machine_Images_createImage(const char* path, Machine_Images_Image** image) {
  if (Machine_Images_startup()) {
    return 1;
  }

  int y, width, height;
  png_byte color_type;
  png_byte bit_depth;
  png_byte channels;

  png_structp png_ptr;
  png_infop info_ptr;
  int number_of_passes;
  png_bytep* row_pointers;
  char header[8];    // 8 is the maximum size that can be checked

  // Open file, check header
  FILE* fp = fopen(path, "rb");
  if (!fp) {
    Machine_Images_shutdown();
    fprintf(stderr, "[read_png_file] File %s could not be opened for reading", path);
    return 1;
  }
  fread(header, 1, 8, fp);
  if (png_sig_cmp(header, 0, 8)) {
    Machine_Images_shutdown();
    fprintf(stderr, "[read_png_file] File %s is not recognized as a PNG file", path);
    return 1;
  }

  //
  png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  if (!png_ptr) {
    Machine_Images_shutdown();
    fprintf(stderr, "[read_png_file] png_create_read_struct failed");
    return 1;
  }

  info_ptr = png_create_info_struct(png_ptr);
  if (!info_ptr) {
    Machine_Images_shutdown();
    fprintf(stderr, "[read_png_file] png_create_info_struct failed");
    return 1;
  }

  if (setjmp(png_jmpbuf(png_ptr))) {
    png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
    Machine_Images_shutdown();
    fprintf(stderr, "[read_png_file] Error during init_io");
    return 1;
  }

  png_init_io(png_ptr, fp);
  png_set_sig_bytes(png_ptr, 8);

  png_read_info(png_ptr, info_ptr);

  width = png_get_image_width(png_ptr, info_ptr);
  height = png_get_image_height(png_ptr, info_ptr);
  color_type = png_get_color_type(png_ptr, info_ptr);
  channels = png_get_channels(png_ptr, info_ptr);
  bit_depth = png_get_bit_depth(png_ptr, info_ptr);

  number_of_passes = png_set_interlace_handling(png_ptr);
  png_read_update_info(png_ptr, info_ptr);


  /* read file */
  if (setjmp(png_jmpbuf(png_ptr))) {
    Machine_Images_shutdown();
    fprintf(stderr, "[read_png_file] Error during read_image");
    return 1;
  }

  png_byte* pixels = malloc(png_get_rowbytes(png_ptr, info_ptr) * height);
  row_pointers = (png_bytep*)malloc(sizeof(png_bytep) * height);
  for (y = 0; y < height; y++)
    row_pointers[y] = pixels + y * png_get_rowbytes(png_ptr, info_ptr);

  png_read_image(png_ptr, row_pointers);

  fclose(fp);

  Machine_Images_Image* image1 = Machine_allocate(sizeof(Machine_Images_Image), NULL, (void (*)(void*)) & Machine_Images_Image_finalize);
  if (!image1) {
    free(row_pointers);
    Machine_Images_shutdown();
    png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
    return 1;
  }
  image1->width = width;
  image1->height = height;
  switch (color_type) {
  case PNG_COLOR_TYPE_RGBA:
    image1->pixelFormat = Machine_Images_PixelFormat_RGBA;
    break;
  case PNG_COLOR_TYPE_RGB:
    image1->pixelFormat = Machine_Images_PixelFormat_RGB;
    break;
  default:
    free(row_pointers);
    free(image1);
    image1 = NULL;
    Machine_Images_shutdown();
    png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
    fprintf(stderr, "[read_png_file] Unsupported png color type (%d) for image file %s\n", (int)color_type, path);
    return 1;
  };
  image1->pixels = pixels;
  png_destroy_read_struct(&png_ptr, &info_ptr, NULL);

  *image = image1;

  return 0;
}

int Machine_Images_createImageDirect(Machine_Images_PixelFormat pixelFormat, int width, int height, void* pixels, Machine_Images_Image** image) {
  if (Machine_Images_startup()) {
    return 1;
  }
  
  Machine_Images_Image* image1 = Machine_allocate(sizeof(Machine_Images_Image), NULL, (void (*)(void*)) & Machine_Images_Image_finalize);
  if (!image1) {
    Machine_Images_shutdown();
    return 1;
  }
  
  image1->width = width;
  image1->height = height;
  image1->pixelFormat = pixelFormat;
  image1->pixels = malloc(width * height * getBytesPerPixel(pixelFormat));
  if (!image1->pixels) {
    Machine_Images_shutdown();
    return 1;
  }
  memcpy(image1->pixels, pixels, width * height * getBytesPerPixel(pixelFormat));
  
  *image = image1;

  return 0;
}

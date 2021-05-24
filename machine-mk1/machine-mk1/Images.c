/**
 * @author Michael Heilmann (<michaelheilmann@primordialmachine.com>)
 * @copyright Copyright (c) 2021 Michael Heilmann. All rights reservied.
 */
#include "Images.h"


#include <string.h>
#include <malloc.h>
#include <png.h>


struct Machine_Images_Image {
  Machine_Object parent;
  int width;
  int height;
  Machine_PixelFormat pixelFormat;
  void* pixels;
};

int Machine_Images_Image_getSize(Machine_Images_Image* self, int* width, int* height) {
  *width = self->width;
  *height = self->height;
  return 0;
}

Machine_PixelFormat Machine_Images_Image_getPixelFormat(Machine_Images_Image* self) {
  return self->pixelFormat;
}

void* Machine_Images_Image_getPixels(Machine_Images_Image* self) {
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

Machine_Images_Image* Machine_Images_createImage(const char* path) {
  int status;

  status = Machine_Images_startup();
  if (status) {
    Machine_setStatus(status);
    Machine_jump();
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
    Machine_setStatus(Machine_Status_EnvironmentFailed);
    Machine_jump();
  }
  fread(header, 1, 8, fp);
  if (png_sig_cmp(header, 0, 8)) {
    Machine_Images_shutdown();
    fclose(fp);
    fp = NULL;
    fprintf(stderr, "[read_png_file] File %s is not recognized as a PNG file", path);
    Machine_setStatus(Machine_Status_EnvironmentFailed);
    Machine_jump();
  }

  //
  png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  if (!png_ptr) {
    fclose(fp);
    fp = NULL;
    Machine_Images_shutdown();
    fprintf(stderr, "[read_png_file] png_create_read_struct failed");
    Machine_setStatus(Machine_Status_EnvironmentFailed);
    Machine_jump();
  }

  info_ptr = png_create_info_struct(png_ptr);
  if (!info_ptr) {
    fclose(fp);
    fp = NULL;
    png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
    Machine_Images_shutdown();
    fprintf(stderr, "[read_png_file] png_create_info_struct failed");
    Machine_setStatus(Machine_Status_EnvironmentFailed);
    Machine_jump();
  }

  if (setjmp(png_jmpbuf(png_ptr))) {
    fclose(fp);
    fp = NULL;
    png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
    Machine_Images_shutdown();
    fprintf(stderr, "[read_png_file] Error during init_io");
    Machine_setStatus(Machine_Status_EnvironmentFailed);
    Machine_jump();
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
    fclose(fp);
    fp = NULL;
    png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
    Machine_Images_shutdown();
    fprintf(stderr, "[read_png_file] Error during read_image");
    Machine_setStatus(Machine_Status_EnvironmentFailed);
    Machine_jump();
  }

  png_byte* pixels = malloc(png_get_rowbytes(png_ptr, info_ptr) * height);
  if (!pixels) {
    fclose(fp);
    fp = NULL;
    png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
    Machine_Images_shutdown();
    Machine_setStatus(Machine_Status_EnvironmentFailed);
    Machine_jump();
  }
  row_pointers = (png_bytep*)malloc(sizeof(png_bytep) * height);
  if (!row_pointers) {
    free(pixels);
    fclose(fp);
    fp = NULL;
    png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
    Machine_Images_shutdown();
    Machine_setStatus(Machine_Status_EnvironmentFailed);
    Machine_jump();
  }
  for (y = 0; y < height; y++)
    row_pointers[y] = pixels + y * png_get_rowbytes(png_ptr, info_ptr);

  png_read_image(png_ptr, row_pointers);

  fclose(fp);
  fp = NULL;
  png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
  free(row_pointers);

  Machine_Images_Image* image1 = Machine_allocate(sizeof(Machine_Images_Image), NULL, (void (*)(void*)) & Machine_Images_Image_finalize);
  if (!image1) {
    Machine_Images_shutdown();
    Machine_setStatus(Machine_Status_EnvironmentFailed);
    Machine_jump();
  }
  image1->width = width;
  image1->height = height;
  switch (color_type) {
  case PNG_COLOR_TYPE_RGBA:
    image1->pixelFormat = Machine_PixelFormat_RGBA;
    break;
  case PNG_COLOR_TYPE_RGB:
    image1->pixelFormat = Machine_PixelFormat_RGB;
    break;
  default:
    free(pixels);
    free(image1);
    image1 = NULL;
    Machine_Images_shutdown();
    fprintf(stderr, "[read_png_file] Unsupported png color type (%d) for image file %s\n", (int)color_type, path);
    Machine_setStatus(Machine_Status_EnvironmentFailed);
    Machine_jump();
  };

  image1->pixels = pixels;

  return image1;
  }

Machine_Images_Image* Machine_Images_createImageDirect(Machine_PixelFormat pixelFormat, int width, int height, void* pixels) {
  int status;

  status = Machine_Images_startup();
  if (status) {
    Machine_setStatus(status);
    Machine_jump();
  }

  Machine_Images_Image* image1 = Machine_allocate(sizeof(Machine_Images_Image), NULL, (void (*)(void*)) & Machine_Images_Image_finalize);
  if (!image1) {
    Machine_Images_shutdown();
    Machine_setStatus(Machine_Status_AllocationFailed);
    Machine_jump();
  }

  image1->width = width;
  image1->height = height;
  image1->pixelFormat = pixelFormat;
  image1->pixels = malloc(width * height * Machine_PixelFormat_getBytesPerPixel(pixelFormat));
  if (!image1->pixels) {
    Machine_Images_shutdown();
    Machine_setStatus(Machine_Status_AllocationFailed);
    Machine_jump();
  }
  memcpy(image1->pixels, pixels, width * height * Machine_PixelFormat_getBytesPerPixel(pixelFormat));

  return image1;
}

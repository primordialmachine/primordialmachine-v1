/**
 * @author Michael Heilmann (<michaelheilmann@primordialmachine.com>)
 * @copyright Copyright (c) 2021 Michael Heilmann. All rights reservied.
 */
#include "Images.h"

#include <malloc.h>
#include <png.h>

static int referenceCount = 0;

int Machine_Images_startup() {
  if (referenceCount == INT_MAX) {
    return 1;
  } else if (referenceCount == 0) {
    /* ~ */
    referenceCount++;
    return 0;
  } else {
    referenceCount++;
    return 0;
  }
}

void Machine_Images_shutdown() {
  if (0 == --referenceCount) {
    /* ~ */
  }
}

int Machine_Images_load(const char* path) {
  int y, width, height;
  png_byte color_type;
  png_byte bit_depth;

  png_structp png_ptr;
  png_infop info_ptr;
  int number_of_passes;
  png_bytep* row_pointers;
  char header[8];    // 8 is the maximum size that can be checked

  /* open file and test for it being a png */
  FILE* fp = fopen(path, "rb");
  if (!fp) {
    fprintf(stderr, "[read_png_file] File %s could not be opened for reading", path);
    return 1;
  }
  fread(header, 1, 8, fp);
  if (png_sig_cmp(header, 0, 8)) {
    fprintf(stderr, "[read_png_file] File %s is not recognized as a PNG file", path);
    return 1;
  }

  /* initialize stuff */
  png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  if (!png_ptr) {
    fprintf(stderr, "[read_png_file] png_create_read_struct failed");
    return 1;
  }

  info_ptr = png_create_info_struct(png_ptr);
  if (!info_ptr) {
    fprintf(stderr, "[read_png_file] png_create_info_struct failed");
    return 1;
  }

  if (setjmp(png_jmpbuf(png_ptr))) {
    fprintf(stderr, "[read_png_file] Error during init_io");
    return 1;
  }

  png_init_io(png_ptr, fp);
  png_set_sig_bytes(png_ptr, 8);

  png_read_info(png_ptr, info_ptr);

  width = png_get_image_width(png_ptr, info_ptr);
  height = png_get_image_height(png_ptr, info_ptr);
  color_type = png_get_color_type(png_ptr, info_ptr);
  bit_depth = png_get_bit_depth(png_ptr, info_ptr);

  number_of_passes = png_set_interlace_handling(png_ptr);
  png_read_update_info(png_ptr, info_ptr);


  /* read file */
  if (setjmp(png_jmpbuf(png_ptr))) {
    fprintf(stderr, "[read_png_file] Error during read_image");
    return 1;
  }

  row_pointers = (png_bytep*)malloc(sizeof(png_bytep) * height);
  for (y = 0; y < height; y++)
    row_pointers[y] = (png_byte*)malloc(png_get_rowbytes(png_ptr, info_ptr));

  png_read_image(png_ptr, row_pointers);

  fclose(fp);

  return 0;
}

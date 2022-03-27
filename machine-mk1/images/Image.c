/// @file Image.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_IMAGES_PRIVATE (1)
#include "Image.h"

#include "Ring1/Status.h"
#include <png.h>
#include <string.h>

struct Machine_Images_Image_Class {
  Machine_Image_Class __parent;
};

struct Machine_Images_Image {
  Machine_Image __parent;

  int width;
  int height;
  Machine_PixelFormat pixelFormat;
  void* pixels;
};

static void getSize(Machine_Images_Image const* self, Machine_Integer* width,
                    Machine_Integer* height) {
  *width = self->width;
  *height = self->height;
}

static Machine_PixelFormat getPixelFormat(Machine_Images_Image const* self) {
  return self->pixelFormat;
}

static void const* getPixels(Machine_Images_Image const* self) {
  return self->pixels;
}

void Machine_Images_Image_destruct(Machine_Images_Image* self) {
  if (self->pixels) {
    Ring1_Memory_deallocate(self->pixels);
    self->pixels = NULL;
  }
}

void Machine_Images_Image_construct(Machine_Images_Image* self, size_t numberOfArguments,
                                    const Machine_Value* arguments) {
  if (numberOfArguments == 1) {
    Machine_String* path = Machine_Extensions_getStringArgument(numberOfArguments, arguments, 0);
    Machine_Images_Image_constructFromPath(self, path);
  } else if (numberOfArguments == 4) {
    Machine_Integer pixelFormat
        = Machine_Extensions_getIntegerArgument(numberOfArguments, arguments, 0);
    Machine_Integer width = Machine_Extensions_getIntegerArgument(numberOfArguments, arguments, 1);
    Machine_Integer height = Machine_Extensions_getIntegerArgument(numberOfArguments, arguments, 2);
    Machine_ByteBuffer* pixels = (Machine_ByteBuffer*)Machine_Extensions_getObjectArgument(
        numberOfArguments, arguments, 3, Machine_ByteBuffer_getType());
    Machine_Images_Image_constructDirect(self, (Machine_PixelFormat)pixelFormat, width, height,
                                         pixels);
  } else {
    Machine_setStatus(Machine_Status_InvalidNumberOfArguments);
    Machine_jump();
  }
}

static void constructClass(Machine_Images_Image_Class* self) {
  ((Machine_Image_Class*)self)->getPixelFormat
      = (Machine_PixelFormat(*)(Machine_Image const*)) & getPixelFormat;
  ((Machine_Image_Class*)self)->getPixels = (void const* (*)(Machine_Image const*)) & getPixels;
  ((Machine_Image_Class*)self)->getSize
      = (void (*)(Machine_Image const*, Machine_Integer*, Machine_Integer*)) & getSize;
}

MACHINE_DEFINE_CLASSTYPE(Machine_Images_Image, Machine_Image, NULL, &Machine_Images_Image_construct,
                         &Machine_Images_Image_destruct, &constructClass, NULL);

typedef struct _Io_State {
  char const* bytes;
  size_t numberOfBytes;
  size_t position;
} _Io_State;

static void _Io_read(png_structp pngPtr, png_bytep data, png_size_t length) {
  _Io_State* state = (_Io_State*)png_get_io_ptr(pngPtr);
  if (state->numberOfBytes < length) {
    png_error(pngPtr, "unable to read Bytes"); // Does not return.
  }
  Machine_Eal_Memory_copy(data, state->bytes + state->position, length, false);
  state->position += length;
}

void Machine_Images_Image_constructFromByteBuffer(Machine_Images_Image* self,
                                                  Machine_ByteBuffer* byteBuffer) {
  // (1) Supertype constructor.
  static const size_t NUMBER_OF_ARGUMENTS = 0;
  static const Machine_Value ARGUMENTS[] = { { Machine_ValueFlag_Void, Machine_Void_Void } };
  Machine_Image_construct((Machine_Image*)self, NUMBER_OF_ARGUMENTS, ARGUMENTS);

  // (3) Load image data.
  int y, width, height;
  png_byte color_type;
  png_byte bit_depth;
  png_byte channels;

  png_structp png_ptr;
  png_infop info_ptr;
  int number_of_passes;
  png_bytep* row_pointers;
  char header[8]; // 8 is the maximum size that can be checked

  // Open file, check header
  // Machine_ByteBufferReader* byteBufferReader = Machine_ByteBufferReader_create(byteBuffer);
  _Io_State state;
  state.position = 0;
  state.bytes = Machine_ByteBuffer_getBytes(byteBuffer);
  state.numberOfBytes = Machine_ByteBuffer_getNumberOfBytes(byteBuffer);

  // (1) read header.
  Machine_Eal_Memory_copy(&(header[0]), state.bytes, 8, false);
  state.position += 8;
  // (2) validate header.
  if (png_sig_cmp(header, 0, 8)) {
    Machine_log(Machine_LogFlags_ToErrors, __FILE__, __LINE__,
                "[read_png_file] file is not recognized as a PNG file\n");
    Machine_setStatus(Machine_Status_EnvironmentFailed);
    Machine_jump();
  }
  // (3) create read struct.
  png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  if (!png_ptr) {
    Machine_log(Machine_LogFlags_ToErrors, __FILE__, __LINE__,
                "[read_png_file] png_create_read_struct failed\n");
    Machine_setStatus(Machine_Status_EnvironmentFailed);
    Machine_jump();
  }
  // (4) create info struct.
  info_ptr = png_create_info_struct(png_ptr);
  if (!info_ptr) {
    png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
    Machine_log(Machine_LogFlags_ToErrors, __FILE__, __LINE__,
                "[read_png_file] png_create_info_struct failed");
    Machine_setStatus(Machine_Status_EnvironmentFailed);
    Machine_jump();
  }

  if (setjmp(png_jmpbuf(png_ptr))) {
    png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
    Machine_log(Machine_LogFlags_ToErrors, __FILE__, __LINE__,
                "[read_png_file] "
                "init_io/png_set_sig_bytes/png_read_info/png_set_interlaced_handling/"
                "png_read_update_info failed");
    Machine_setStatus(Machine_Status_EnvironmentFailed);
    Machine_jump();
  }
  png_set_read_fn(png_ptr, (png_voidp)&state, &_Io_read);
  png_set_sig_bytes(png_ptr, 8);

  png_read_info(png_ptr, info_ptr);

  width = png_get_image_width(png_ptr, info_ptr);
  height = png_get_image_height(png_ptr, info_ptr);
  color_type = png_get_color_type(png_ptr, info_ptr);
  channels = png_get_channels(png_ptr, info_ptr);
  bit_depth = png_get_bit_depth(png_ptr, info_ptr);

  number_of_passes = png_set_interlace_handling(png_ptr);
  png_read_update_info(png_ptr, info_ptr);

  // Read the file.
  if (setjmp(png_jmpbuf(png_ptr))) {
    // If we arrive here, then png_error was invoked.
    png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
    Machine_log(Machine_LogFlags_ToErrors, __FILE__, __LINE__,
                "[read_png_file] error during read_image");
    Machine_setStatus(Machine_Status_EnvironmentFailed);
    Machine_jump();
  }

  png_byte* pixels = NULL;
  if (Ring1_Memory_allocateArray(&pixels, png_get_rowbytes(png_ptr, info_ptr), height)) {
    Ring1_Status_set(Ring1_Status_Success);
    png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
    Machine_setStatus(Machine_Status_EnvironmentFailed);
    Machine_jump();
  }
  row_pointers = NULL;
  if (Ring1_Memory_allocateArray((void **) & row_pointers, sizeof(png_bytep), height)) {
    Ring1_Status_set(Ring1_Status_Success);
    Ring1_Memory_deallocate(pixels);
    png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
    Machine_setStatus(Machine_Status_EnvironmentFailed);
    Machine_jump();
  }
  for (y = 0; y < height; y++)
    row_pointers[y] = pixels + y * png_get_rowbytes(png_ptr, info_ptr);

  png_read_image(png_ptr, row_pointers);

  png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
  Ring1_Memory_deallocate(row_pointers);

  // (4) Store.
  self->width = width;
  self->height = height;
  switch (color_type) {
    case PNG_COLOR_TYPE_RGBA:
      self->pixelFormat = Machine_PixelFormat_RGBA;
      break;
    case PNG_COLOR_TYPE_RGB:
      self->pixelFormat = Machine_PixelFormat_RGB;
      break;
    default:
      Ring1_Memory_deallocate(pixels);
      Machine_log(Machine_LogFlags_ToErrors, __FILE__, __LINE__,
                  "[read_png_file] Unsupported png color type (%d) for image file\n",
                  (int)color_type);
      Machine_setStatus(Machine_Status_EnvironmentFailed);
      Machine_jump();
  };
  self->pixels = pixels;
  // (5) Set class type.
  Machine_setClassType((Machine_Object*)self, Machine_Images_Image_getType());
}

void Machine_Images_Image_constructFromPath(Machine_Images_Image* self, Machine_String* path) {
  Machine_ByteBuffer* byteBuffer = Machine_getFileContents(path);
  Machine_Images_Image_constructFromByteBuffer(self, byteBuffer);
}

void Machine_Images_Image_constructDirect(Machine_Images_Image* self,
                                          Machine_PixelFormat pixelFormat, Machine_Integer width,
                                          Machine_Integer height, Machine_ByteBuffer* pixels) {
  // (1) Supertype constructor.
  static const size_t NUMBER_OF_ARGUMENTS = 0;
  static const Machine_Value ARGUMENTS[] = { { Machine_ValueFlag_Void, Machine_Void_Void } };
  Machine_Image_construct((Machine_Image*)self, NUMBER_OF_ARGUMENTS, ARGUMENTS);

  // (3) Store.
  self->width = width;
  self->height = height;
  self->pixelFormat = pixelFormat;
  self->pixels = NULL;
  if (Ring1_Memory_allocateArray(&self->pixels, width * height,
                                 Machine_PixelFormat_getBytesPerPixel(pixelFormat))) {
    Ring1_Status_set(Ring1_Status_Success);
    Machine_setStatus(Machine_Status_AllocationFailed);
    Machine_jump();
  }
  Machine_Eal_Memory_copy(self->pixels, Machine_ByteBuffer_getBytes(pixels),
                          width * height * Machine_PixelFormat_getBytesPerPixel(pixelFormat), false);

  // (4) Set class type.
  Machine_setClassType((Machine_Object*)self, Machine_Images_Image_getType());
}

Machine_Images_Image* Machine_Images_Image_createImageFromPath(Machine_String* path) {
  Machine_ClassType* ty = Machine_Images_Image_getType();
  static const size_t NUMBER_OF_ARGUMENTS = 1;
  Machine_Value ARGUMENTS[1];
  Machine_Value_setString(&ARGUMENTS[0], path);
  Machine_Images_Image* self
      = (Machine_Images_Image*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  return self;
}

Machine_Images_Image* Machine_Images_Image_createImageDirect(Machine_PixelFormat pixelFormat,
                                                             Machine_Integer width,
                                                             Machine_Integer height,
                                                             Machine_ByteBuffer* pixels) {
  Machine_ClassType* ty = Machine_Images_Image_getType();
  static const size_t NUMBER_OF_ARGUMENTS = 4;
  Machine_Value ARGUMENTS[4];
  Machine_Value_setInteger(&ARGUMENTS[0], pixelFormat);
  Machine_Value_setInteger(&ARGUMENTS[1], width);
  Machine_Value_setInteger(&ARGUMENTS[2], height);
  Machine_Value_setObject(&ARGUMENTS[3], (Machine_Object*)pixels);
  Machine_Images_Image* self
      = (Machine_Images_Image*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  return self;
}

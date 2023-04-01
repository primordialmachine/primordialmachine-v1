/// @file Image.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_IMAGES_PRIVATE (1)
#include "Image.h"


#include "Ring1/All/_Include.h"
#include <png.h>


struct Machine_Images_Image_Class {
  Ring3_Image_Class __parent;
};

struct Machine_Images_Image {
  Ring3_Image __parent;

  int width;
  int height;
  Ring3_PixelFormat pixelFormat;
  void* pixels;
};

static void getSize(Machine_Images_Image const* self, Ring2_Integer* width,
                    Ring2_Integer* height) {
  *width = self->width;
  *height = self->height;
}

static Ring3_PixelFormat getPixelFormat(Machine_Images_Image const* self) {
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
                                    const Ring2_Value* arguments) {
  if (numberOfArguments == 1) {
    Ring2_String* path = Ring2_CallArguments_getStringArgument(numberOfArguments, arguments, 0);
    Machine_Images_Image_constructFromPath(self, path);
  } else if (numberOfArguments == 4) {
    Ring2_Integer pixelFormat = Ring2_CallArguments_getIntegerArgument(numberOfArguments, arguments, 0);
    Ring2_Integer width = Ring2_CallArguments_getIntegerArgument(numberOfArguments, arguments, 1);
    Ring2_Integer height = Ring2_CallArguments_getIntegerArgument(numberOfArguments, arguments, 2);
    Ring2_ByteBuffer* pixels = (Ring2_ByteBuffer*)Ring2_CallArguments_getObjectArgument(numberOfArguments,
                                                                                        arguments,
                                                                                        3,
                                                                                        Ring2_ByteBuffer_getType());
    Machine_Images_Image_constructDirect(self, (Ring3_PixelFormat)pixelFormat, width, height,
                                         pixels);
  } else {
    Ring1_Status_set(Ring1_Status_InvalidNumberOfArguments);
    Ring2_jump();
  }
}

static void constructClass(Machine_Images_Image_Class* self) {
  ((Ring3_Image_Class*)self)->getPixelFormat
      = (Ring3_PixelFormat(*)(Ring3_Image const*)) & getPixelFormat;
  ((Ring3_Image_Class*)self)->getPixels = (void const* (*)(Ring3_Image const*)) & getPixels;
  ((Ring3_Image_Class*)self)->getSize
      = (void (*)(Ring3_Image const*, Ring2_Integer*, Ring2_Integer*)) & getSize;
}

MACHINE_DEFINE_CLASSTYPE(Machine_Images_Image, Ring3_Image, NULL, &Machine_Images_Image_construct,
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
  Ring1_Memory_copyFast(data, state->bytes + state->position, length);
  state->position += length;
}

void
Machine_Images_Image_constructFromByteBuffer
  (
    Machine_Images_Image* self,
    Ring2_ByteBuffer* byteBuffer
  )
{
  // (1) Supertype constructor.
  static size_t const NUMBER_OF_ARGUMENTS = 0;
  static Ring2_Value const ARGUMENTS[] = { Ring2_Value_StaticInitializerVoid() };
  Ring3_Image_construct(Ring1_cast(Ring3_Image*,self), NUMBER_OF_ARGUMENTS, ARGUMENTS);

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
  state.bytes = Ring2_ByteBuffer_getBytes(byteBuffer);
  state.numberOfBytes = Ring2_ByteBuffer_getNumberOfBytes(byteBuffer);

  // (1) read header.
  Ring1_Memory_copyFast(&(header[0]), state.bytes, 8);
  state.position += 8;
  // (2) validate header.
  if (png_sig_cmp(header, 0, 8)) {
    Ring2_log(Ring2_LogFlags_ToErrors, __FILE__, __LINE__,
              "[read_png_file] file is not recognized as a PNG file\n");
    Ring1_Status_set(Ring1_Status_EnvironmentFailed);
    Ring2_jump();
  }
  // (3) create read struct.
  png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  if (!png_ptr) {
    Ring2_log(Ring2_LogFlags_ToErrors, __FILE__, __LINE__,
              "[read_png_file] png_create_read_struct failed\n");
    Ring1_Status_set(Ring1_Status_EnvironmentFailed);
    Ring2_jump();
  }
  // (4) create info struct.
  info_ptr = png_create_info_struct(png_ptr);
  if (!info_ptr) {
    png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
    Ring2_log(Ring2_LogFlags_ToErrors, __FILE__, __LINE__,
              "[read_png_file] png_create_info_struct failed");
    Ring1_Status_set(Ring1_Status_EnvironmentFailed);
    Ring2_jump();
  }

  if (setjmp(png_jmpbuf(png_ptr))) {
    png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
    Ring2_log(Ring2_LogFlags_ToErrors, __FILE__, __LINE__,
              "[read_png_file] "
              "init_io/png_set_sig_bytes/png_read_info/png_set_interlaced_handling/"
              "png_read_update_info failed");
    Ring1_Status_set(Ring1_Status_EnvironmentFailed);
    Ring2_jump();
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
    Ring2_log(Ring2_LogFlags_ToErrors, __FILE__, __LINE__,
              "[read_png_file] error during read_image");
    Ring1_Status_set(Ring1_Status_EnvironmentFailed);
    Ring2_jump();
  }

  png_byte* pixels = NULL;
  if (Ring1_Memory_allocateArray(&pixels, png_get_rowbytes(png_ptr, info_ptr), height)) {
    png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
    Ring2_jump();
  }
  row_pointers = NULL;
  if (Ring1_Memory_allocateArray((void **) & row_pointers, sizeof(png_bytep), height)) {
    Ring1_Memory_deallocate(pixels);
    png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
    Ring2_jump();
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
      self->pixelFormat = Ring3_PixelFormat_RGBA;
      break;
    case PNG_COLOR_TYPE_RGB:
      self->pixelFormat = Ring3_PixelFormat_RGB;
      break;
    default:
      Ring1_Memory_deallocate(pixels);
      Ring2_log(Ring2_LogFlags_ToErrors, __FILE__, __LINE__,
                "[read_png_file] Unsupported png color type (%d) for image file\n",
                (int)color_type);
      Ring1_Status_set(Ring1_Status_EnvironmentFailed);
      Ring2_jump();
  };
  self->pixels = pixels;
  // (5) Set class type.
  Machine_setClassType(Ring1_cast(Machine_Object *, self), Machine_Images_Image_getType());
}

void Machine_Images_Image_constructFromPath(Machine_Images_Image* self, Ring2_String* path) {
  Ring2_ByteBuffer* byteBuffer = Machine_getFileContentsAsByteBuffer(path);
  Machine_Images_Image_constructFromByteBuffer(self, byteBuffer);
}

void
Machine_Images_Image_constructDirect
  (
    Machine_Images_Image* self,
    Ring3_PixelFormat pixelFormat,
    Ring2_Integer width,
    Ring2_Integer height,
    Ring2_ByteBuffer* pixels
  )
{
  // (1) Supertype constructor.
  static size_t const NUMBER_OF_ARGUMENTS = 0;
  static Ring2_Value const ARGUMENTS[] = { Ring2_Value_StaticInitializerVoid() };
  Ring3_Image_construct(Ring1_cast(Ring3_Image*,self), NUMBER_OF_ARGUMENTS, ARGUMENTS);

  // (3) Store.
  self->width = width;
  self->height = height;
  self->pixelFormat = pixelFormat;
  self->pixels = NULL;
  if (Ring1_Memory_allocateArray(&self->pixels, width * height,
                                 Ring3_PixelFormat_getBytesPerPixel(pixelFormat))) {
    Ring2_jump();
  }
  Ring1_Memory_copyFast(self->pixels, Ring2_ByteBuffer_getBytes(pixels),
                        width * height * Ring3_PixelFormat_getBytesPerPixel(pixelFormat));

  // (4) Set class type.
  Machine_setClassType(Ring1_cast(Machine_Object *, self), Machine_Images_Image_getType());
}

Ring1_NoDiscardReturn() Machine_Images_Image*
Machine_Images_Image_createImageFromPath
  (
    Ring2_String* path
  )
{
  Machine_Type* ty = Machine_Images_Image_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 1;
  Ring2_Value arguments[1];
  Ring2_Value_setString(&arguments[0], path);
  Machine_Images_Image* self = Ring1_cast(Machine_Images_Image*,Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, arguments));
  return self;
}

Ring1_NoDiscardReturn() Machine_Images_Image*
Machine_Images_Image_createImageDirect
  (
    Ring3_PixelFormat pixelFormat,
    Ring2_Integer width,
    Ring2_Integer height,
    Ring2_ByteBuffer* pixels
  )
{
  Machine_Type* ty = Machine_Images_Image_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 4;
  Ring2_Value arguments[4];
  Ring2_Value_setInteger(&arguments[0], pixelFormat);
  Ring2_Value_setInteger(&arguments[1], width);
  Ring2_Value_setInteger(&arguments[2], height);
  Ring2_Value_setObject(&arguments[3], Ring1_cast(Machine_Object*,pixels));
  Machine_Images_Image* self = Ring1_cast(Machine_Images_Image*,Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, arguments));
  return self;
}

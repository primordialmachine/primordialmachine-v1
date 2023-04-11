#define RING3_IMAGESTRANSCODERS_LIBPNG_PRIVATE (1)
#include "Ring3/ImagesTranscoders/LibPng/ImagesDecoder.h"
#undef RING3_IMAGESTRANSCODERS_LIBPNG_PRIVATE

#include <png.h> // Include directive for the LibPng header.


static void
constructClass
  (
    Ring3_ImagesTranscoders_LibPng_ImagesDecoder_Class* self
  );

typedef struct _Io_State {
  char const* bytes;
  size_t numberOfBytes;
  size_t position;
} _Io_State;

static void
_Io_read
  (
    png_structp pngPtr,
    png_bytep data,
    png_size_t length
  )
{
  _Io_State* state = (_Io_State*)png_get_io_ptr(pngPtr);
  if (state->numberOfBytes < length) {
    png_error(pngPtr, "unable to read Bytes"); // Does not return.
  }
  Ring1_Memory_copyFast(data, state->bytes + state->position, length);
  state->position += length;
}

static void
decodeImpl
  (
    Ring3_ImagesTranscoders_LibPng_ImagesDecoder* self,
    char const *sourceBytes,
    int64_t numberOfSourceBytes,
    void** targetBytes,
    int64_t *numberOfTargetBytes,
    Ring3_PixelFormat* targetPixelFormat,
    int* targetWidth,
    int* targetHeight
  )
{
  int y, width, height;
  png_byte color_type;
  png_byte bit_depth;
  png_byte channels;

  png_structp png_ptr;
  png_infop info_ptr;
  int number_of_passes;
  png_bytep* row_pointers;
  char header[8]; // 8 is the maximum size that can be checked
  
  _Io_State state;
  state.position = 0;
  state.bytes = sourceBytes;
  state.numberOfBytes = numberOfSourceBytes;

  // Read header.
  Ring1_Memory_copyFast(&(header[0]), state.bytes, 8);
  state.position += 8;
  // Validate header.
  if (png_sig_cmp(header, 0, 8)) {
    Ring2_log(Ring2_LogFlags_ToErrors, __FILE__, __LINE__,
              "[read_png_file] file is not recognized as a PNG file\n");
    Ring1_Status_set(Ring1_Status_EnvironmentFailed);
    Ring2_jump();
  }
  // Create read struct.
  png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  if (!png_ptr) {
    Ring2_log(Ring2_LogFlags_ToErrors, __FILE__, __LINE__,
              "[read_png_file] png_create_read_struct failed\n");
    Ring1_Status_set(Ring1_Status_EnvironmentFailed);
    Ring2_jump();
  }
  // Create info struct.
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
  size_t numberOfBytes = png_get_rowbytes(png_ptr, info_ptr) * height;
  if (Ring1_Memory_allocate(&pixels, numberOfBytes)) {
    png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
    Ring2_jump();
  }
  row_pointers = NULL;
  if (Ring1_Memory_allocateArray((void**)&row_pointers, sizeof(png_bytep), height)) {
    Ring1_Memory_deallocate(pixels);
    png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
    Ring2_jump();
  }
  for (y = 0; y < height; y++)
    row_pointers[y] = pixels + y * png_get_rowbytes(png_ptr, info_ptr);

  png_read_image(png_ptr, row_pointers);

  png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
  Ring1_Memory_deallocate(row_pointers);

  // Store.
  *targetWidth = width;
  *targetHeight = height;
  switch (color_type) {
  case PNG_COLOR_TYPE_RGBA:
    *targetPixelFormat = Ring3_PixelFormat_RGBA;
    break;
  case PNG_COLOR_TYPE_RGB:
    *targetPixelFormat = Ring3_PixelFormat_RGB;
    break;
  default:
    Ring1_Memory_deallocate(pixels);
    Ring2_log(Ring2_LogFlags_ToErrors, __FILE__, __LINE__,
              "[read_png_file] Unsupported png color type (%d) for image file\n",
              (int)color_type);
    Ring1_Status_set(Ring1_Status_EnvironmentFailed);
    Ring2_jump();
  };
  *targetBytes = pixels;
  *numberOfTargetBytes = numberOfBytes;
}

struct Ring3_ImagesTranscoders_LibPng_ImagesDecoder_Class {
  Ring3_ImagesDecoder_Class parent;
};

struct Ring3_ImagesTranscoders_LibPng_ImagesDecoder {
  Ring3_ImagesDecoder parent;
};

static void
constructClass
  (
    Ring3_ImagesTranscoders_LibPng_ImagesDecoder_Class* self
  )
{
  Ring1_cast(Ring3_ImagesDecoder_Class*, self)->decode =
    (void (*)
      (
        Ring3_ImagesDecoder*,
        char const*,
        int64_t,
        void**,
        int64_t*,
        Ring3_PixelFormat*,
        int*,
        int*
      )
    )
    &decodeImpl;
}

MACHINE_DEFINE_CLASSTYPE(Ring3_ImagesTranscoders_LibPng_ImagesDecoder,
                         Ring3_ImagesDecoder,
                         NULL,
                         &Ring3_ImagesTranscoders_LibPng_ImagesDecoder_construct,
                         NULL,
                         &constructClass,
                         NULL);

void
Ring3_ImagesTranscoders_LibPng_ImagesDecoder_construct
  (
    Ring3_ImagesTranscoders_LibPng_ImagesDecoder* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  )
{
  Ring3_ImagesDecoder_construct(Ring1_cast(Ring3_ImagesDecoder*, self), numberOfArguments, arguments);
  Machine_setClassType(Ring1_cast(Machine_Object*, self), Ring3_ImagesTranscoders_LibPng_ImagesDecoder_getType());
}

Ring1_NoDiscardReturn() Ring3_ImagesTranscoders_LibPng_ImagesDecoder*
Ring3_ImagesTranscoders_LibPng_ImagesDecoder_create
  (
  )
{
  Machine_Type* ty = Ring3_ImagesTranscoders_LibPng_ImagesDecoder_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 0;
  static Ring2_Value const ARGUMENTS[] = { Ring2_Value_StaticInitializerVoid() };
  Ring3_ImagesTranscoders_LibPng_ImagesDecoder* self = Ring1_cast(Ring3_ImagesTranscoders_LibPng_ImagesDecoder*,
                                                                  Machine_allocateClassObject(ty,
                                                                                              NUMBER_OF_ARGUMENTS,
                                                                                              ARGUMENTS));
  return self;
}

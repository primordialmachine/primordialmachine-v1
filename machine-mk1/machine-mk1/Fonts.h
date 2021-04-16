#if !defined(MACHINE_FONTS_H_INCLUDED)
#define MACHINE_FONTS_H_INCLUDED

typedef struct Machine_Fonts_Font Machine_Fonts_Font;

/**
 * Increment the text module by @a 1.
 * FAILS if the reference count is INT_MAX.
 * @return @a 0 on success, a non-zero value on failure.
 */
int Machine_Fonts_startup();

/**
 * Decrement the text module by @a 1.
 * UNDEFINED if the reference count is @a 0.
 */
void Machine_Fonts_shutdown();

/**
 * @brief Load a font of the specified size.
 * @param path The path.
 * @param pointSize The point size.
 * @return A pointer to the font on success, null on failure.
 */
Machine_Fonts_Font* Machine_Fonts_createFont(const char* path, int pointSize);

void Machine_Fonts_Font_destroy(Machine_Fonts_Font* font);

#endif // MACHINE_FONTS_H_INCLUDED

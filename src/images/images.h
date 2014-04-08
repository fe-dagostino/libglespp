
#ifndef FI_UTILS_H
#define FI_UTILS_H

/**
 * Used to load an image using freeimage library.
 * returned buffer must be released with free() function.
 */
unsigned char* fi_load( const char* filename, unsigned int* size, int* width, int* height );

#endif //FI_UTILS_H


#ifndef UTIL_H
#define UTIL_H

#include <stddef.h>

/* Case-insensitive strcmp; returns <0, 0, >0 like strcmp */
int stricmp(const char *a, const char *b);

/* Trim trailing newline(s) in-place */
void trim_newline(char *s);

/* Trim spaces on both ends; returns pointer to first non-space.
   Also writes a '\0' at the new end for right-trim. */
char *trim_spaces(char *s);

/* Safe copy (always NUL-terminates) */
void safe_strcpy(char *dst, const char *src, size_t dst_cap);

#endif /* UTIL_H */

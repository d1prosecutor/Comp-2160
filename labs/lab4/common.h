#ifndef COMMON_H
#define COMMON_H

#include <stdlib.h>
#include <string.h>

#define MAX_LINE 80
#define MAX_FIELD 80
#define MAX_PROV 3

// Variables
extern const char CSV_SEPARATOR_STRING[];

// Functions
int count_lines(FILE *f);

#endif
#ifndef COMMON_H
#define COMMON_H

#define MAX_LINE 80
#define MAX_FIELD 80
#define MAX_PROV 3

extern const char CSV_SEPARATOR_STRING[];

int count_lines(FILE *f);

#endif /* COMMON_H */

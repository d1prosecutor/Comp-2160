#ifndef PROVINCE_H
#define PROVINCE_H

#include "common.h"

// Struct
typedef struct PROVINCE Province;

// Functions
Province *read_provinces(const char[], int *);

int find_prov(char[], Province *, int, char[]);

void sort_provinces_by_name(Province *, int);

// Getters
const char *getProv(Province *);
const char *getProvName(Province *);

#endif
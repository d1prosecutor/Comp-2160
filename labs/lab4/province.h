#ifndef PROVINCE_H
#define PROVINCE_H

#include "common.h"

// Struct
typedef struct PROVINCE
{
    char prov[MAX_PROV];
    char name[MAX_FIELD];
} Province;

// Functions
Province *read_provinces(const char[], int *);

int find_prov(char[], Province *, int, char[]);

void sort_provinces_by_name(Province *, int);

#endif
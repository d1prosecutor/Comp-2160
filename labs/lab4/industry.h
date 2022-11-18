#ifndef INDUSTRY_H
#define INDUSTRY_H

#include "common.h"

// Struct
typedef struct INDUSTRY
{
    int ind_code;
    char name[MAX_FIELD];
} Industry;

// Functions
Industry *read_industries(const char[], int *);

void sort_industries_by_name(Industry *array, int);

#endif
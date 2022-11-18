#ifndef INDUSTRY_H
#define INDUSTRY_H

#include "common.h"

// Struct
typedef struct INDUSTRY Industry;

// Functions
Industry *read_industries(const char[], int *);

void sort_industries_by_name(Industry *array, int);

// Getters
int getIndustryIndCode(Industry *);
const char *getIndName(Industry *);

#endif
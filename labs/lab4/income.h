#ifndef INCOME_H
#define INCOME_H

#include "common.h"

// Struct
typedef struct INCOME
{
    char prov[MAX_PROV];
    int year;
    int income;
    int ind_code;
} Income;

// Functions
Income *read_incomes(const char[], int *);

int find_year_range(Income *, int, int *, int *);

#endif
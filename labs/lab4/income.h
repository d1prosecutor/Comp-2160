#ifndef INCOME_H
#define INCOME_H

#include "common.h"

// Struct
typedef struct INCOME Income;

// Public Functions
Income *read_incomes(const char[], int *);

int find_year_range(Income *, int, int *, int *);

#endif
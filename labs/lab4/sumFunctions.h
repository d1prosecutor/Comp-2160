#ifndef SUMFUNCTIONS_H
#define SUMFUNCTIONS_H

#include "province.h"
#include "industry.h"
#include "income.h"

// Variable
extern const char COMMAND_SEPARATOR_STRING[];

// Functions
void sum_province_by_year(char[], Province *, int, Industry *, int, Income *, int);
void sum_ind_in_year_by_province(char[], int, Province *, int, Industry *, int, Income *, int);

#endif
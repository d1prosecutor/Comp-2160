#ifndef TEST_H
#define TEST_H

#include "common.h"
#include "income.h"
#include "industry.h"
#include "province.h"

typedef struct INDUSTRY
{
    int ind_code;
    char name[MAX_FIELD];
} Industry;

typedef struct INCOME
{
    char prov[MAX_PROV];
    int year;
    int income;
    int ind_code;
} Income;

typedef struct PROVINCE
{
    char prov[MAX_PROV];
    char name[MAX_FIELD];
} Province;

#endif
#ifndef SUM_H
#define SUM_H

#include "provinces.h"
#include "industries.h"
#include "incomes.h"

void sum_province_by_year(char prov_name[], Province *provinces, int num_provinces, Industry *industries, int num_industries, Income *incomes, int num_incomes);
void sum_ind_in_year_by_province(char ind_name[], int year, Province *provinces, int num_provinces, Industry *industries, int num_industries, Income *incomes, int num_incomes);

#endif /* SUM_H */

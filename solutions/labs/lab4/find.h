#ifndef FIND_H
#define FIND_H

#include "provinces.h"
#include "industries.h"
#include "incomes.h"

void find(char prov_name[], int year, char ind_name[], Province *provinces, int num_provinces, Industry *industries, int num_industries, Income *incomes, int num_incomes);

#endif /* FIND_H */
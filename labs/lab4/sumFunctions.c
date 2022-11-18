#include <stdio.h>
#include <string.h>

#include "sumFunctions.h"
#include "incomeStruct.h"
#include "industryStruct.h"
#include "provinceStruct.h"

void sum_province_by_year(char prov_name[], Province *provinces, int num_provinces, Industry *industries, int num_industries, Income *incomes, int num_incomes)
{
    char prov[MAX_PROV];
    int min_year, max_year;
    int *sums_by_year;

    if (!find_prov(prov_name, provinces, num_provinces, prov))
    {
        fprintf(stderr, "Unable to find province %s\n", prov_name);
    }
    else
    {
        // we only need to do this once, but we don't have a good place to store
        // the results (yet)
        if (find_year_range(incomes, num_incomes, &min_year, &max_year))
        {

            // this isn't the only strategy... but it works
            sums_by_year = calloc(max_year - min_year + 1, sizeof(int));

            if (NULL == sums_by_year)
            {
                fprintf(stderr, "Unable to allocate array for results\n");
            }
            else
            {

                for (int i = 0; i < num_incomes; i++)
                {
                    if (strcmp(incomes[i].prov, prov) == 0)
                    {
                        sums_by_year[incomes[i].year - min_year] += incomes[i].income;
                    }
                }

                for (int year = min_year; year <= max_year; year++)
                {
                    printf(" -> %d $%d\n", year, sums_by_year[year - min_year]);
                }

                // avoid memory leaks
                free(sums_by_year);
            }
        }
    }
}

void sum_ind_in_year_by_province(char ind_name[], int year, Province *provinces, int num_provinces, Industry *industries, int num_industries, Income *incomes, int num_incomes)
{
    int sum = 0;
    int ind_name_len = strlen(ind_name);

    for (int i = 0; i < num_provinces; i++)
    {
        for (int j = 0; j < num_industries; j++)
        {
            if (strncmp(ind_name, industries[j].name, ind_name_len) == 0)
            {
                for (int k = 0; k < num_incomes; k++)
                {
                    if (incomes[k].ind_code == industries[j].ind_code && incomes[k].year == year && strcmp(provinces[i].prov, incomes[k].prov) == 0)
                    {
                        sum = sum + incomes[k].income;
                    }
                }
            }
        }
        printf(" -> %s %d: $%d\n", provinces[i].name, year, sum);
    }
}
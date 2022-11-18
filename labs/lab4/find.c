#include <stdio.h>
#include <string.h>

#include "find.h"
#include "industryStruct.h"
#include "incomeStruct.h"

void find(char prov_name[], int year, char ind_name[], Province *provinces, int num_provinces, Industry *industries, int num_industries, Income *incomes, int num_incomes)
{
    char prov[MAX_PROV];
    int ind_name_len = strlen(ind_name);

    if (!find_prov(prov_name, provinces, num_provinces, prov))
    {
        fprintf(stderr, "Unable to find province %s\n", prov_name);
    }
    else
    {
        for (int i = 0; i < num_industries; i++)
        {
            if (strncmp(ind_name, industries[i].name, ind_name_len) == 0)
            {
                for (int j = 0; j < num_incomes; j++)
                {
                    if (incomes[j].ind_code == industries[i].ind_code && incomes[j].year == year && strcmp(incomes[j].prov, prov) == 0)
                    {
                        printf(" -> %s $%d\n", industries[i].name, incomes[j].income);
                    }
                }
            }
        }
    }
}
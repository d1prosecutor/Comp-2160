#include "find.h"

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
            if (strncmp(ind_name, getIndName(industries[i]), ind_name_len) == 0)
            {
                for (int j = 0; j < num_incomes; j++)
                {
                    if (getIncomeIndCode(incomes[j]) == getIndustryIndCode(industries[i]) && getIncomeYear(incomes[j]) == year && strcmp(getIncomeProv(incomes[j]), prov) == 0)
                    {
                        printf(" -> %s $%d\n", getIndName(industries[i]), getIncome(incomes[j]));
                    }
                }
            }
        }
    }
}
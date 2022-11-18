#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "processCommands.h"

const char PROVINCES_FILE[] = "q1_province.txt";
const char INDUSTRIES_FILE[] = "q1_industry.txt";
const char INCOMES_FILE[] = "q1_income.txt";

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

int main()
{
  Province *provinces;
  Industry *industries;
  Income *incomes;

  int num_provinces, num_industries, num_incomes;

  provinces = read_provinces(PROVINCES_FILE, &num_provinces);
  industries = read_industries(INDUSTRIES_FILE, &num_industries);
  incomes = read_incomes(INCOMES_FILE, &num_incomes);
  // printf("%d %d %d\n", num_provinces, num_industries, num_incomes);

  sort_provinces_by_name(provinces, num_provinces);
  sort_industries_by_name(industries, num_industries);

  // if (NULL != provinces && NULL != industries && NULL != incomes)
  // {
  //   process_commands(provinces, num_provinces, industries, num_industries, incomes, num_incomes);
  // }

  for (int i = 0; i < num_provinces; i++)
  {
    printf("%s %s\n", provinces[i].prov, provinces[i].name);
  }
  for (int i = 0; i < num_industries; i++)
  {
    printf("%d %s\n", industries[i].ind_code, industries[i].name);
  }
  for (int i = 0; i < num_incomes; i++)
  {
    printf("%s %d %d %d\n", incomes[i].prov, incomes[i].year, incomes[i].income, incomes[i].ind_code);
  }

  //////////////////
  printf("\nEnd of Processing");

  return 0;
}

#include "income.h"

// Struct
struct INCOME
{
  char prov[MAX_PROV];
  int year;
  int income;
  int ind_code;
};

Income *read_incomes(const char filename[], int *num)
{
  FILE *f;
  Income *incomes, *income;
  char line[MAX_LINE];
  char *fgets_result, *token;

  *num = 0;
  incomes = NULL;

  f = fopen(filename, "r");
  if (NULL == f)
  {
    fprintf(stderr, "Error reading incomes from %s\n", filename);
  }
  else
  {
    *num = count_lines(f) - 1;
    incomes = calloc(*num, sizeof(Income));
    if (NULL == incomes)
    {
      fprintf(stderr, "Unable to allocate array for incomes\n");
      *num = 0;
    }
    else
    {
      fgets_result = fgets(line, MAX_LINE, f); // skip
      income = incomes;

      while (NULL != fgets_result)
      {
        if (NULL != (fgets_result = fgets(line, MAX_LINE, f)))
        {
          token = strtok(line, CSV_SEPARATOR_STRING);
          if (NULL != token)
          {
            strncpy(income->prov, token, MAX_PROV);
          }
          token = strtok(NULL, CSV_SEPARATOR_STRING);
          if (NULL != token)
          {
            income->year = atol(token);
          }
          token = strtok(NULL, CSV_SEPARATOR_STRING);
          if (NULL != token)
          {
            income->income = atol(token);
          }
          token = strtok(NULL, CSV_SEPARATOR_STRING);
          if (NULL != token)
          {
            income->ind_code = atol(token);
          }
          income++;
        }
      }
    }
  }

  fclose(f);

  return incomes;
}

int find_year_range(Income *incomes, int num_incomes, int *min, int *max)
{
  *min = -1;
  *max = -1;

  for (int i = 0; i < num_incomes; i++)
  {
    if (*min < 0)
    {
      *min = incomes[i].year;
      *max = incomes[i].year;
    }
    else
    {
      if (*min > incomes[i].year)
      {
        *min = incomes[i].year;
      }
      if (*max < incomes[i].year)
      {
        *max = incomes[i].year;
      }
    }
  }

  return *min > 0;
}

int getIncomeYear(Income *tempIncome)
{
  return tempIncome->year;
}

int getIncome(Income *tempIncome)
{
  return tempIncome->income;
}

int getIncomeIndCode(Income *tempIncome)
{
  return tempIncome->ind_code;
}

const char *getIncomeProv(Income *tempIncome)
{
  return tempIncome->prov;
}
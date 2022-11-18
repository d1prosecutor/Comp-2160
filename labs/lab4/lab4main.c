#include "lab4main.h"

static const char PROVINCES_FILE[] = "q1_province.txt";
static const char INDUSTRIES_FILE[] = "q1_industry.txt";
static const char INCOMES_FILE[] = "q1_income.txt";

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
    printf("%s %s\n", getProv(&provinces[i]), getProvName(&provinces[i]));
  }
  for (int i = 0; i < num_industries; i++)
  {
    printf("%d %s\n", getIndustryIndCode(&industries[i]), getIndName(&industries[i]));
  }
  for (int i = 0; i < num_incomes; i++)
  {
    printf("%s %d %d %d\n", getIncomeProv(&incomes[i]), getIncomeYear(&incomes[i]), getIncome(&incomes[i]), getIncomeIndCode(&incomes[i]));
  }

  //////////////////
  printf("\nEnd of Processing");

  return 0;
}

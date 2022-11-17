#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 80
#define MAX_FIELD 80
#define MAX_PROV 3

const char PROVINCES_FILE[] = "q1_province.txt";
const char INDUSTRIES_FILE[] = "q1_industry.txt";
const char INCOMES_FILE[] = "q1_income.txt";

const char CSV_SEPARATOR_STRING[] = ",\n";
const char COMMAND_SEPARATOR_STRING[] = " ";

typedef struct PROVINCE {
  char prov[MAX_PROV];
  char name[MAX_FIELD];
} Province;

typedef struct INDUSTRY {
  int ind_code;
  char name[MAX_FIELD];
} Industry;

typedef struct INCOME {
  char prov[MAX_PROV];
  int year;
  int income;
  int ind_code;
} Income;

int count_lines(FILE *f)
{
  char line[MAX_LINE];
  int count = 0;
  
  while (NULL != fgets(line, MAX_LINE, f)) {
    count++;
  }
  
  rewind(f);
  
  return count;
}

Province *read_provinces(const char filename[], int *num)
{
  FILE *f;
  Province *provinces, *province;
  char line[MAX_LINE];
  char *fgets_result, *token;
  
  *num = 0;
  provinces = NULL;
  
  f = fopen(filename, "r");
  if (NULL == f) {
    fprintf(stderr, "Error reading provinces from %s\n", filename);
  } else {
    *num = count_lines(f) - 1;
    provinces = calloc(*num, sizeof(Province));
    if (NULL == provinces) {
      fprintf(stderr, "Unable to allocate array for provinces\n");
      *num = 0;
    } else {
      fgets_result = fgets(line, MAX_LINE, f); // skip
      province = provinces;

      while (NULL != fgets_result) {
        if (NULL != (fgets_result = fgets(line, MAX_LINE, f))) {
          // if ('\n' == line[strlen(line)-1]) {
          //   line[strlen(line)-1] == '\0';
          // }
          token = strtok(line, CSV_SEPARATOR_STRING);
          if (NULL != token) {
            strncpy(province->name, token, MAX_FIELD);
          }
          token = strtok(NULL, CSV_SEPARATOR_STRING);
          if (NULL != token) {
            strncpy(province->prov, token, MAX_PROV);
          }
          province++;
        }
      }
    }
  }
  
  fclose(f);
  
  return provinces;
}

// this looks familiar; by the end of the course we will know how to eliminate this repetition!
Industry *read_industries(const char filename[], int *num)
{
  FILE *f;
  Industry *industries, *industry;
  char line[MAX_LINE];
  char *fgets_result, *token;
  
  *num = 0;
  industries = NULL;
  
  f = fopen(filename, "r");
  if (NULL == f) {
    fprintf(stderr, "Error reading industries from %s\n", filename);
  } else {
    *num = count_lines(f) - 1;
    industries = calloc(*num, sizeof(Industry));
    if (NULL == industries) {
      fprintf(stderr, "Unable to allocate array for industries\n");
      *num = 0;
    } else {
      fgets_result = fgets(line, MAX_LINE, f); // skip
      industry = industries;

      while (NULL != fgets_result) {
        if (NULL != (fgets_result = fgets(line, MAX_LINE, f))) {
          token = strtok(line, CSV_SEPARATOR_STRING);
          if (NULL != token) {
            industry->ind_code = atol(token);
          }
          token = strtok(NULL, CSV_SEPARATOR_STRING);
          if (NULL != token) {
            strncpy(industry->name, token, MAX_FIELD);
          }
          industry++;
        }
      }
    }
  }
  
  fclose(f);
  
  return industries;
}

// this looks familiar; by the end of the course we will know how to eliminate this repetition!
Income *read_incomes(const char filename[], int *num)
{
  FILE *f;
  Income *incomes, *income;
  char line[MAX_LINE];
  char *fgets_result, *token;
  
  *num = 0;
  incomes = NULL;
  
  f = fopen(filename, "r");
  if (NULL == f) {
    fprintf(stderr, "Error reading incomes from %s\n", filename);
  } else {
    *num = count_lines(f) - 1;
    incomes = calloc(*num, sizeof(Income));
    if (NULL == incomes) {
      fprintf(stderr, "Unable to allocate array for incomes\n");
      *num = 0;
    } else {
      fgets_result = fgets(line, MAX_LINE, f); // skip
      income = incomes;

      while (NULL != fgets_result) {
        if (NULL != (fgets_result = fgets(line, MAX_LINE, f))) {
          token = strtok(line, CSV_SEPARATOR_STRING);
          if (NULL != token) {
            strncpy(income->prov, token, MAX_PROV);
          }
          token = strtok(NULL, CSV_SEPARATOR_STRING);
          if (NULL != token) {
            income->year = atol(token);
          }
          token = strtok(NULL, CSV_SEPARATOR_STRING);
          if (NULL != token) {
            income->income = atol(token);
          }
          token = strtok(NULL, CSV_SEPARATOR_STRING);
          if (NULL != token) {
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

int find_prov(char prov_name[], Province *provinces, int num_provinces, char prov[]) {
  int found = 0;

  for (int i = 0; !found && i < num_provinces; i++) {
    if (strcmp(prov_name, provinces[i].name) == 0) {
      strncpy(prov, provinces[i].prov, MAX_PROV);
      found = 1;
    }
  }
  
  return found;
}

void find(char prov_name[], int year, char ind_name[], Province *provinces, int num_provinces, Industry *industries, int num_industries, Income *incomes, int num_incomes)
{
  char prov[MAX_PROV];
  int ind_name_len = strlen(ind_name);

  if (!find_prov(prov_name, provinces, num_provinces, prov)) {
    fprintf(stderr, "Unable to find province %s\n", prov_name);
  } else {
    for (int i = 0; i < num_industries; i++) {
      if (strncmp(ind_name, industries[i].name, ind_name_len) == 0) {
        for (int j = 0; j < num_incomes; j++) {
          if (incomes[j].ind_code == industries[i].ind_code && incomes[j].year == year && strcmp(incomes[j].prov, prov) == 0) {
            printf(" -> %s $%d\n", industries[i].name, incomes[j].income);
          }
        }
      }
    }
  }
}

// this only works for years AD!
int find_year_range(Income *incomes, int num_incomes, int *min, int *max)
{
  *min = -1;
  *max = -1;
  
  for (int i = 0; i < num_incomes; i++) {
    if (*min < 0) {
      *min = incomes[i].year;
      *max = incomes[i].year;
    } else {
      if (*min > incomes[i].year) {
        *min = incomes[i].year;
      }
      if (*max < incomes[i].year) {
        *max = incomes[i].year;
      }
    }
  }
  
  return *min > 0;
}

void sum_province_by_year(char prov_name[], Province *provinces, int num_provinces, Industry *industries, int num_industries, Income *incomes, int num_incomes)
{
  char prov[MAX_PROV];
  int min_year, max_year;
  int *sums_by_year;
  
  if (!find_prov(prov_name, provinces, num_provinces, prov)) {
    fprintf(stderr, "Unable to find province %s\n", prov_name);
  } else {
    // we only need to do this once, but we don't have a good place to store
    // the results (yet)
    if (find_year_range(incomes, num_incomes, &min_year, &max_year)) {
  
      // this isn't the only strategy... but it works
      sums_by_year = calloc(max_year - min_year + 1, sizeof(int));
  
      if (NULL == sums_by_year) {
        fprintf(stderr, "Unable to allocate array for results\n");
      } else {
      
        for (int i = 0; i < num_incomes; i++) {
          if (strcmp(incomes[i].prov, prov) == 0) {
            sums_by_year[incomes[i].year - min_year] += incomes[i].income;
          }
        }
        
        for (int year = min_year; year <= max_year; year++) {
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

  for (int i = 0; i < num_provinces; i++) {
    for (int j = 0; j < num_industries; j++) {
      if (strncmp(ind_name, industries[j].name, ind_name_len) == 0) {
        for (int k = 0; k < num_incomes; k++) {
          if (incomes[k].ind_code == industries[j].ind_code && incomes[k].year == year && strcmp(provinces[i].prov, incomes[k].prov) == 0) {
            sum = sum + incomes[k].income;
          }
        }
      }
    }
    printf(" -> %s %d: $%d\n", provinces[i].name, year, sum);
  }
}

void process_commands(Province *provinces, int num_provinces, Industry *industries, int num_industries, Income *incomes, int num_incomes)
{
  char line[MAX_LINE], field[MAX_LINE];
  char *token, *rest;
  int year;
  
  while (NULL != fgets(line, MAX_LINE, stdin)) {
    fprintf(stderr, "Command: %s", line);
    token = strtok(line, COMMAND_SEPARATOR_STRING);
    
    if (strcmp(token, "FIND") == 0) {
      token = strtok(NULL, CSV_SEPARATOR_STRING);
      strncpy(field, token, MAX_LINE);
      token = strtok(NULL, CSV_SEPARATOR_STRING);
      year = atoi(token);
      if (0 == year) {
        fprintf(stderr, "Invalid year: %s\n", token);
      } else {
        token = strtok(NULL, "\n"); // everything to end of line
        find(field, year, token, provinces, num_provinces, industries, num_industries, incomes, num_incomes);
      }
    } else if (strcmp(token, "SUM") == 0) {
      rest = strtok(NULL, "\n");
      token = strstr(rest, " BY ");
      if (NULL == token) {
        fprintf(stderr, "Invalid command\n");
      } else {
        token[0] = '\0'; // changing the first character of " BY " to '\0'
        if (strcmp(token+1, "BY Year") == 0) {
          sum_province_by_year(rest, provinces, num_provinces, industries, num_industries, incomes, num_incomes);
        } else if (strcmp(token+1, "BY Province") == 0) {
          token = strstr(rest, " IN ");
          if (NULL == token) {
            fprintf(stderr, "Invalid command\n");
          } else {
            token[0] = '\0'; // changing the first character of " IN " to '\0'
            year = atoi(token + 4);
            if (0 == year) {
              fprintf(stderr, "Invalid year: %s\n", token);
            } else {
              sum_ind_in_year_by_province(rest, year,  provinces, num_provinces, industries, num_industries, incomes, num_incomes);
            }
          }
        } else {
          fprintf(stderr, "Invalid command\n");
        }
      }
    } else {
      fprintf(stderr, "Invalid command\n");
    }
  }
}

int compare_industries_by_name(const void *a, const void *b)
{
  const Industry *ia = (Industry *)a;
  const Industry *ib = (Industry *)b;
  return strcmp(ia->name, ib->name);
}

void sort_industries_by_name(Industry *array, int n)
{
  qsort(array, n, sizeof(Industry), compare_industries_by_name);
}

int compare_provinces_by_name(const void *a, const void *b)
{
  const Province *pa = (Province *)a;
  const Province *pb = (Province *)b;
  return strcmp(pa->name, pb->name);
}

void sort_provinces_by_name(Province *array, int n)
{
  qsort(array, n, sizeof(Province), compare_provinces_by_name);
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
  
  if (NULL != provinces && NULL != industries && NULL != incomes) {
    process_commands(provinces, num_provinces, industries, num_industries, incomes, num_incomes);
  }
  
  // for (int i = 0; i < num_provinces; i++) {
  //   printf("%s %s\n", provinces[i].prov, provinces[i].name);
  // }
  // for (int i = 0; i < num_industries; i++) {
  //   printf("%d %s\n", industries[i].ind_code, industries[i].name);
  // }
  // for (int i = 0; i < num_incomes; i++) {
  //   printf("%s %d %d %d\n", incomes[i].prov, incomes[i].year, incomes[i].income, incomes[i].ind_code);
  // }
  
  return 0;
}

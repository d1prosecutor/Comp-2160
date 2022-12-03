#ifndef INCOMES_H
#define INCOMES_H

typedef struct INCOME Income;

Income *read_incomes(const char filename[], int *num);
int find_year_range(Income *incomes, int num_incomes, int *min, int *max);

#endif /* INCOMES_H */

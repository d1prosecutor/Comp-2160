#ifndef INDUSTRIES_H
#define INDUSTRIES_H

typedef struct INDUSTRY Industry;

Industry *read_industries(const char filename[], int *num);
void sort_industries_by_name(Industry *array, int n);

#endif /* INDUSTRIES_H */
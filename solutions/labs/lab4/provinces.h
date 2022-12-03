#ifndef PROVINCES_H
#define PROVINCES_H

typedef struct PROVINCE Province;

Province *read_provinces(const char filename[], int *num);
int find_prov(char prov_name[], Province *provinces, int num_provinces, char prov[]);
void sort_provinces_by_name(Province *array, int n);

#endif /* PROVINCES_H */
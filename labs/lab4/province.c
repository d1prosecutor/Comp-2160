#include <stdio.h>
#include <string.h>

#include "province.h"
#include "provinceStruct.h"

// private function
static int compare_provinces_by_name(const void *, const void *);

// Functions
Province *read_provinces(const char filename[], int *num)
{
    FILE *f;
    Province *provinces, *province;
    char line[MAX_LINE];
    char *fgets_result, *token;

    *num = 0;
    provinces = NULL;

    f = fopen(filename, "r");
    if (NULL == f)
    {
        fprintf(stderr, "Error reading provinces from %s\n", filename);
    }
    else
    {
        *num = count_lines(f) - 1;
        provinces = calloc(*num, sizeof(Province));
        if (NULL == provinces)
        {
            fprintf(stderr, "Unable to allocate array for provinces\n");
            *num = 0;
        }
        else
        {
            fgets_result = fgets(line, MAX_LINE, f); // skip
            province = provinces;

            while (NULL != fgets_result)
            {
                if (NULL != (fgets_result = fgets(line, MAX_LINE, f)))
                {
                    // if ('\n' == line[strlen(line)-1]) {
                    //   line[strlen(line)-1] == '\0';
                    // }
                    token = strtok(line, CSV_SEPARATOR_STRING);
                    if (NULL != token)
                    {
                        strncpy(province->name, token, MAX_FIELD);
                    }
                    token = strtok(NULL, CSV_SEPARATOR_STRING);
                    if (NULL != token)
                    {
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

int find_prov(char prov_name[], Province *provinces, int num_provinces, char prov[])
{
    int found = 0;

    for (int i = 0; !found && i < num_provinces; i++)
    {
        if (strcmp(prov_name, provinces[i].name) == 0)
        {
            strncpy(prov, provinces[i].prov, MAX_PROV);
            found = 1;
        }
    }

    return found;
}

void sort_provinces_by_name(Province *array, int n)
{
    qsort(array, n, sizeof(Province), compare_provinces_by_name);
}

static int compare_provinces_by_name(const void *a, const void *b)
{
    const Province *pa = (Province *)a;
    const Province *pb = (Province *)b;
    return strcmp(pa->name, pb->name);
}

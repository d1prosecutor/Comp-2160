#include "industry.h"

// Private Function
static int compare_industries_by_name(const void *, const void *);

Industry *read_industries(const char filename[], int *num)
{
    FILE *f;
    Industry *industries, *industry;
    char line[MAX_LINE];
    char *fgets_result, *token;

    *num = 0;
    industries = NULL;

    f = fopen(filename, "r");
    if (NULL == f)
    {
        fprintf(stderr, "Error reading industries from %s\n", filename);
    }
    else
    {
        *num = count_lines(f) - 1;
        industries = calloc(*num, sizeof(Industry));
        if (NULL == industries)
        {
            fprintf(stderr, "Unable to allocate array for industries\n");
            *num = 0;
        }
        else
        {
            fgets_result = fgets(line, MAX_LINE, f); // skip
            industry = industries;

            while (NULL != fgets_result)
            {
                if (NULL != (fgets_result = fgets(line, MAX_LINE, f)))
                {
                    token = strtok(line, CSV_SEPARATOR_STRING);
                    if (NULL != token)
                    {
                        industry->ind_code = atol(token);
                    }
                    token = strtok(NULL, CSV_SEPARATOR_STRING);
                    if (NULL != token)
                    {
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

void sort_industries_by_name(Industry *array, int n)
{
    qsort(array, n, sizeof(Industry), compare_industries_by_name);
}

static int compare_industries_by_name(const void *a, const void *b)
{
    const Industry *ia = (Industry *)a;
    const Industry *ib = (Industry *)b;
    return strcmp(ia->name, ib->name);
}
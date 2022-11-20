#include "common.h"

// Definition of the common variable
const char CSV_SEPARATOR_STRING[] = ",\n";

int count_lines(FILE *f)
{
    char line[MAX_LINE];
    int count = 0;

    while (NULL != fgets(line, MAX_LINE, f))
    {
        count++;
    }

    rewind(f);

    return count;
}

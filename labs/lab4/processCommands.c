#include "processCommands.h"

// variable definition
const char COMMAND_SEPARATOR_STRING[] = " ";

void process_commands(Province *provinces, int num_provinces, Industry *industries, int num_industries, Income *incomes, int num_incomes)
{
    char line[MAX_LINE], field[MAX_LINE];
    char *token, *rest;
    int year;

    while (NULL != fgets(line, MAX_LINE, stdin))
    {
        fprintf(stderr, "Command: %s", line);
        token = strtok(line, COMMAND_SEPARATOR_STRING);

        if (strcmp(token, "FIND") == 0)
        {
            token = strtok(NULL, CSV_SEPARATOR_STRING);
            strncpy(field, token, MAX_LINE);
            token = strtok(NULL, CSV_SEPARATOR_STRING);
            year = atoi(token);
            if (0 == year)
            {
                fprintf(stderr, "Invalid year: %s\n", token);
            }
            else
            {
                token = strtok(NULL, "\n"); // everything to end of line
                find(field, year, token, provinces, num_provinces, industries, num_industries, incomes, num_incomes);
            }
        }
        else if (strcmp(token, "SUM") == 0)
        {
            rest = strtok(NULL, "\n");
            token = strstr(rest, " BY ");
            if (NULL == token)
            {
                fprintf(stderr, "Invalid command\n");
            }
            else
            {
                token[0] = '\0'; // changing the first character of " BY " to '\0'
                if (strcmp(token + 1, "BY Year") == 0)
                {
                    sum_province_by_year(rest, provinces, num_provinces, industries, num_industries, incomes, num_incomes);
                }
                else if (strcmp(token + 1, "BY Province") == 0)
                {
                    token = strstr(rest, " IN ");
                    if (NULL == token)
                    {
                        fprintf(stderr, "Invalid command\n");
                    }
                    else
                    {
                        token[0] = '\0'; // changing the first character of " IN " to '\0'
                        year = atoi(token + 4);
                        if (0 == year)
                        {
                            fprintf(stderr, "Invalid year: %s\n", token);
                        }
                        else
                        {
                            sum_ind_in_year_by_province(rest, year, provinces, num_provinces, industries, num_industries, incomes, num_incomes);
                        }
                    }
                }
                else
                {
                    fprintf(stderr, "Invalid command\n");
                }
            }
        }
        else
        {
            fprintf(stderr, "Invalid command\n");
        }
    }
}
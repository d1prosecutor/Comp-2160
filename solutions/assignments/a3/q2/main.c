#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "mystring.h"


int main(void)
{
#define MAX_INPUT_SIZE 80
    char input[MAX_INPUT_SIZE];
    char delim[MAX_INPUT_SIZE];
    int expected_tokens = -1;

    printf("Enter the input string: ");
    fgets(input, MAX_INPUT_SIZE, stdin);
    printf("Enter the delimiter: ");
    fgets(delim, MAX_INPUT_SIZE, stdin);
    printf("Enter the expected number of tokens: ");
    scanf("%d", &expected_tokens);

    string *to_split = make_string(input);

    string **tokens = split(to_split, delim);

    printf("Here's the output:\n");
    for (int i = 0; i < expected_tokens; i++)
    {
        printf("%d\t%s\n", i, get_content(tokens[i]));
    }
    return 0;
}


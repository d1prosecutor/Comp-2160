
//-----------------------------------------
// NAME: Chukwunaza Chukwuocha
// STUDENT NUMBER: 07928676
// COURSE: COMP 2160, SECTION: A01
// INSTRUCTOR: Saulo dos Santos
// ASSIGNMENT: assignment 1, QUESTION: question 1
//
// REMARKS: This program reads string(written as singe words on multiple lines) as input from
// standard input and formats it into paragraphs (and blank lines where necessary)
//
//-----------------------------------------

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LINE_SIZE 50

int main(int argc, char* argv[])
{
    int position = 1;
    char inputLine[LINE_SIZE];

    // Reads standard input with a max size of LINE_SIZE and stores it in inputLine
    while (fgets(inputLine, LINE_SIZE, stdin) != NULL)
    {
        // replaces the \n charcter at the end of each line with a null terminator
        inputLine[strlen(inputLine) - 1] = '\0';

        // checks if the current line being read is a blank line and prints a blank line if true
        if (strcmp(inputLine, "") == 0)
        {
            if (position > 1)
            {
                printf("\n");
            }

            printf("\n");
            position = 1;
        }

        else
        {
            // checks if the max charcters for as line has been exceeded and goes to a new line if true
            if ((position + strlen(inputLine) - 1) > LINE_SIZE)
            {
                printf("\n");
                position = 1;
            }

            printf("%s", inputLine);

            position += strlen(inputLine);

            // prints a blank space (between words) if the max characters for a line has not been exceeded
            if (position <= LINE_SIZE)
            {
                printf(" ");
                position++;
            }
        }
    }

    printf("\nThe program completed normally\n");

    return 0;
}

/*****************************************************************************************
 * NAME: Chukwunaza Chukwuocha
 * STUDENT NUMBER: 7928676
 * COURSE: COMP 2160, SECTION: A01
 * INSTRUCTOR: Saulo dos Santos
 * ASSIGNMENT: Assignment 3, Question 1
 *
 * REMARKS: Implements Test-functions for the functions provided by the container interface
 ******************************************************************************************/

#include <stdio.h>
#include <string.h>
#include "container.h"

/***********************************************************************
 *  printContainer
 *
 *  PURPOSE: prints out the contents of the container using the iterator
 *
 *  OUTPUT PARAMETERS:
 *      testContainer: The Container whose contents should be printed
 ***********************************************************************/
void printContainer(Container *testContainer)
{
    if (NULL != testContainer)
    {
        char *firstWord = firstItem(testContainer);
        if (NULL != firstWord)
        {
            printf("Contents of My Container: \"%s\"", firstWord);

            char *nextString = nextItem(testContainer);
            while (NULL != nextString)
            {
                printf(", \"%s\"", nextString);
                nextString = nextItem(testContainer);
            }

            // reset the containers iterator to the beginning of the list after printing to avoid affecting test codes
            firstItem(testContainer);
        }
        else
        {
            printf("Container is empty\n");
        }
    }
    else
    {
        printf("Container is invalid (NULL)\n");
    }

    printf("\n\n");
}

int main()
{

    Container *validContainer = createContainer();

    insertItem(validContainer, "One");
    insertItem(validContainer, "Two");
    insertItem(validContainer, "Two");
    insertItem(validContainer, "Three");
    insertItem(validContainer, "Three");
    insertItem(validContainer, "Three");
    insertItem(validContainer, "Four");
    insertItem(validContainer, "Four");
    insertItem(validContainer, "Four");
    insertItem(validContainer, "Four");
    insertItem(validContainer, "ten");
    printContainer(validContainer);

    deletedup(validContainer);
    printContainer(validContainer);

    printf("\nEnd of Processing\n");
    return 0;
}
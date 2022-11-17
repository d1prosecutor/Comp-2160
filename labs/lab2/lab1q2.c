//-----------------------------------------
// NAME: Chukwunaza Chukwuocha
// STUDENT NUMBER: 07928676
// COURSE: COMP 2160, SECTION: A01
// INSTRUCTOR: Saulo dos Santos
// LAB: Lab1, Question 2
//
// REMARKS: merges a file by matching its data by the keys representing each data.
// Appends each element with the same key together.
//
//-----------------------------------------

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE 80
#define NUM_INDEX 100

int main()
{
  char data[NUM_INDEX][MAX_LINE];
  char input[MAX_LINE];
  // *** declare more variables as required
  int arrayLength;
  int arrayKey;

  // null terminate the array at the top to create empty strings
  for (int i = 0; i < NUM_INDEX; i++)
  {
    data[i][0] = '\0';
  }

  // *** perform the input and processing

  while (NULL != fgets(input, MAX_LINE, stdin))
  {
    input[strlen(input) - 1] = '\0';

    input[2] = '\0';

    sscanf(input, "%d", &arrayKey);

    arrayLength = strlen(data[arrayKey]);

    // if there is already some data in teh array, add a comma before appending other data
    if (arrayLength > 0)
    {
      data[arrayKey][arrayLength++] = ',';
      data[arrayKey][arrayLength] = '\0';
    }

    strncat(data[arrayKey], input + 3, MAX_LINE - arrayLength - 1);
  }

  // print out all the arrays that have a valid length(>0)
  for (int i = 0; i < NUM_INDEX; i++)
  {
    if (strlen(data[i]) > 0)
    {
      printf("%02d %s\n", i, data[i]);
    }
  }

  return 0;
}
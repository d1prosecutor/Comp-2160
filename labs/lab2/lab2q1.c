//-----------------------------------------
// NAME: Chukwunaza Chukwuocha
// STUDENT NUMBER: 07928676
// COURSE: COMP 2160, SECTION: A01
// INSTRUCTOR: Saulo dos Santos
// LAB: Lab1, Question 1
//
// REMARKS: Joins and merges two files which are alphabetically sorted, such that every data
// item that falls under one given category(Key), is sorted and grouped together
//
//-----------------------------------------

#include <stdio.h>
#include <string.h>

#define MAX_INPUT 80

char *split(char *str, char delim);

int main()
{
  FILE *input1, *input2;
  char filename[MAX_INPUT];
  // *** declare more variables as required

  // remember we are NOT checking errors as we should!
  printf("Please enter the first filename: ");
  fgets(filename, MAX_INPUT, stdin);
  filename[strlen(filename) - 1] = '\0';
  input1 = fopen(filename, "r");

  printf("Please enter the second filename: ");
  fgets(filename, MAX_INPUT, stdin);
  filename[strlen(filename) - 1] = '\0';
  input2 = fopen(filename, "r");

  if (NULL == input1 || NULL == input2)
  {
    fprintf(stderr, "Unable to open an input file.\n");
  }
  else
  {
    // *** join lines from the two files here

    // Tracks if either of the files has been completely read
    int file1Empty = 0;
    int file2Empty = 0;

    // Contains the Key tokens whenn the split function finishes operating on it
    char file1Key[MAX_INPUT];
    char file2Key[MAX_INPUT];

    // Contains the data tokens
    char *file1Data;
    char *file2Data;

    // Keeps track of current Key(first token) being worked on
    char currentKey[MAX_INPUT];
    currentKey[0] = '\0';

    //..........Input Variables for File 1
    // Populates input variables
    fgets(file1Key, MAX_INPUT, input1);
    file1Key[strlen(file1Key) - 1] = '\0';

    file1Data = split(file1Key, ' ');
    //...................................

    //..........Input variables for File 2
    fgets(file2Key, MAX_INPUT, input2);
    file2Key[strlen(file2Key) - 1] = '\0';

    file2Data = split(file2Key, ' ');
    //.................................

    while (!file1Empty || !file2Empty)
    {

      int keyCompare = strcmp(file1Key, file2Key);
      int dataCompare = strcmp(file1Data, file2Data);

      // If file1 is the correct file to read from
      if (!file1Empty && (file2Empty || ((keyCompare < 0) || (keyCompare == 0 && dataCompare < 0))))
      {
        // Add input1 to the
        if (strcmp(file1Key, currentKey) != 0)
        { // if the key in the new Line and the currect key being worked on are not equal
          // add newline character + file1key + file1data

          printf("\n%s %s", file1Key, file1Data); // print to output file

          strcpy(currentKey, file1Key); // Copy the new prefix into the "currentPrefix" variable
        }
        else
        {
          // add ' '+data1
          printf(",%s", file1Data);
        }

        // get next inputStr1 String
        if (fgets(file1Key, MAX_INPUT, input1) == NULL)
        {
          file1Empty = 1;
        }
        else
        {
          file1Key[strlen(file1Key) - 1] = '\0';
          file1Data = split(file1Key, ' ');
          // update the loop for file 1 alone
        }
      }
      else // input2 is the correct one to draw from
      {
        // Add input1 to the output file
        if (strcmp(file2Key, currentKey) != 0)
        { // if not equal
          // add newline character + inputStr1 + data1
          printf("\n%s %s", file2Key, file2Data); // print to output file

          strcpy(currentKey, file2Key); // Copy the new prefix into the "currentPrefix" variable
        }
        else
        {
          // add ' '+data1
          printf(",%s", file2Data);
        }

        // get next inputStr1 String
        if (fgets(file2Key, MAX_INPUT, input2) == NULL)
        {
          file2Empty = 1;
        }
        else
        {
          file2Key[strlen(file2Key) - 1] = '\0';
          file2Data = split(file2Key, ' ');
        }
      }
    }

    fclose(input1);
    fclose(input2);
  }

  return 0;
}

// splits the string passed by the delimiter (by null terminating the string)and returns the contents
// after the delimiter
char *split(char *str, char delim)
{
  char *ptr = str;
  while (*ptr != delim)
  {
    ptr++;
  }
  *ptr = '\0';
  ptr++;

  return ptr;
}

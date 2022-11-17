#include <stdio.h>
#include <string.h>

#define MAX_INPUT 80

// this is a terrible function: we will learn why later!
// or, just use strtok()
int clean_and_make_space_pos(char str[])
{
  int pos = 0, npos;
  
  // no error checking! should be looking for \0 too
  while (' ' != str[pos]) {
    pos++;
  }
  
  str[pos] = '\0';

  npos = pos;
  while ('\n' != str[npos]) {
    npos++;
  }
  
  str[npos] = '\0';
  
  return pos;
}

int main()
{
  FILE *input1, *input2;
  char filename[MAX_INPUT];
  // *** declare more variables as required
  char line1[MAX_INPUT], line2[MAX_INPUT];
  char *result1, *result2;
  int space_pos1, space_pos2;
  char current_join[MAX_INPUT];
  int cmp, one_before_two;

  // remember we are NOT checking errors as we should!
  printf("Please enter the first filename: ");
  fgets(filename, MAX_INPUT, stdin);
  filename[strlen(filename)-1] = '\0';
  input1 = fopen(filename, "r");

  printf("Please enter the second filename: ");
  fgets(filename, MAX_INPUT, stdin);
  filename[strlen(filename)-1] = '\0';
  input2 = fopen(filename, "r");
  
  if (NULL == input1 || NULL == input2) {
    fprintf(stderr, "Unable to open an input file.\n");
  } else {
    // *** join lines from the two files here

    result1 = fgets(line1, MAX_INPUT, input1);
    result2 = fgets(line2, MAX_INPUT, input2);
    if (NULL != result1) {
      space_pos1 = clean_and_make_space_pos(line1);
    }
    if (NULL != result2) {
      space_pos2 = clean_and_make_space_pos(line2);
    }

    while (NULL != result1 || NULL != result2) {
      if (NULL == result1) {
        // nothing left in input 1: line2 first
        one_before_two = 0;
      } else if (NULL == result2) {
        // nothing left in input 2: line1 first
        one_before_two = 1;
      } else {
        cmp = strcmp(line1, line2);
        if (cmp < 0) {
          // line1 first
          one_before_two = 1;
        } else if (cmp > 0) {
          // line2 first
          one_before_two = 0;
        } else {
          // check the value after the common field
          if (strcmp(line1 + space_pos1 + 1, line2 + space_pos2 + 1) < 0) {
            one_before_two = 1;
          } else {
            one_before_two = 0;
          }
        }
      }

      if (one_before_two) {
        // line1 first
        if (0 != strcmp(current_join, line1)) {
          printf("%s ", line1);
          strcpy(current_join, line1);
        }
        printf("%s", line1 + space_pos1 + 1);
        result1 = fgets(line1, MAX_INPUT, input1);
        if (NULL == result1) {
          line1[0] = '\0';
        } else {
          space_pos1 = clean_and_make_space_pos(line1);
        }
      } else {
        // line2 first
        if (0 != strcmp(current_join, line2)) {
          printf("%s ", line2);
          strcpy(current_join, line2);
        }
        printf("%s", line2 + space_pos2 + 1);
        result2 = fgets(line2, MAX_INPUT, input2);
        if (NULL == result2) {
          line2[0] = '\0';
        } else {
          space_pos2 = clean_and_make_space_pos(line2);
        }
      }
      
      if (0 == strcmp(current_join, line1) || 0 == strcmp(current_join, line2)) {
        printf(",");
      } else {
        printf("\n");
      }
      fflush(stdout);
    }
    
    fclose(input2);
    fclose(input1);
  }
  
  return 0;
}
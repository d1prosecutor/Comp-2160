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
  
  int len, index;
  
  // fill the array with empty strings
  for (int i = 0; i < NUM_INDEX; i++) {
    data[i][0] = '\0';
  }
  
  // *** perform the input and processing
    
  while (NULL != fgets(input, MAX_LINE, stdin)) {
    input[strlen(input)-1] = '\0';
    
    input[2] = '\0';
    index = atoi(input);
    len = strlen(data[index]);
    if (len > 0) {
      data[index][len] = ',';
      len++;
      data[index][len] = '\0';
    }
    strncat(data[index], input+3, MAX_LINE-len-1);
  }
  
  for (int i = 0; i < NUM_INDEX; i++) {
    if (strlen(data[i]) > 0) {
      printf("%02d %s\n", i, data[i]);
    }
  }
  
  return 0;
}
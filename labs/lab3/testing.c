#include <stdio.h>
#include "binsearchB08.c"

void test_binary_search(int, int, int[], int);
void test_typical_cases();

static int tests_executed = 0;
static int tests_failed = 0;

void test_binary_search(int expected, int key, int array[], int count)
{
  int result = binsearch(key, array, count);

  if (result == expected)
  {
    printf("Passed: %d searching for '%d' in array length %d\n", result, key, count);
  }
  else
  {
    printf("FAILED: %d instead of %d searching for '%d' in array length %d\n", result, expected, key, count);
    tests_failed++;
  }

  tests_executed++;
}

void test_typical_cases()
{
  int array1[] = {1, 2, 3};
  int array2[] = {4, 5, 6, 7, 8, 9};
  int array3[] = {1, 5, 13, 53, 54, 55, 58};
  int array4[] = {-10, -5, 0, 1, 2, 3, 4, 7, 10, 12};

  printf("Testing typical cases\n");

  // test more stuff...
  test_binary_search(1, 2, array1, 3);
  test_binary_search(2, 6, array2, 6);
  test_binary_search(5, 55, array3, 7);
  test_binary_search(-1, -6, array4, 10);
}

void test_edge_cases()
{
  int array0[] = {};
  int array1[] = {4, 5, 6, 7, 8, 9};
  int array2[] = {1, 5, 13, 53, 54, 55, 58}; 
  int array3[] = {-10, -5, 0, 1, 2, 3, 4, 7, 10, 12};
  printf("Testing edge cases\n");

  test_binary_search(-1, 2, array0, 0);
  test_binary_search(0, 4, array1, 6);
  test_binary_search(6, 58, array2, 7);
  test_binary_search(0, -10, array3, 10);
}

void test_bad_cases()
{
  int array1[] = {9, 8, 7, 6, 5, 4, 3};
  int array2[] = {5, 1, 57, 31, 42, 68};
  printf("Testing bad cases\n");

  test_binary_search(5, 4, array1, 7);
  test_binary_search(5, 58, array2, 6);
}

int main()
{
  printf("Beginning tests\n\n");
  test_typical_cases();
  printf("\n");

  test_edge_cases();
  printf("\n");

  test_bad_cases();
  printf("\n");

  // test more stuff...

  printf("\nTotal number of tests executed: %d\n", tests_executed);
  printf("Number of tests passed:         %d\n", (tests_executed - tests_failed));
  printf("Number of tests failed:         %d\n", tests_failed);

  return 0;
}
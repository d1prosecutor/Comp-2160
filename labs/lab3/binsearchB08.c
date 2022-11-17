// Section B08
#include <assert.h>

int binsearch(int, int[], int);
void checkState(int[], int);

int binsearch(int value, int array[], int length)
{
  assert(length > 0);
  checkState(array, length);

  int start, end, mid, found;

  start = 0;
  end = length - 1;
  mid = 0;

  found = 0;

  int valuePos = -1;

  if (length > 0)
  {
    while (start <= end && found != 1)
    {
      assert(start <= end);

      mid = start + (end - start) / 2;

      if (value < array[mid])
        end = mid - 1;
      else if (value > array[mid])
        start = mid + 1;
      else
      {
        valuePos = mid;
        found = 1;
      }
    }
  }

  assert((found == 0 && valuePos == -1) || (found == 1 && (valuePos >= 0 && valuePos <= end)));
  checkState(array, length);

  return valuePos;
}

void checkState(int array[], int length)
{
  for (int i = 0; i < length - 1; i++)
  {
    assert(i < length);
    assert(array[i] < array[i + 1]);
  }
}

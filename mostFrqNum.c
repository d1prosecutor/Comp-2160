#include <stdio.h>
#include <stdlib.h>

typedef struct FREQUENCY
{
    int value;
    int count;
} Frequency;
const int MAX_UNIQUE_VALUES = 100000;

// typedef struct NODE
// {
//     char *item;
//     struct NODE *next;
// } Node, *Nodeptr;

void printMostFrequent(Frequency mostFrquent[], int size)
{ // if no input provided

    if (size == 0)
    {
        printf("No value is entered");
    }
    else
    { // Assume that first value is most frequent
        int mostIndex = 0;
        for (int index = 1; index < size - 1; index++)
        {
            if (mostFrquent[index].count > mostFrquent[mostIndex].count)
            {
                mostIndex = index;
            } // in case of tie, take the highest value
            else if (mostFrquent[index].count == mostFrquent[mostIndex].count && mostFrquent[index].value > mostFrquent[mostIndex].value)
            {
                mostIndex = index;
            }
        } // Print the most occurred number
        printf("Most frequest number: %d, count: %d", mostFrquent[mostIndex].value, mostFrquent[mostIndex].count);
    }
}

int main()
{
    // Declare array to store input
    Frequency mostFrquent[MAX_UNIQUE_VALUES]; // To hold how many unique characters entered
    int uniqueValueCount = 0;                 // Get user input until it finds end of line
    int input;
    scanf("%d", &input);
    while (input != -999)
    { // Verify if the number already exists in the array
        int newUnique = 1;
        for (int i = 1; i < MAX_UNIQUE_VALUES; i++)
        { // if found increment the count
            if (mostFrquent[i].value == input)
            {
                mostFrquent[i].count += 1;
                newUnique = 0;
            }
        } // if it is newUnique number add to array as new entry
        if (newUnique == 1)
        {
            mostFrquent[uniqueValueCount].value = input;
            mostFrquent[uniqueValueCount].count = 1;
            uniqueValueCount += 1;
        }
        scanf("%d", &input);
    } // Call the method
    printMostFrequent(mostFrquent, uniqueValueCount);
    return 0;
}
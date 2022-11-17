//-----------------------------------------
// NAME: Chukwunaza Chukwuocha
// STUDENT NUMBER: 07928676
// COURSE: COMP 2160, SECTION: A01
// INSTRUCTOR: Saulo dos Santos
// ASSIGNMENT: assignment 1, QUESTION: question 2
//
// REMARKS: Compares two strings and checks if the distance between the strings(essentially the difference between the
// two strings - in letters) is equal to the expected number passed in by the user.
//
//-----------------------------------------

#include <stdio.h>
#include <string.h>
#include <assert.h>

// Explicit declaration of all my functions
void testDistance(char s[], char t[], int expected);
int levenshtein(char s[], char t[]);
int minimum(int minimum[], int sizeOfMinimum);
void subString(char str[], char tempStr[], int n);
int endsWith(char str[], char substr[], int subStringIndex);

// Variable declarations
int testsFailed = 0;
int testsExecuted = 0;

int main(int argc, char *argv[])
{
    printf("Testing typical cases.\n\n");
    testDistance("kitten", "kitten", 0);
    testDistance("kitten", "sitting", 3);
    testDistance("kitten", "mittens", 2);
    testDistance("balloon", "saloon", 2);
    testDistance("hello", "doggo", 4);
    testDistance("\t\thi", "\t\t\t\thi", 2);

    printf("\nTesting empty/edge cases.\n\n");
    testDistance("", "", 0);
    testDistance("hello", "", 5);
    testDistance("", "doggo", 5);
    testDistance("a", "b", 1);
    testDistance("b", "b", 0);
    testDistance(" ", " ", 0);

    printf("\nThis might take a while...\n\n");
    testDistance("12345678901", "123456789012", 1); // how many chars are we looking at?

    printf("\n******These tests will be opposite in the C version******\n\n");
    printf("\n******These tests **should** FAIL in the C version*******\n\n");
    testDistance("kitten", "mitten\0s", 3); // ????
    testDistance("\0totally", "\0different", 9);

    printf("\nTotal number of tests executed: %d\n", testsExecuted);
    printf("Number of tests passed: %d\n", (testsExecuted - testsFailed));
    printf("Number of tests failed: %d\n", testsFailed);

    printf("\nThe program completed normally\n");

    return 0;
}

//------------------------------------------------------
// testDistance
//
// PURPOSE: Claculates the difference(in number of characters) between two strings (using levenshtein()), compares
// this distance with the expected distance passed in by the user and prints if they are the same or not
// INPUT PARAMETERS:
// chars s[]: The first string passed by the user
// char t[]: The second string passed by the user
// int expected: The value which the user expects the distance between s and t to be
//------------------------------------------------------
void testDistance(char s[], char t[], int expected)
{
    int distance = levenshtein(s, t);

    if (distance == expected)
    {
        printf("Passed! You can get from '%s' to '%s' in %d moves.\n", s, t, expected);
    }
    else
    {
        printf("FAILED: I thought it would take %d moves, but apparently it takes %d "
               "moves to get from '%s' to '%s'.\n",
               expected,
               distance, s, t);

        testsFailed++;
    }

    testsExecuted++;
}

//------------------------------------------------------
// levenshtein
//
// PURPOSE: Uses recursion to calculate the difference in characters between two strings
// INPUT PARAMETERS:
// char s[]: The first string to be compared
// char t[]: The second string to be compared
// OUTPUT PARAMETERS:
// distance: The calculated difference in charactes between the two strings as an int value.
//------------------------------------------------------
int levenshtein(char s[], char t[])
{
    int cost = 0;
    int distance = 0;

    int sLength = strlen(s);
    int tLength = strlen(t);

    // creating new char arrays with the same space in memory as s and t
    char deleteS[sLength + 1];
    char deleteT[tLength + 1];

    // terminating the newly created char array
    deleteS[sLength] = '\0';
    deleteT[tLength] = '\0';

    if (sLength == 0)
    {
        distance = tLength;
    }
    else if (tLength == 0)
    {
        distance = sLength;
    }
    else
    {
        if (s[0] == t[0])
        {
            cost = 0;
        }
        else
        {
            cost = 1;
        }

        // Variable to show the starting index of the substring
        int subStringStart = 1;

        // instead of creating a subString function, you could just create a pointer to point to another index
        // in the original string array(since that array is not being modified in any way)
        //  char *deleteS = &s[subStringStart];
        //  char *deleteT = &t[subStringStart];

        // perform the substring function and modify deleteS and deleteT in place
        subString(s, deleteS, subStringStart);
        subString(t, deleteT, subStringStart);

        assert(strlen(deleteS) == (strlen(s) - 1));
        assert(strlen(deleteT) == (strlen(t) - 1));

        assert(endsWith(s, deleteS, subStringStart));
        assert(endsWith(t, deleteT, subStringStart));

        int tempIntArr[] = {(int)levenshtein(deleteS, t) + 1, (int)levenshtein(s, deleteT) + 1, (int)levenshtein(deleteS, deleteT) + cost};
        int sizeOftempArr = (sizeof(tempIntArr) / sizeof(tempIntArr[0]));

        distance = minimum(tempIntArr, sizeOftempArr);
    }

    return distance;
}

//------------------------------------------------------
// minimum
//
// PURPOSE: Finds the minimum value in an array of Integers
// INPUT PARAMETERS:
// int minimum[]: The array to be searched
// sizeOfMinimum: The size of the arra(minimum[]) to be searched
// OUTPUT PARAMETERS:
// min: The smallest integer found in the searched array(minimum[])
//------------------------------------------------------
int minimum(int minimum[], int sizeOfMinimum)
{
    int min = 0;

    assert(sizeOfMinimum > 0);

    if (sizeOfMinimum > 0)
    {
        min = minimum[0];

        for (int i = 1; i < sizeOfMinimum; i++)
        {
            if (minimum[i] < min)
            {
                min = minimum[i];
            }
        }
    }

    return min;
}

//------------------------------------------------------
// subString
//
// PURPOSE: Creates a substring from another string passed by the user from an index(also passed by the user)
// INPUT PARAMETERS:
// char str[]: The Original string
// char tempStr[]: The string variable which holds the extracted substring
// int startIndex:  The index where the extraction of the substring should start
//------------------------------------------------------
void subString(char str[], char tempStr[], int startIndex)
{
    // extracts characters between 0 and n'th index from source string
    // and copy them into the destination string
    int i = 0;

    if (startIndex <= strlen(str))
    {
        while (str[(i + startIndex)] != '\0' && (i + startIndex) < strlen(str))
        {
            tempStr[i] = str[(i + startIndex)];
            i++;
        }
    }

    // null-terminate the extracted substring
    tempStr[i] = '\0';
}

//------------------------------------------------------
// endsWith
//
// PURPOSE: Checks if a string(passed by the user) ends with another string(also passed by the user) from a
// specified index
// INPUT PARAMETERS:
// str[]: The bigger string variable (which is meant to contain the substring)
// substr[]: The (smaller) string variable which is to be looked for inside  the bigger str[] variable
// subStringIndex: The index to start comparing the str[] and subStr[] variables from
// OUTPUT PARAMETERS:
// boolValue: mimics the boolean type. Returns 1 if str ends with subStr and 0 otherwise
//------------------------------------------------------
int endsWith(char str[], char subStr[], int subStringIndex)
{
    int boolValue = 0;

    if (strlen(subStr) <= strlen(str))
    {
        int i = 0;
        boolValue = 1;

        while (i < strlen(subStr) && boolValue == 1)
        {
            if (str[i + subStringIndex] != subStr[i])
            {
                boolValue = 0;
            }

            i++;
        }
    }

    return boolValue;
}

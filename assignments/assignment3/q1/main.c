#include <stdio.h>
#include <string.h>
#include "main.h"

// Variable declarations
int testsFailed = 0;
int testsExecuted = 0;

//----------------------------------------------------------------
// FUNCTIONS
//----------------------------------------------------------------

void testCreateContainer(Container *testContainer, Boolean expected)
{
    Boolean result = (NULL != testContainer);

    if (result == expected)
    {
        printf("Container was created successfully\n");
    }
    else
    {
        printf("Container was not created Successfully\n");
        testsFailed++;
    }
    testsExecuted++;
}

void testDestroyContainer(Container **testContainer, Boolean expected)
{
    Boolean result = destroyContainer(testContainer);
    if (result == expected)
    {
        printf("Container was destroyed successfully\n");
    }
    else
    {
        printf("Container was not destroyed successfully\n");
        testsFailed++;
    }
    testsExecuted++;
}

void testInsertItem(Container *testContainer, char *tempString, int expectedSize)
{
    int prevSize = size(testContainer);
    Boolean isInserted = insertItem(testContainer, tempString);
    int newSize = size(testContainer);

    if (isInserted)
    {
        if (newSize == expectedSize)
        {
            printf("\"%s\" was inserted Successfuly\n", tempString);
            printf("Previous size of the container was %d, and the current size is %d\n\n", prevSize, newSize);
        }
        else
        {
            printf("\"%s\" was not inserted Successfully\n", tempString);
            printf("Previous size of the container was %d, and the current size is still %d\n\n", prevSize, newSize);

            testsFailed++;
        }
    }
    else
    {
        printf("\nError!!! The container is Invalid and thus can't be inserted into\n");
        testsFailed++;
    }
    testsExecuted++;
}

void testDeleteItem(Container *testContainer, char *removeString, int expectedSize)
{
    int prevSize = size(testContainer);
    Boolean isDeleted = deleteItem(testContainer, removeString);
    int newSize = size(testContainer);

    if (isDeleted)
    {
        if (newSize == expectedSize)
        {
            printf("\"%s\" was Deleted Successfully\n", removeString);
            printf("Previous size of the container was %d, and the current size is %d\n\n", prevSize, newSize);
        }
        else
        {
            printf("\"%s\" was not found and thus was not deleted Successfully\n", removeString);
            printf("Previous size of the container was %d, and the current size is still %d\n\n", prevSize, newSize);
            testsFailed++;
        }
    }
    else
    {
        printf("\nError!!! The Item could not be deleted from the Container because the Container is invalid\n");
        testsFailed++;
    }
    testsExecuted++;
}

void testClear(Container *testContainer, Boolean expected)
{
    Boolean result = clear(testContainer);

    if (result == expected)
    {
        printf("The Container has been cleared\n");
        printf("The size of the container is %d\n", size(testContainer));
    }
    else
    {
        printf("The Container could not be cleared because it is Invalid (NULL)\n");
        printf("The size of the container is %d\n", size(testContainer));

        testsFailed++;
    }
    testsExecuted++;
}

void testFirstItem(Container *testContainer, char *expectedString)
{
    char *returnedString = firstItem(testContainer);

    if (NULL == returnedString)
    {
        printf("Container is Invalid/Empty\n");
    }
    else if (NULL == expectedString)
    {
        printf("The expected String is NULL\n");
    }
    else
    {
        int result = strcmp(returnedString, expectedString);

        if (result == 0)
        {
            printf("The first item is \"%s\", which is the expected item\n", returnedString);
        }
        else
        {
            printf("Error, FirstItem() returned \"%s\" but the expected string was %s\n", returnedString, expectedString);
            testsFailed++;
        }
    }

    testsExecuted++;
}

void testNextItem(Container *testContainer, char *expectedString)
{
    char *returnedString = nextItem(testContainer);

    if (NULL == returnedString)
    {
        printf("Reached end of List or Container is Invalid/Empty\n");
    }
    else if (NULL == expectedString)
    {
        printf("The expected String is NULL\n");
    }
    else
    {
        int result = strcmp(returnedString, expectedString);

        if (result == 0)
        {
            printf("The next item is \"%s\", which is the expected item\n", returnedString);
        }
        else
        {
            printf("Error, NextItem() returned \"%s\" but the expected string was \"%s\"\n", returnedString, expectedString);
            testsFailed++;
        }
    }

    testsExecuted++;
}

void testContains(Container *testContainer, char *checkItem, Boolean expectedResult)
{
    Boolean result = contains(testContainer, checkItem);

    if (expectedResult == result)
    {
        printf("\"%s\" was found in the Container\n", checkItem);
    }
    else
    {
        printf("Container is invalid or \"%s\" was not found in the container\n", checkItem);
        testsFailed++;
    }
    testsExecuted++;
}

void testSize(Container *testContainer, int expectedSize)
{
    int returnedSize = size(testContainer);

    if (returnedSize == expectedSize)
    {
        printf("The size of the Container is %d, which is the expected size of the container\n", returnedSize);
    }
    else if (returnedSize == -1)
    {
        printf("Container is invalid, The size should be \"%d\" not \"%d\"\n", returnedSize, expectedSize);
        testsFailed++;
    }
    else
    {
        printf("Error, size() returned %d, but the expected size of the container should be %d\n", returnedSize, expectedSize);
        testsFailed++;
    }
    testsExecuted++;
}

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
    //-----------------------------------------------------------
    printf("\n******************** TESTING CREATE_CONTAINER ********************\n");

    printf("\n***************** Typical Case ******************\n");

    Container *validContainer = createContainer();

    printf("\nThis test should PASS beacause a valid container is Created\n");
    testCreateContainer(validContainer, true);

    printf("\n***************** Edge Case *****************\n");

    Container *invalidContainer = NULL;

    printf("This test should FAIL beacause the container is NULL\n");
    testCreateContainer(invalidContainer, true);

    //---------------------------------------------------------------
    printf("\n\n**************** TESTING INSERT_ITEM (Typical Cases) *****************\n");

    printf("\n");
    printf("The container should be empty\n");
    printContainer(validContainer);
    printf("\n");

    printf("Creating a new container...........\n");

    printf("These tests should all PASS\n\n");

    printf("Inserting \"String 1\"\n");
    testInsertItem(validContainer, "String 1", 1);
    printContainer(validContainer);

    printf("Inserting \"String 2\"\n");
    testInsertItem(validContainer, "String 2", 2);
    printContainer(validContainer);

    //-----------------------------------------------------------
    printf("\n***************** TESTING DESTROY_CONTAINER *******************\n");

    printf("\n*********** Typical Case ************\n");

    printf("\nThis test should PASS beacause the container is valid and thus can be destroyed\n");
    testDestroyContainer(&validContainer, true);

    printf("\n*********** Edge Case ***********\n");
    printf("This test should FAIL beacause the container is NULL and thus can't be destroyed\n");
    testDestroyContainer(&invalidContainer, true);

    //---------------------------------------------------------------
    printf("\n\n**************** TESTING INSERT_ITEM (Typical Cases) *****************\n");

    printf("\n");
    printf("The container should be destroyed and should be null\n");
    printContainer(validContainer);
    printf("\n");

    printf("Creating a new container...........\n");

    validContainer = createContainer();

    printf("These tests should all PASS\n\n");

    printf("Inserting \"String 1\"\n");
    testInsertItem(validContainer, "String 1", 1);
    printContainer(validContainer);

    printf("Inserting \"String 2\"\n");
    testInsertItem(validContainer, "String 2", 2);
    printContainer(validContainer);

    printf("Inserting \"String 3\"\n");
    testInsertItem(validContainer, "String 3", 3);
    printContainer(validContainer);

    printf("Inserting \"String 4\"\n");
    testInsertItem(validContainer, "String 4", 4);
    printContainer(validContainer);

    printf("\nInserting \"ANYTHING\" into the invalid Container \n");
    printf("This test should FAIL because the Container is NUll and can't be inserted into\n");
    testInsertItem(invalidContainer, "ANYTHING", 1);

    printf("\nThe Container should be null to show it is invalid\n");
    printContainer(invalidContainer);

    //-----------------------------------------------------------
    printf("\n\n***************** TESTING SIZE ****************\n");

    printf("\n************* Typical Case **************\n");

    printf("\nThe size of the container should be 4 here so this test should PASS\n");
    testSize(validContainer, 4);

    printf("\n*************** Edge Case *****************\n");
    printf("The Container is NUll, hence the size should be -1. This test should PASS\n");
    testSize(invalidContainer, -1);

    printf("\n*************** Edge Case *****************\n");
    printf("The Container is NUll, hence the size should be -1. This test should FAIL\n");
    testSize(invalidContainer, 0);

    //-----------------------------------------------------------------
    printf("\n\n********************* TESTING CONTAINS *******************\n");

    printf("\n");
    printContainer(validContainer);
    printf("\n");

    printf("\n***************** Typical Cases *****************\n");
    printf("\nThese tests should PASS\n");
    testContains(validContainer, "String 1", true);
    testContains(validContainer, "String 3", true);

    printf("\nThis next test should FAIL beacause \"String 0\" is not in the Container\n");
    testContains(validContainer, "String 0", true);

    printf("\n**************** Edge Cases *******************\n");
    printf("\nThe Container does not contain the empty string so these tests should FAIL\n");
    testContains(validContainer, "\0 String 1", true);
    testContains(validContainer, "", true);

    printf("\nThe Container does not contain the string with 4 spaces so this test should FAIL\n");
    testContains(validContainer, "    ", true);

    //-----------------------------------------------------------------
    printf("\n\n****************** TESTING FIRST_ITEM *********************\n");

    printf("\n");
    printContainer(validContainer);

    printf("\n****************** Typical Cases *******************\n");

    printf("This next test should PASS because the first item in the Container is \"String 4\"\n");
    testFirstItem(validContainer, "String 4");

    printf("\n*********** Edge Cases ***********\n");
    printf("This next test should return that the Container is either Empty or NULL\n");
    testFirstItem(invalidContainer, NULL);

    //-----------------------------------------------------------------
    printf("\n\n************** TESTING NEXT_ITEM *****************\n");

    printf("\n");
    printContainer(validContainer);

    printf("\n*********** Typical Cases ***********\n");

    printf("\nThis next test should PASS because the next item after \"String 4\" is \"String 3\"\n");
    testNextItem(validContainer, "String 3");

    printf("\nThis next test should FAIL because the next item after \"String 3\" is \"String 2\" ");
    printf("but \"String 2\" was passed as expected Result\n");
    testNextItem(validContainer, "String 1");

    printf("\nThe Container iterator is currently at the position of \"String 2\"\n");
    printf("\nThis next test should PASS because the next item after \"String 2\" is \"String 1\"\n");
    testNextItem(validContainer, "String 1");

    printf("\n/*Testing that the iterator does not loops through the Container in a circular manner\n");
    printf("The output of the following test should be null\n");
    printf("The contents of the Container at this point is String 4, String 3, String 2, String 1*/\n\n");
    testNextItem(validContainer, "String 4");

    //-----------------------------------------------------------------
    printf("\n\n************** TESTING DELETE_ITEM (Typical Cases) **************\n");

    printf("\n");
    printContainer(validContainer);

    printf("\nThese tests should PASS because \"String 1\" and \"String 3\" are in the Container\n");
    testDeleteItem(validContainer, "String 1", 3);
    printContainer(validContainer);
    testDeleteItem(validContainer, "String 3", 2);
    printContainer(validContainer);

    printf("\nThese tests should FAIL because \"String 0\" and \"String 5\" are in not the Container\n");
    testDeleteItem(validContainer, "String 0", 1);
    printContainer(validContainer);
    testDeleteItem(validContainer, "String 5", 0);
    printContainer(validContainer);

    printf("\nDeleting \"ANYTHING\" from the invalid Container \n");
    printf("\nThis test should FAIL because the Container is NUll and can't be deleted from\n");
    testDeleteItem(invalidContainer, "ANYTHING", 1);

    printf("\nThe Container should be null to show it is invalid\n");
    printContainer(invalidContainer);

    //-----------------------------------------------------------
    printf("\n\n************** TESTING SIZE ***************\n");

    printf("\nThe size of the container should be be 2 at this point, this test should PASS\n");
    testSize(validContainer, 2);

    //----------------------------------------------------------------
    printf("\n\n************ TESTING CLEAR (VALID CONTAINER)************\n");

    printf("\nThis test should PASS because the container is valid and thus can be cleared\n");
    testClear(validContainer, true);

    printf("\nThe Container should be empty\n");
    printContainer(validContainer);

    //-----------------------------------------------------------------
    printf("\n\n****************** TESTING FIRST_ITEM *********************\n");

    printf("\n");
    printContainer(validContainer);

    printf("\n****************** Typical Cases *******************\n");

    printf("This next test should PASS because the only item in the empty Container is NULL\n");
    testFirstItem(validContainer, NULL);

    //----------------------------------------------------------------
    printf("\n\n************ TESTING CLEAR (INVALID CONTAINER)************\n");

    printf("\nThis test should FAIL because the container is NULL and thus cannot be cleared\n");
    printf("\nThe size of the invalid container should be -1 to show that it is NULL\n");
    testClear(invalidContainer, true);

    //----------------------------------------------------------------
    printf("\n\n************ TESTING SIZE *************\n");

    printf("\nThe size of the valid container should be 0 after clearing\n");
    testSize(validContainer, 0);

    //----------------------------------------------------------------
    printf("\n\n**************** TESTING INSERT_ITEM (Edge Cases) ****************\n");

    printf("\nInserting a string containing 4 spaces. This test should PASS\n");
    testInsertItem(validContainer, "      ", 1);
    printContainer(validContainer);

    printf("\nInserting the empty String. This test should PASS\n");
    testInsertItem(validContainer, "", 2);
    printContainer(validContainer);

    printf("\nInserting a string terminated at the middle. This test should PASS and \"NULL\" should be inserted\n");
    testInsertItem(validContainer, "NULL\0terminatedString", 3);
    printContainer(validContainer);

    printf("\nInserting a string (char array) terminated at the middle. This test should PASS and \"NULL\" should be inserted\n");
    char testInsertString[] = {'N', 'U', 'L', 'L', '\0', 'A', 'R', 'R', 'A', 'Y'};
    testInsertItem(validContainer, testInsertString, 4);
    printContainer(validContainer);

    printf("\nInserting a string containing \"\\\\0\" inbetween. This test should PASS and \"NULL\\0String\" should be inserted\n");
    testInsertItem(validContainer, "NULL\\0String", 5);
    printContainer(validContainer);

    //----------------------------------------------------------------
    printf("\n\n*************** TESTING SIZE ***************\n");
    printf("\nThe size at this point should be 5, so this test should FAIL\n");
    testSize(validContainer, 4);

    printf("\nThis test should PASS\n");
    testSize(validContainer, 5);

    //-----------------------------------------------------------------
    printf("\n\n************* TESTING CONTAINS **************\n");

    printf("\n");
    printContainer(validContainer);

    printf("\n************* Typical Cases *************\n");

    printf("\nThe Container contains the empty string so this test should PASS\n");
    testContains(validContainer, "", true);

    printf("\nThe Container does not contain \"String 1\" so this test should FAIL\n");
    testContains(validContainer, "String 1", true);

    printf("\nThe Container contains \"NULL\" and this test searches for \"NULL\" so this test should PASS\n");
    testContains(validContainer, "NULL\0terminatedString", true);

    printf("\n************ Edge Cases ************\n");
    printf("\nThe Container does not contain \"{'N', 'U', 'L', 'L', '\\0', 'A', 'R', 'R', 'A', 'Y'}\" so this test should FAIL\n");
    testContains(validContainer, "{'N', 'U', 'L', 'L', '\0', 'A', 'R', 'R', 'A', 'Y'}", true);

    printf("\nThe Container does not contain the String with just 1 space so this test should FAIL\n");
    testContains(validContainer, " ", true);

    //----------------------------------------------------------------
    printf("\n\n*************** TESTING DELETE_ITEM (Edge Cases) *************\n");

    printf("\n");
    printContainer(validContainer);

    printf("\nThis test should PASS because the empty String is in the Container\n");
    testDeleteItem(validContainer, "", 4);
    printContainer(validContainer);

    printf("\nThis test should PASS because the String with 4 spaces is in the Container\n");
    testDeleteItem(validContainer, "      ", 3);
    printContainer(validContainer);

    printf("\nThis test should FAIL because the String with 2 spaces is not in the Container\n");
    testDeleteItem(validContainer, "  ", 2);
    printContainer(validContainer);

    printf("\nThis test should PASS because \"NULL\" is in the Container\n");
    testDeleteItem(validContainer, "NULL\0terminatedString", 2);
    printContainer(validContainer);

    printf("\nThis test should PASS because another \"NULL\" is in the Container\n");
    char testDeleteString[] = {'N', 'U', 'L', 'L', '\0', 'A', 'R', 'R', 'A', 'Y'};
    testDeleteItem(validContainer, testDeleteString, 1);
    printContainer(validContainer);

    printf("\nThis test should FAIL because \"NULL\\0\" is not in the Container\n");
    testDeleteItem(validContainer, "NULL\\0", 0);
    printContainer(validContainer);

    // Free the heap memory
    destroyContainer(&validContainer);

    printf("\n SUMMARY OF THE TESTS\n");
    printf("\nTotal number of tests EXECUTED: %d", testsExecuted);
    printf("\nNumber of tests PASSED: %d", (testsExecuted - testsFailed));
    printf("\nNumber of tests FAILED: %d\n", testsFailed);

    printf("\nEnd of Processing\n");
    return 0;
}
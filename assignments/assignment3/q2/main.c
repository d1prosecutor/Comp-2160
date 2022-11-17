#include <stdio.h>
#include "main.h"

// Variable declarations
int testsFailed = 0;
int testsExecuted = 0;

//----------------------------------------------------------------
// FUNCTIONS
//----------------------------------------------------------------

void testNewSet(Set *testSet, Boolean expected)
{
    Boolean result = (NULL != testSet);

    if (result == expected)
    {
        printf("Set was created successfully\n");
    }
    else
    {
        printf("Set was NOT created Successfully\n");
        testsFailed++;
    }
    testsExecuted++;
}

void testDeleteSet(Set *testSet, Boolean expected)
{
    Set *destroyedSet = deleteSet(testSet);

    Boolean result = (NULL == destroyedSet);

    if (result == expected)
    {
        printf("The Set was deleted successfully\n");
    }
    else
    {
        printf("The Set was NOT deleted successfully\n");
        testsFailed++;
    }
    testsExecuted++;
}

void testInsertItem(Set *const testSet, const int newItem, Boolean expected)
{
    Boolean isInserted = insertItem(testSet, newItem);

    if (testSet)
    {
        if (isInserted == expected)
        {
            printf("'%d' was inserted Successfuly\n", newItem);
        }
        else
        {
            printf("'%d' was NOT inserted Successfully\n", newItem);

            testsFailed++;
        }
    }
    else
    {
        printf("\nError!!! The Set is Invalid and thus can't be inserted into\n");
        testsFailed++;
    }
    testsExecuted++;
}

void testRemoveItem(Set *const testSet, const int givenItem, Boolean expected)
{
    Boolean isDeleted = removeItem(testSet, givenItem);

    if (testSet)
    {
        if (isDeleted == expected)
        {
            printf("'%d' was Deleted Successfuly\n", givenItem);
        }
        else
        {
            printf("'%d' was NOT found and thus was NOT deleted Successfully\n", givenItem);
            testsFailed++;
        }
    }
    else
    {
        printf("\nError!!! The Item could NOT be deleted from the Set because the Set is invalid\n");
        testsFailed++;
    }
    testsExecuted++;
}

void testAreEqual(Set const *const testSetA, Set const *const testSetB, Boolean expected)
{
    Boolean equal = areEqual(testSetA, testSetB);

    if (testSetA && testSetB)
    {
        if (equal == expected)
        {
            printf("The two sets contain the same elements and thus ARE equal\n");
        }
        else
        {
            printf("The two sets do NOT contain the same elements and thus are NOT equal\n");
            testsFailed++;
        }
    }
    else
    {
        printf("At least one of the sets is invalid and thus cannot be compared\n");
        testsFailed++;
    }
    testsExecuted++;
}

void testAreDisjoint(Set const *const testSetA, Set const *const testSetB, Boolean expected)
{
    Boolean disjoint = areDisjoint(testSetA, testSetB);

    if (testSetA && testSetB)
    {
        if (disjoint == expected)
        {
            printf("The two sets contain no common elements and thus ARE disjoint\n");
        }
        else
        {
            printf("The two sets contain at least one common element and thus are NOT disjoint\n");
            testsFailed++;
        }
    }
    else
    {
        printf("At least one of the sets is invalid and thus cannot be compared\n");
        testsFailed++;
    }
    testsExecuted++;
}

void testUnionOf(Set const *const testSetA, Set const *const testSetB, Set const *const unionSet)
{
    Set *tempSet = unionOf(testSetA, testSetB);

    if (testSetA && testSetB)
    {
        if (areEqual(tempSet, unionSet))
        {
            printf("The result of the union of the two sets is ACCURATE\n");
        }
        else
        {
            printf("The resulting Union Set DIFFERS from the expected Union Set\n");
            testsFailed++;
        }
    }
    else
    {
        printf("At least one of the sets is invalid and thus cannot be joined to the other set\n");
        testsFailed++;
    }

    deleteSet(tempSet);
    testsExecuted++;
}

void testSymmetricDifferenceOf(Set const *const testSetA, Set const *const testSetB, Set const *const symmDiffSet)
{
    Set *tempSet = symmetricDifferenceOf(testSetA, testSetB);

    if (testSetA && testSetB)
    {
        if (areEqual(tempSet, symmDiffSet))
        {
            printf("The result of the symmetric difference of the two sets is ACCURATE\n");
        }
        else
        {
            printf("The resulting symmetric difference Set DIFFERS from the expected symmetric difference Set\n");
            testsFailed++;
        }
    }
    else
    {
        printf("At least one of the sets is invalid and thus cannot be joined to the other set\n");
        testsFailed++;
    }

    deleteSet(tempSet);
    testsExecuted++;
}

void testValidateMemUse(Boolean expected)
{
    Boolean result = validateMemUse();

    if (result == expected)
    {
        printf("\nThere are no existing Set objects\n");
    }
    else
    {
        printf("\nThere are existing Set objects\n");
        testsFailed++;
    }
    testsExecuted++;
}

int main()
{
    //-----------------------------------------------------------

    // Creating 2 empty Sets which will be used in test cases
    Set *emptySet1 = newSet();
    Set *emptySet2 = newSet();

    printf("\n******************** TESTING NEW_SET ********************\n");

    printf("\n***************** Typical Case ******************\n");

    Set *validSet1 = newSet();

    printf("\nThis test should PASS beacause a valid Set (validSet1) is Created\n");
    testNewSet(validSet1, true);

    printf("\n***************** TESTING NEW_SET (Edge Case) *****************\n");

    // Set *invalidSet = NULL;

    // printf("This test should FAIL beacause the Set (invalidSet) is NULL\n");
    // testNewSet(invalidSet, true);

    //---------------------------------------------------------------
    printf("\n\n**************** TESTING INSERT_ITEM (Typical Cases) *****************\n");

    printf("\nThese tests should all PASS\n\n");

    printf("Inserting '1'\n");
    testInsertItem(validSet1, 1, true);

    printf("Inserting '2' \n");
    testInsertItem(validSet1, 2, true);

    //-----------------------------------------------------------
    printf("\n***************** TESTING DELETE_SET (Typical case) *******************\n");

    printf("\n*********** Typical Case ************\n");

    printf("\nThis test should PASS beacause the Set (validSet1) is valid and thus can be destroyed\n");
    testDeleteSet(validSet1, true);

    printf("\n*********** TESTING DELETE_SET (Empty/Edge Cases) ***********\n");

    printf("\nThis test should PASS beacause the Set is valid (although empty) and thus can be destroyed\n");
    testDeleteSet(emptySet1, true);

    // printf("\nThis test should FAIL beacause the Set (invalidSet) is NULL and thus can't be destroyed\n");
    // testDeleteSet(invalidSet, true);

    printf("\nRecreating the empty Set (because it was just destroyed)...........\n");
    emptySet1 = newSet();

    //---------------------------------------------------------------
    printf("\n\n**************** TESTING INSERT_ITEM (Typical Cases) *****************\n");

    printf("\nRecreating validSet1 (because it was aslo destroyed)...........\n");

    validSet1 = newSet();

    printf("\nRecreating equalSet which contains all the elements that should be in validSet aftrr inserting...........\n");
    Set *equalSet = newSet();

    insertItem(equalSet, 1);
    insertItem(equalSet, 2);
    insertItem(equalSet, 3);
    insertItem(equalSet, 4);
    insertItem(equalSet, 5);

    printf("\nThese tests should all PASS\n\n");

    printf("Inserting '1'\n");
    testInsertItem(validSet1, 1, true);

    printf("Inserting '2'\n");
    testInsertItem(validSet1, 2, true);

    printf("Inserting '3'\n");
    testInsertItem(validSet1, 3, true);

    printf("Inserting '4'\n");
    testInsertItem(validSet1, 4, true);

    printf("Inserting '5'\n");
    testInsertItem(validSet1, 5, true);

    printf("\n\nThese tests should all FAIL Because the numbers being inserted into validSet1 are already contained in validSet1\n\n");

    printf("Inserting \"1\"\n");
    testInsertItem(validSet1, 1, true);

    printf("Inserting \"2\"\n");
    testInsertItem(validSet1, 2, true);

    printf("Inserting \"3\"\n");
    testInsertItem(validSet1, 3, true);

    printf("Inserting \"4\"\n");
    testInsertItem(validSet1, 4, true);

    printf("Inserting \"5\"\n");
    testInsertItem(validSet1, 5, true);

    printf("\n\n********** TESTING INSERT_ITEM(Edge Cases) *********\n");

    printf("\nThis test should PASS because equalSet contains all the elements that validSet1 should contain after insertion\n");
    testAreEqual(equalSet, validSet1, true);

    //-----------------------------------------------------------------
    printf("\n\n************** TESTING REMOVE_ITEM (Typical Cases) **************\n");

    printf("\nThese tests should PASS because \"1\" and \"3\" are in validSet1\n");
    testRemoveItem(validSet1, 1, true);
    testRemoveItem(validSet1, 3, true);

    printf("\nThese tests should FAIL because \"0\" and \"6\" are in NOT validSet1\n");
    testRemoveItem(validSet1, 0, true);
    testRemoveItem(validSet1, 6, true);

    removeItem(equalSet, 1);
    removeItem(equalSet, 2);
    printf("\nThis test should PASS because equalSet contains all the elements that validSet1 should contain after deletion\n");
    testAreEqual(equalSet, validSet1, true);

    printf("\n\n********** TESTING REMOVE_ITEM (Empty/Edge Cases) *********\n");

    printf("\nDeleting any random number from the empty Set \n");
    printf("\nThis test should FAIL because the set (emptySet) is empty so there's nothing to be deleted\n");
    testRemoveItem(emptySet1, 0, true);

    printf("\nAdding 1 and 3 back to the valid Set for testing purposes...........\n");
    insertItem(validSet1, 1);
    insertItem(validSet1, 3);

    //----------------------------------------------------------------
    printf("\n\n**************** TESTING ARE_EQUAL (Typical Cases) ****************\n");

    printf("\nCreating a second Set (validSet2) with same elements as the first set (validSet1)......\n");

    Set *validSet2 = newSet();
    insertItem(validSet2, 1);
    insertItem(validSet2, 2);
    insertItem(validSet2, 3);
    insertItem(validSet2, 4);
    insertItem(validSet2, 5);

    printf("\nThis test should PASS because validSet1 and validSet2 have the same elements\n");
    testAreEqual(validSet1, validSet2, true);

    printf("\nRemoving the last element from validSet2 so that the Sets are no longer equal\n");
    removeItem(validSet2, 5);

    printf("\nThis test should FAIL because validSet1 and validSet2 don't have the same elements\n");
    testAreEqual(validSet1, validSet2, true);

    printf("\n\n********** TESTING ARE_EQUAL (Empty/Edge Cases) *********\n");

    printf("\nThis test should PASS because validSet1 and validSet1 are the same Set and thus are equal\n");
    testAreEqual(validSet1, validSet1, true);

    printf("\nThis test should FAIL because validSet1 and emptySet don't have the same elements (validSet1 contains elements)\n");
    testAreEqual(validSet1, emptySet1, true);

    // testAreEqual(validSet1, invalidSet, true);

    printf("\nThis test should PASS because emptySet and emptySet have the same elements (no elements)\n");
    testAreEqual(emptySet1, emptySet1, true);
    // testAreEqual(emptySet, invalidSet, true);
    // testAreEqual(invalidSet, invalidSet, true);

    //----------------------------------------------------------------
    printf("\n\n*************** TESTING ARE_DISJOINT (Typical Case) *************\n");

    printf("\nCreating a third Set with no common elements as the first set (validSet1)......\n");

    Set *disjointSet = newSet();
    insertItem(disjointSet, -1);
    insertItem(disjointSet, -2);
    insertItem(disjointSet, -4);
    insertItem(disjointSet, -5);
    insertItem(disjointSet, -6);

    printf("\nThis test should FAIL because validSet1 and validSet2 have some common elements and thus are NOT disjoint\n");
    testAreDisjoint(validSet1, validSet2, true);

    printf("\nThis test should PASS because validSet1 and disjointSet have no common elements and thus are disjoint\n");
    testAreDisjoint(validSet1, disjointSet, true);

    printf("\n\n********** TESTING ARE_DISJOINT (Empty/Edge Case) *********\n");
    printf("\nThis test should FAIL because validSet1 and validSet1 are the same Set and thus are NOT disjoint (contain same elements)\n");
    testAreDisjoint(validSet1, validSet1, true);

    printf("\nThis test should PASS because one of the sets is empty and thus the sets are Disjoint\n");
    testAreDisjoint(validSet1, emptySet1, true);
    // testAreDisjoint(validSet1, invalidSet, true);

    printf("\nThis test should PASS because emptySet and emptySet have no elements, thus no common elements and are thus, disjoint\n");
    testAreDisjoint(emptySet1, emptySet1, true);
    // testAreDisjoint(emptySet, invalidSet, true);
    // testAreDisjoint(invalidSet, invalidSet, true);

    //----------------------------------------------------------------
    printf("\n\n**************** TESTING UNION_OF (Typical Cases) ****************\n");

    printf("\nCreating a second Set with elements of both validSet1 and validSet2 (without duplicates)......\n");

    Set *unionSet = newSet();
    insertItem(unionSet, 1);
    insertItem(unionSet, 2);
    insertItem(unionSet, 3);
    insertItem(unionSet, 4);
    insertItem(unionSet, 5);

    printf("\nThis test should PASS because the union Set contains all the elements from validSet1 and validSet2\n");
    testUnionOf(validSet1, validSet2, unionSet);

    printf("\nAdding an element to the union set that is neither in validSet1 nor validSet2......\n");
    insertItem(unionSet, 6);

    printf("\nThis test should FAIL because the union Set contains an extra element in addition to all the elements from validSet1 and validSet2\n");
    testUnionOf(validSet1, validSet2, unionSet);

    printf("\nMaking the union set contain only all the elements from the smaller set (validSet2)......\n");
    removeItem(unionSet, 5);

    printf("\nThis test should FAIL because the union Set is missing one element from validSet2\n");
    testUnionOf(validSet1, validSet2, unionSet);

    printf("\n\n********** TESTING UNION_OF (Empty/Edge Cases) *********\n");
    printf("\nThis test should PASS because validSet1 and validSet1 are the same Set and thus the union is the same Set (contains same elements as validSet1)\n");
    testUnionOf(validSet1, validSet1, validSet1);

    printf("\nThis test should PASS because the union of validSet1 and emptySet is validSet1\n");
    testUnionOf(validSet1, emptySet1, validSet1);

    // testUnionOf(validSet1, invalidSet, validSet1);

    printf("\nThis test should PASS because the union of emptySet1 and emptySet1 is the emptySet(-emptySet1, all having the same memory address)\n");
    testUnionOf(emptySet1, emptySet1, emptySet1);

    printf("\nThis test should PASS because the union of emptySet1 and emptySet1 is the emptySet(-emptySet2, with a different memory adress from emptySet1)\n");
    testUnionOf(emptySet1, emptySet1, emptySet2);
    // testUnionOf(emptySet, invalidSet, emptySet);
    // testUnionOf(invalidSet, invalidSet, NULL);

    //----------------------------------------------------------------
    printf("\n\n**************** TESTING SYMMETRIC_DIFFERENCE (Typical Cases) ****************\n");

    printf("\nAdding extra items to validSet1 and validSet2 to get a substantial symmetric difference (not jut a single number).......\n");
    insertItem(validSet1, 0);
    insertItem(validSet1, 6);
    insertItem(validSet1, 7);
    insertItem(validSet1, 8);
    insertItem(validSet1, 9);
    insertItem(validSet1, 10);

    insertItem(validSet2, 6);
    insertItem(validSet2, 7);
    insertItem(validSet2, 8);
    insertItem(validSet2, 9);
    insertItem(validSet2, 20);
    insertItem(validSet2, 30);
    insertItem(validSet2, 40);
    insertItem(validSet2, 50);

    printf("\nCreating a second Set with the symmetric difference of validSet1 and validSet2......\n");

    Set *symmDiffSet = newSet();
    insertItem(symmDiffSet, 0);
    insertItem(symmDiffSet, 5);
    insertItem(symmDiffSet, 10);
    insertItem(symmDiffSet, 20);
    insertItem(symmDiffSet, 30);
    insertItem(symmDiffSet, 40);
    insertItem(symmDiffSet, 50);

    printf("\nThis test should PASS because the symmetric Difference Set contains all the elements either in validSet1 or validSet2 but not both\n");
    testSymmetricDifferenceOf(validSet1, validSet2, symmDiffSet);

    printf("\nAdding an element that is in both validSet1 and validSet2 to the symmetric Difference set......\n");
    insertItem(symmDiffSet, 1);

    printf("\nThis test should FAIL because the symmetric difference Set contains an element in which is in both validSet1 and validSet2\n");
    testSymmetricDifferenceOf(validSet1, validSet2, symmDiffSet);

    printf("\nMaking the symmetric difference set contain only all the elements that are in validSet2 but not in validSet1......\n");
    removeItem(symmDiffSet, 0);
    removeItem(symmDiffSet, 5);
    removeItem(symmDiffSet, 10);

    printf("\nThis test should FAIL because the symmetric difference Set is missing some elements from Set1 which it should contain\n");
    testSymmetricDifferenceOf(validSet1, validSet2, symmDiffSet);

    printf("\n\n********** TESTING SYMMETRIC_DIFFERENCE (Empty/Edge Cases) *********\n");

    printf("\nThis test should PASS because validSet1 and validSet1 are the same Set and thus their symmetric Difference Set is the empty set\n");
    testSymmetricDifferenceOf(validSet1, validSet1, emptySet1);

    printf("\nThis test should PASS because the symmetric Difference of any non-empty Set (validSet1) and an empty Set is the non-empty Set(validSet1)\n");
    testSymmetricDifferenceOf(validSet1, emptySet1, validSet1);

    // testSymmetricDifferenceOf(validSet1, invalidSet, validSet1);

    printf("\nThis test should PASS because the symmetric difference of two empty Sets(emptySet1 and emptySet1) is the emptySet(emptySet1- all having same memory address)\n");
    testSymmetricDifferenceOf(emptySet1, emptySet1, emptySet1);

    printf("\nThis test should PASS because the symmetric difference of two empty Sets(emptySet1 and emptySet1) is the emptySet(emptySet2- with different memory address)\n");
    testSymmetricDifferenceOf(emptySet1, emptySet1, emptySet2);

    // testSymmetricDifferenceOf(emptySet, invalidSet, emptySet);
    // testSymmetricDifferenceOf(invalidSet, invalidSet, NULL);

    //----------------------------------------------------------------
    printf("\n\n**************** TESTING VALIDATE_MEM_USE (Typical Cases) ****************\n");
    printf("\nThis test should FAIL because validSet1, validSet2, unionSet, disjointSet, symmetricDifference set, emptySet1, and emptySet2 are still in use\n");
    testValidateMemUse(true);

    printf("\nDeleting emptySet1.........\n");
    deleteSet(emptySet1);
    printf("\nThis test should FAIL because validSet1, validSet2, unionSet, disjointSet, symmetricDifference set, and emptySet2 are still in use\n");
    testValidateMemUse(true);

    printf("\nDeleting symmDiffSet.........\n");
    deleteSet(symmDiffSet);
    printf("\nThis test should FAIL because validSet1, validSet2, unionSet, disjointSet, and emptySet2 are still in use\n");
    testValidateMemUse(true);

    printf("\nDeleting unionSet......\n");
    deleteSet(unionSet);
    printf("\nThis test should FAIL because validSet1, validSet2, disjointSet, and emptySet2 are still in use\n");
    testValidateMemUse(true);

    printf("\nDeleting all the sets still in use..........\n");
    deleteSet(disjointSet);
    deleteSet(emptySet2);
    deleteSet(validSet2);
    deleteSet(validSet1);

    printf("\nThis test should PASS because there should be no other Set still in use (still in memory)\n");
    testValidateMemUse(true);

    //-----------------------------------------------------------------
    printf("\n SUMMARY OF THE TESTS\n");
    printf("\nTotal number of tests EXECUTED: %d", testsExecuted);
    printf("\nNumber of tests PASSED: %d", (testsExecuted - testsFailed));
    printf("\nNumber of tests FAILED: %d\n", testsFailed);

    printf("\nEnd of Processing\n");
    return 0;
}
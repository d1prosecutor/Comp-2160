#include "ObjectManager.h"
#include <stdio.h>
#include <string.h>

typedef struct POINTER
{
    int *integerPtr;
    char *characterPtr;
    char *stringPtr;
} pointer;

int main(int argc, char *argv[])
{
    printf("---INITIALIZING THE MEMORY POOL......\n\n");
    char *charPtr, *strPtr1, *strPtr2;
    int *intPtr;
    int i;
    int id1, id2, id3, id4, id5;
    initPool();

    printf("---TESTING INSERT_OBJECT---\n");
    // ID1
    id1 = insertObject(400);
    intPtr = (int *)retrieveObject(id1);

    for (i = 0; i < 100; i++)
    {
        intPtr[i] = (i + 1);
    }

    printf("The buffer should contain a memory block holding integers 1 to 100...\n");
    for (i = 0; i < 100; i++)
    {
        printf("%d ", intPtr[i]);
    }
    printf("\n");

    // ID2
    id2 = insertObject(26);
    charPtr = (char *)retrieveObject(id2);

    for (i = 0; i < 26; i++)
    {
        charPtr[i] = (char)(i % 26 + 'A');
    }

    printf("\nThe buffer should contain a memory block holding the letters of the Alphabet...\n");
    for (i = 0; i < 26; i++)
    {
        printf("%c ", charPtr[i]);
    }
    printf("\n");

    // ID3
    id3 = insertObject(42);
    char testString[] = "The Quick Brown Fox Jumps Over A Lazy Dog.";

    strPtr1 = (char *)retrieveObject(id3);
    for (i = 0; i < 42; i++)
    {
        strPtr1[i] = testString[i];
    }

    printf("\nThe buffer should contain a memory block holding a Sentence...\n");
    printf("%s\n", strPtr1);

    printf("\n---TESTING RETRIEVE_OBJECT && DUMP_POOL---\n");

    // ID4
    id4 = insertObject(16);
    pointer *ptr_PTR;
    ptr_PTR = (pointer *)retrieveObject(id4);

    ptr_PTR->integerPtr = (int *)retrieveObject(id1);
    ptr_PTR->characterPtr = (char *)retrieveObject(id2);
    ptr_PTR->stringPtr = (char *)retrieveObject(id3);
    printf("\nThe address of the memory block holding Integers is: %p\n", ptr_PTR->integerPtr);
    printf("The address of the memory block holding Characters is: %p\n", ptr_PTR->characterPtr);
    printf("The address of the memory block holding String is: %p\n", ptr_PTR->stringPtr);

    printf("\nThe first three blocks in the memory buffer below should have the same address as the addresses above.\n");
    dumpPool();

    printf("\n---TESTING ADD AND DROP REFERENCE---\n");
    printf("\nAdding one reference each to the objects with id 1 and 3...\n");
    addReference(id1);
    addReference(id3);

    printf("\nDropping the only reference to the object with id = 2...\n");
    dropReference(id2);

    printf("\nOnly three memory blocks should exist in the memory buffer now (Block 2 should be gone).\n");
    dumpPool();

    printf("---TESTING INSERT_OBJECT---\n");
    printf("The memory block which was removed should not be available to write to untill garbage is collected.\n");

    // ID5
    printf("Requesting for 'more than enough' space for the string to be inserted...\n");
    id5 = insertObject(50);
    char testString2[] = "Testing insert after dropping a reference.";

    strPtr2 = (char *)retrieveObject(id3);
    for (i = 0; i < 43; i++)
    {
        strPtr2[i] = testString2[i];
    }

    printf("\nThe buffer should contain a memory block holding a Sentence and some other garbage at the end...\n");
    for (i = 0; i < 50; i++)
    {
        printf("%c", strPtr2[i]);
    }
    printf("\n");

    // dumpPool();
    // destroyPool();
    // fprintf(stderr, "---\n");

    return 0;
}

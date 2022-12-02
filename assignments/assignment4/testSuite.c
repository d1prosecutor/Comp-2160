#include "ObjectManager.h"
#include <stdio.h>
#include <string.h>

typedef struct STRUCT
{
    int intVal;
    double doubleVal;
    char *stringVal;
} structure;

int main(int argc, char *argv[])
{
    //--------------------------------------------
    printf("\n\t\t\tTESTING TYPICAL FUNCTIONS\n");
    //--------------------------------------------

    printf("\n--- INITIALIZING THE MEMORY POOL ---\n\n");
    char *charPtr, *strPtr;
    int *intPtr;
    int i;
    int id1, id2, id3, id4, id5;
    initPool();

    //--------------------------------------------------------
    printf("---TESTING INSERT_OBJECT && RETRIEVE_OBJECT---\n");
    //--------------------------------------------------------

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
    id2 = insertObject(1000);
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
    id3 = insertObject(2000);
    char testString[] = "The Quick Brown Fox Jumps Over A Lazy Dog.";

    strPtr = (char *)retrieveObject(id3);
    for (i = 0; i < 43; i++)
    {
        strPtr[i] = testString[i];
    }

    printf("\nThe buffer should contain a memory block holding a String (Sentence)...\n\"");
    printf("%s\"\n", strPtr);

    // ID4
    structure mixedDataType;
    mixedDataType.intVal = 500000;
    mixedDataType.doubleVal = 0.123456789;
    mixedDataType.stringVal = "Hello, World!";

    id4 = insertObject(sizeof(structure));
    structure *structPtr = (structure *)retrieveObject(id4);

    *structPtr = mixedDataType;
    printf("\nThe buffer should contain struct having Integer, Double and String members...");
    printf("\nThe Struct's int, double and string values are: %d, %lf, \"%s\"\n",
           structPtr->intVal, structPtr->doubleVal, structPtr->stringVal);

    printf("\nThere should be FOUR existing distinct blocks (Objects) in the memory pool.\n");
    dumpPool();

    printf("\nTrying to request for memory which is Invalid...\n");
    id5 = insertObject(-100000);
    printf("\nThe return value should be a null reference...\n");
    printf("The Object reference returned is: %d\n", id5);

    printf("\nTrying to request for memory which is larger than the buffer...\n");
    id5 = insertObject(600000);
    printf("\nThe return value should be a null reference...\n");
    printf("The Object reference returned is: %d\n", id5);

    printf("\nTrying to Retrieve the address of an invalid Object...\n");
    char *invalid = (char *)retrieveObject(0);
    printf("\nThe return value should be null...\n");
    printf("The memory address returned is: %s\n", invalid);

    //-------------------------------------------------
    printf("\n---TESTING ADD AND DROP REFERENCE---\n");
    //-------------------------------------------------

    printf("\nAdding one reference each to the objects with id = 1 and id = 3...\n");
    addReference(id1);
    addReference(id3);

    printf("\nDropping the only reference to the object with id = 2...\n");
    dropReference(id2);

    printf("\nOnly three memory blocks should exist in the memory buffer now (Block with id = 2 should be gone).\n");
    dumpPool();

    printf("\nDropping one reference to the object with id = 1...\n");
    dropReference(id1);

    printf("There should still be one object pointing to the reference of id1 so it should still be in the memory pool...\n");
    dumpPool();

    printf("Dropping two references to the object with id = 3...\n");
    dropReference(id3);
    dropReference(id3);

    printf("There should be no references to the object with id = 3, so it should no longer be in the memory pool...\n");
    dumpPool();

    printf("\nTrying to add a reference to an object which is no longer in existence(id3)...\n");
    addReference(id3);

    printf("The memory pool should remain unchanged (conatain 2 blocks) because the reference shouldn't be added\n");
    dumpPool();

    printf("\nTrying to remove a reference to an object which is no longer in existence(id3)...\n");
    dropReference(id3);

    printf("The memory pool should remain unchanged (conatain 2 blocks) because the reference shouldn't be found\n");
    dumpPool();

    printf("--- DESTROYING THE MEMORY POOL ---");
    destroyPool();

    printf("\n\n////////////////////////////////////////////////////////////////////////////////////////////////////////\n");

    //-------------------------------------------------
    printf("\n\t\t\tTESTING THE GARBAGE COLLECTOR\n");
    //-------------------------------------------------

    printf("\n--- INITIALIZING THE MEMORY POOL ---\n");
    initPool();

    printf("\nRequesting space for 25,000 Integers from the buffer...\n");
    printf("So 100,000 bytes should now be used up from the buffer, the buffer should have 424,288 bytes left.\n\n");
    id1 = insertObject(100000);
    dumpPool();

    printf("\nRequesting space for 200,000 characters from the buffer...\n");
    printf("300,000 bytes should now be used up from the buffer, so it should have 224,288 bytes left.\n\n");
    id2 = insertObject(200000);
    dumpPool();

    printf("\nDeleting the object with id = 2 from the buffer (200,000 bytes marked as garbage)...\n");
    dropReference(id2);
    dumpPool();

    printf("\nRequesting space for 300,000 characters from the buffer...\n");
    printf("The space left in the buffer is just 224,288 bytes but 200,000 bytes should be garbage collected now...\n");
    printf("So there should be enough memory to allocate 300,000 bytes to the user\n");
    id3 = insertObject(300000);

    printf("\n>>>\nThe number of objects still in use should now be 2 (because another object was created after garbage collection)...\n");
    printf("The number of bytes in use now should be 400,000...\n");
    printf("The available memory in the buffer now should be 124,288 bytes...\n<<<\n");
    dumpPool();

    printf("\nRequesting space for 10,000 Double values from the buffer...\n");
    printf("So 80,000 bytes should now be used up from the buffer, the buffer should have 44,288 bytes left.\n\n");

    id4 = insertObject(80000);
    double *doublePtr = (double *)retrieveObject(id4);
    *doublePtr = 57.24681357;

    printf("The double value contained by object with id4 is: %lf\n", *doublePtr);

    printf("\nDeleting the object with id = 1 from the buffer (100,000 bytes marked as garbage)...\n");
    dropReference(id1);
    dumpPool();

    printf("\nRequesting space for 64,000 characters from the buffer...\n");
    printf("The space left in the buffer is just 44,288 bytes but 100,000 bytes should be garbage collected now...\n");
    printf("So there should be enough memory to allocate 64,000 bytes to the user\n");
    id5 = insertObject(64000);

    printf("\n>>>\nThe number of objects still in use should be 3...\n");
    printf("The number of bytes in use now should be 444,000...\n");
    printf("The available memory in the buffer now should be 80,288 bytes...\n<<<\n");
    dumpPool();

    printf("--- DESTROYING THE MEMORY POOL ---\n\n");
    destroyPool();

    fprintf(stderr, "---\n");
    printf("\nEnd of Processing\n");
    return 0;
}

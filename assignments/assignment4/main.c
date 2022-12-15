//-----------------------------------------------
// NAME: Zehra Rizvi
// STUDENT NUMBER: 7839659
// COURSE: COMP 2160, SECTION: A02
// INTRUCTOR: Rasit Eskicioglu
// ASSIGNMENT: assignment 4
//
// FILE NAME: main.c
//
// Purpose: THIS FUNCTION IS A TEST SUITE THAT I ENGINEERED TO MAKE SURE CAN SAFELY TEST
// OUT EDGE CASES WITHOUT ANY ERROR MESSAGES

#include "ObjectManager.h"
#include <stdio.h>

int main(int argc, char *argv[])
{

    /* TEST INSERTOBJECT FUNCTION */
    int id1, id2, id3, id4, id5;
    initPool();

    /* TEST A STRING */
    id1 = insertObject(100);
    char *ptr; // string pointer
    ptr = (char *)retrieveObject(id1);
    for (int i = 0; i < 55; i++)
        ptr[i] = (char)(i % 26 + 'B');
    dumpPool();

    /* TEST A LONG */
    id2 = insertObject(800);
    long *lptr; // string pointer
    lptr = (long *)retrieveObject(id1);
    for (int i = 0; i < 100; i++)
        lptr[i] = 5000;
    dumpPool();

    /* TEST A INT  */
    id3 = insertObject(4000);
    int *intptr = (int *)retrieveObject(id3);
    for (int i = 0; i < 1000; i++)
        intptr[i] = 3;
    dumpPool();
    dropReference(id3);
    dumpPool();

    /* TEST A DOUBLE */
    id4 = insertObject(8000);
    double *dblePtr = (double *)retrieveObject(id4);
    for (int i = 0; i < 1000; i++)
        dblePtr[i] = 7.8;

    dumpPool();
    // MAX_SIZE = 524,288
    // MAX_SIZE - 12,900 = 511,388
    id5 = insertObject(513388);
    dumpPool();

    destroyPool();
    fprintf(stderr, "---\n");

    return 0;
}

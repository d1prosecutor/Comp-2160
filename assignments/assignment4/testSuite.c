#include "ObjectManager.h"
#include <stdio.h>

void testInsertObject(const int size)
{
}

// returns a pointer to the object being requested given by the reference id
void testRetrieveObject(const Ref ref);

// update our index to indicate that we have another reference to the given object
void testAddReference(const Ref ref);

// update our index to indicate that a reference is gone
void testDropReference(const Ref ref);

// initialize the object manager
void testInitPool();

// clean up the object manager (before exiting)
void testDestroyPool();

// This function traverses the index and prints the info in each entry corresponding to a block of allocated memory.
// You should print the block's reference id, it's starting address, and it's size (in bytes).
void testDumpPool();

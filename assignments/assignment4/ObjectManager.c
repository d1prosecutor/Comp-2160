#include "ObjectManager.h"
#include <stdlib.h>
#include <assert.h>

typedef struct NODE Node;
struct NODE
{
    Ref numBytes;
    void *startAddress;
    Ref referenceID;
    Ref count;

    Node *next;
};

struct MEMORYPOOL
{
    Node *top;
    Ref numNodes;
    void *freePtr;
    void *endOfBuffer;
};
typedef struct MEMORYPOOL memPool;

// Global variable for the object memory manager
memPool *heapMemory = NULL;

// initialize the object manager
void initPool()
{
    heapMemory = malloc(sizeof(memPool) + MEMORY_SIZE); // might or might not use

    // Ensure that the space was actually allocated
    assert(NULL != heapMemory);

    // Initialize the member variables new object manager
    if (NULL != heapMemory)
    {
        heapMemory->top = NULL;
        heapMemory->numNodes = 1;
        heapMemory->freePtr = heapMemory + sizeof(memPool);

        // Variable to hold the address end of the Memory Buffer
        heapMemory->endOfBuffer = heapMemory->freePtr + MEMORY_SIZE;

        assert(NULL != heapMemory);
    }
    else
    {
        printf("Not enough memory\n");
        exit(1);
    }
}

// This function trys to allocate a block of given size from our buffer.
// It will fire the garbage collector as required.
// We always assume that an insert always creates a new object...
// On success it returns the reference number for the block of memory allocated for the object.
// On failure it returns NULL_REF (0)
Ref insertObject(const int size)
{
    Ref refResult = NULL_REF;

    assert(NULL != heapMemory);

    if (NULL != heapMemory)
    {
        if (heapMemory->freePtr + size < heapMemory->endOfBuffer)
        {
            // If there is still memory avaiable to allocate
            assert(heapMemory->freePtr + size <= heapMemory->endOfBuffer);

            Node *curr = heapMemory->top;
            Node *prev = NULL;

            // Find the location to insert the new allocated memory
            while (NULL != curr)
            {
                prev = curr;
                curr = curr->next;
            }

            // Making a new Node for the linked list
            Node *newNode = malloc(sizeof(Node));

            assert(NULL != newNode);
            if (NULL != newNode)
            {

                // Initialize the member variables for the new Node
                newNode->numBytes = size;
                newNode->startAddress = heapMemory->freePtr;
                newNode->count = 1; // number of objects pointing to this address
                newNode->referenceID = heapMemory->numNodes++;
                newNode->next = NULL; // The next node will always be null since insertion is occuring at the end

                if (NULL == prev)
                {
                    // Insert at the top as the only element if the list is empty
                    heapMemory->top = newNode;
                }
                else
                {
                    // Insert at the end of the list if there are existing elements
                    prev->next = newNode;
                }

                // Shift the position of the free memory pointer to point to the next available space
                heapMemory->freePtr += size;

                refResult = newNode->referenceID;

                // assert that the memory now contains at least one element
                assert(NULL != heapMemory->top);
            }
        }
        else
        {
            assert(heapMemory->freePtr + size > heapMemory->endOfBuffer);

            /// Garbage collection here
        }
    }

    return refResult;
}

// returns a pointer to the object being requested given by the reference id
void *retrieveObject(const Ref ref)
{
    int objectNotFound = 1; // boolean variable for searching for the object
    void *result = NULL;

    Node *curr = heapMemory->top;

    assert(NULL != curr);
    while ((NULL != curr) && objectNotFound)
    {
        if (ref == curr->referenceID)
        {
            result = curr->startAddress;
            objectNotFound = 0;

            assert(ref == curr->referenceID);
        }
        curr = curr->next;
    }

    return result;
}

// update our index to indicate that we have another reference to the given object
void addReference(const Ref ref)
{
    int objectNotFound = 1; // boolean variable for searching for the object

    Node *curr = heapMemory->top;

    assert(NULL != curr);
    while ((NULL != curr) && objectNotFound)
    {
        if (ref == curr->referenceID)
        {
            assert(ref == curr->referenceID);

            curr->count++;
            objectNotFound = 0;
        }
        curr = curr->next;
    }
}

// update our index to indicate that a reference is gone
void dropReference(const Ref ref)
{
    int objectNotFound = 1; // boolean variable for searching for the object

    Node *curr = heapMemory->top;
    Node *prev = NULL;

    assert(NULL != curr);
    while ((NULL != curr) && objectNotFound)
    {
        if (ref == curr->referenceID)
        {
            assert(ref == curr->referenceID);

            curr->count--;
            objectNotFound = 0;
        }
        prev = curr;
        curr = curr->next;
    }

    // If there are no more objects pointing to that address, unlink it from the list
    if (NULL != curr && curr->count == 0)
    {
        assert(curr->count == 0);

        prev->next = curr->next;
    }
}

// clean up the object manager (before exiting)
void destroyPool();

// This function traverses the index and prints the info in each entry corresponding to a block of allocated memory.
// You should print the block's reference id, it's starting address, and it's size (in bytes).
void dumpPool()
{
    Node *curr = heapMemory->top;

    while (NULL != curr)
    {
        assert(NULL != curr);

        printf("Block ID: %lu\n", curr->referenceID);
        printf("Starting Address: %p\n", curr->startAddress);
        printf("Block Size: %lu bytes\n\n", curr->numBytes);
    }
}

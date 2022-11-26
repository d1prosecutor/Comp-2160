#include "ObjectManager.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/*********
 * STRUCTS
 *********/
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
    void *buffer1;
    void *buffer2;
    void *currentBuffer;
};
typedef struct MEMORYPOOL memPool;

/*******************
 * PRIVATE FUNCTIONS
 ******************/
static void compact();
static void copyMemBlock(void *emptyMemPool, Node *memBlock);

/******************
 * GLOBAL VARIABLES
 *****************/
static memPool *heapMemory = NULL;
static Ref numBytesCollected = 0;

/***********************
FUNCTION IMPLEMENTATIONS
************************/
void initPool()
{
    heapMemory = (memPool *)malloc(sizeof(memPool)); // might or might not use

    // Ensure that the space was actually allocated
    assert(NULL != heapMemory);

    // Initialize the member variables new object manager
    if (NULL != heapMemory)
    {
        heapMemory->top = NULL;
        heapMemory->numNodes = 1;
        heapMemory->buffer1 = malloc(MEMORY_SIZE);
        heapMemory->buffer2 = NULL;
        heapMemory->currentBuffer = heapMemory->buffer1;
        heapMemory->freePtr = heapMemory->currentBuffer;

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
        if ((char *)heapMemory->freePtr + size < (char *)heapMemory->currentBuffer + MEMORY_SIZE)
        {
            // If there is still memory avaiable to allocate
            assert((char *)heapMemory->freePtr + size < (char *)heapMemory->currentBuffer + MEMORY_SIZE);

            Node *curr = heapMemory->top;
            Node *prev = NULL;

            // Find the location to insert the new allocated memory
            while (NULL != curr)
            {
                prev = curr;
                curr = curr->next;
            }

            // Making a new Node for the linked list
            Node *newNode = (Node *)malloc(sizeof(Node));

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
                heapMemory->freePtr = (char *)heapMemory->freePtr + size;

                refResult = newNode->referenceID;

                // assert that the memory now contains at least one element
                assert(NULL != heapMemory->top);
            }
        }
        else
        {
            assert(heapMemory->freePtr + size >= (char *)heapMemory->currentBuffer + MEMORY_SIZE);

            // Collect garbage if there's not enough space to insert a new Item
            compact();
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

            // If there are no more objects pointing to that address, unlink it from the list
            if (curr->count == 0)
            {
                assert(curr->count == 0);

                // Save the number of bytes of the garbage node
                numBytesCollected += curr->numBytes;

                if (prev)
                {
                    // If the node to unlink is not at the head of the list
                    prev->next = curr->next;
                }
                else
                {
                    // If the node to unlink is the first element of the list
                    heapMemory->top = curr->next;
                }
            }
        }
        else
        {
            prev = curr;
            curr = curr->next;
        }
    }
}

// clean up the object manager (before exiting)
void destroyPool()
{
    if (NULL != heapMemory)
    {
        assert(heapMemory != NULL);

        Node *prev = NULL;
        while (NULL != heapMemory->top)
        {
            // Save a reference to each node in order to free it
            prev = heapMemory->top;

            // Move the top to the next Item thereby unlinking the previous item so it can be freed
            heapMemory->top = heapMemory->top->next;

            free(prev);
        }

        free(heapMemory);
    }
}

// This function traverses the index and prints the info in each entry corresponding to a block of allocated memory.
// You should print the block's reference id, it's starting address, and it's size (in bytes).
void dumpPool()
{
    Node *curr = heapMemory->top;

    printf("\n---BLOCK INFO---\n");
    while (NULL != curr)
    {
        assert(NULL != curr);

        printf("Block ID: %lu\n", curr->referenceID);
        printf("Starting Address: %p\n", curr->startAddress);
        printf("Block Size: %lu bytes\n\n", curr->numBytes);

        curr = curr->next;
    }
}

void compact()
{
    Node *curr = heapMemory->top;

    // Check to see which memory pool is filled and which one should be copied into
    char *emptyPool;
    if (heapMemory->currentBuffer == heapMemory->buffer1)
    {
        heapMemory->buffer2 = malloc(MEMORY_SIZE);
        emptyPool = (char *)heapMemory->buffer2;
    }
    else
    {
        heapMemory->buffer1 = malloc(MEMORY_SIZE);
        emptyPool = (char *)heapMemory->buffer1;
    }

    // Set the freePtr to point to the begining of the empty pool (next avaiable memory to insert into).
    heapMemory->freePtr = emptyPool;

    int numExistingObjects = 0;
    Ref numExistingBytes = 0;
    while (NULL != curr)
    {
        assert(NULL != curr);

        // Copy each (valid) block left in the linked list into the free buffer
        copyMemBlock(emptyPool, curr);

        // Save the details of the exisiting blocks
        numExistingObjects += curr->count;
        numExistingBytes += curr->numBytes;

        curr = curr->next;
    }

    // Free the previous active buffer thereby deleting all the contents (After copying over into the empty buffer).
    free(heapMemory->currentBuffer);

    // Set the Active buffer to the buffer which was just copied into
    heapMemory->currentBuffer = (void *)emptyPool;

    printf("\n---GARBAGE COLLECTION STATISTIC---\n");
    printf("Number of existing Objects: %d\n", numExistingObjects);
    printf("Current number of Bytes in Use: %lu\n", numExistingBytes);
    printf("Number of Bytes Collected: %lu bytes\n\n", numBytesCollected);

    // Reset the number of bytes collected
    numBytesCollected = 0;
}

/*
This method copies the contents of a memory block from a full buffer into an empty buffer
*/
void copyMemBlock(void *emptyMemPool, Node *memBlock)
{
    char *addressToCopy = (char *)memBlock->startAddress;
    char *tempEmpty = (char *)emptyMemPool;

    Ref index = 0;
    while (index < memBlock->numBytes)
    {
        tempEmpty[index] = addressToCopy[index];
        index++;
    }

    // Set the free pointer to point to the next available memory address to insert into
    heapMemory->freePtr = (char *)heapMemory->freePtr + index;
}

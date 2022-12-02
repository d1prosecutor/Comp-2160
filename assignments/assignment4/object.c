#include "ObjectManager.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/********************
 * STRUCTS
 *******************/
typedef struct NODE Node;
struct NODE
{
    Ref numBytes;
    Ref startAddress;
    Ref referenceID;
    Ref refCount;

    Node *next;
};

struct MEMORYPOOL
{
    Node *top;
    Ref numNodes;
    Ref freePtr;
    unsigned char *buffer1;
    unsigned char *buffer2;
    unsigned char *currentBuffer;
};
typedef struct MEMORYPOOL memPool;

/************************************************************
 * PRIVATE FUNCTIONS
 ***********************************************************/
static void compact();
static void copyMemBlock(void *emptyMemPool, Node *memBlock);
static void checkState();

/*******************************
 * GLOBAL VARIABLES
 *******************************/
static memPool heapMemory;
static Ref numBytesCollected = 0;

/***********************
FUNCTION IMPLEMENTATIONS
************************/
void initPool()
{
    // Initialize the member variables of the object manager
    heapMemory.top = NULL;
    heapMemory.numNodes = 1;
    heapMemory.buffer1 = (unsigned char *)malloc(MEMORY_SIZE);
    heapMemory.buffer2 = (unsigned char *)malloc(MEMORY_SIZE);
    heapMemory.currentBuffer = heapMemory.buffer1;
    heapMemory.freePtr = 0;

    checkState();
}

// This function trys to allocate a block of given size from our buffer.
// It will fire the garbage collector as required.
// We always assume that an insert always creates a new object...
// On success it returns the reference number for the block of memory allocated for the object.
// On failure it returns NULL_REF (0)
Ref insertObject(const int size)
{
    Ref refResult = NULL_REF;

    // Verify that the size is within the bounds
    assert(size > 0 && size < MEMORY_SIZE);

    if (size > 0 && size < MEMORY_SIZE)
    {
        // If there's no heap memory, compact first then try to allocate memory
        if (heapMemory.freePtr + size >= MEMORY_SIZE)
        {
            assert(heapMemory.freePtr + size >= MEMORY_SIZE);

            // Collect garbage if there's not enough space to insert a new Item
            compact();
            checkState();
        }

        // allocate memory in the heap if there's enough space
        if (heapMemory.freePtr + size < MEMORY_SIZE)
        {
            // If there is still memory avaiable to allocate
            assert(heapMemory.freePtr + size < MEMORY_SIZE);

            Node *curr = heapMemory.top;
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
                newNode->startAddress = heapMemory.freePtr;
                newNode->refCount = 1; // number of objects pointing to this address
                newNode->referenceID = heapMemory.numNodes++;
                newNode->next = NULL; // The next node will always be null since insertion is occuring at the end

                if (NULL == prev)
                {
                    // Insert at the top as the only element if the list is empty
                    heapMemory.top = newNode;

                    // assert that the memory was allocated
                    assert(heapMemory.top->numBytes == size);
                }
                else
                {
                    // Insert at the end of the list if there are existing elements
                    prev->next = newNode;

                    // assert that the memory was allocated
                    assert(prev->next->numBytes == size);
                }

                // Shift the position of the free memory pointer to point to the next available space
                heapMemory.freePtr += size;

                refResult = newNode->referenceID;

                // assert that the memory now contains at least one element
                assert(NULL != heapMemory.top);
            }
        }
    }
    checkState();

    return refResult;
}

// returns a pointer to the object being requested given by the reference id
void *retrieveObject(const Ref ref)
{
    int objectNotFound = 1; // boolean variable for searching for the object
    void *result = NULL;

    Node *curr = heapMemory.top;

    // assert that the reference passed in is valid
    assert(ref > 0);
    if (ref > 0)
    {
        assert(NULL != curr);
        while ((NULL != curr) && objectNotFound)
        {
            checkState();
            if (ref == curr->referenceID)
            {
                assert(ref == curr->referenceID);

                result = (void *)(&heapMemory.currentBuffer[curr->startAddress]);
                objectNotFound = 0;
            }
            curr = curr->next;
        }
    }
    return result;
}

// update our index to indicate that we have another reference to the given object
void addReference(const Ref ref)
{
    int objectNotFound = 1; // boolean variable for searching for the object

    Node *curr = heapMemory.top;

    // assert that the reference passed in is valid
    assert(ref > 0);
    if (ref > 0)
    {
        assert(NULL != curr);
        while ((NULL != curr) && objectNotFound)
        {
            checkState();
            if (ref == curr->referenceID)
            {
                assert(ref == curr->referenceID);

                curr->refCount++;
                objectNotFound = 0;
            }
            curr = curr->next;
        }
    }
}

// update our index to indicate that a reference is gone
void dropReference(const Ref ref)
{
    int objectNotFound = 1; // boolean variable for searching for the object

    Node *curr = heapMemory.top;
    Node *prev = NULL;

    // assert that the reference passed in is valid
    assert(ref > 0);
    if (ref > 0)
    {
        assert(NULL != curr);
        while ((NULL != curr) && objectNotFound)
        {
            checkState();
            if (ref == curr->referenceID)
            {
                assert(ref == curr->referenceID);

                curr->refCount--;
                objectNotFound = 0;

                // If there are no more objects pointing to that address, unlink it from the list
                if (curr->refCount == 0)
                {
                    assert(curr->refCount == 0);

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
                        heapMemory.top = curr->next;
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
}

// clean up the object manager (before exiting)
void destroyPool()
{
    // Free all the Nodes in the linked list
    Node *prevNode = NULL;
    while (NULL != heapMemory.top)
    {
        // Save a reference to each node in order to free it
        prevNode = heapMemory.top;

        // Move the top to the next Item thereby unlinking the previous item so it can be freed
        heapMemory.top = heapMemory.top->next;

        free(prevNode);
    }

    // Free the two buffers and set the current buffer to NULL
    free(heapMemory.buffer1);
    free(heapMemory.buffer2);

    // Reset the global variables
    numBytesCollected = 0;

    heapMemory.currentBuffer = NULL;
}

// This function traverses the index and prints the info in each entry corresponding to a block of allocated memory.
// You should print the block's reference id, it's starting address, and it's size (in bytes).
void dumpPool()
{
    Node *curr = heapMemory.top;

    checkState();

    printf("\n------ BLOCK INFO ------\n");
    while (NULL != curr)
    {
        assert(NULL != curr);

        printf("Block ID: %lu\n", curr->referenceID);
        printf("Starting Address: %lu\n", curr->startAddress);
        printf("Block Size: %lu bytes\n", curr->numBytes);

        curr = curr->next;
    }
    printf("------------------------\n\n");
}

static void compact()
{
    Node *currNode = heapMemory.top;

    // Check to see which memory pool is filled and which one should be copied into
    unsigned char *emptyPool;

    if (heapMemory.currentBuffer == heapMemory.buffer1)
    {
        emptyPool = heapMemory.buffer2;
    }
    else
    {
        emptyPool = heapMemory.buffer1;
    }

    // Set the freePtr to point to the begining of the empty pool (next avaiable memory to insert into).
    heapMemory.freePtr = 0;

    int numExistingObjects = 0;
    Ref numExistingBytes = 0;

    checkState();

    while (NULL != currNode)
    {
        assert(NULL != currNode);

        // Copy each (valid) block left in the linked list into the free buffer
        copyMemBlock(emptyPool, currNode);

        // Save the details of the exisiting blocks
        numExistingObjects += currNode->refCount;
        numExistingBytes += currNode->numBytes;

        currNode = currNode->next;
    }

    // Set the Active buffer to the buffer which was just copied into
    heapMemory.currentBuffer = emptyPool;

    printf("\n--------------- GARBAGE COLLECTION STATISTIC ----------------\n");
    printf("Number of existing Objects after Garbage Collection: %d objects\n", numExistingObjects);
    printf("Current number of Bytes in Use: %lu bytes\n", numExistingBytes);
    printf("Number of Bytes Collected: %lu bytes\n", numBytesCollected);
    printf("Number of Bytes Available/Free: %lu bytes\n", MEMORY_SIZE - numExistingBytes);
    printf("-------------------------------------------------------------\n\n");

    // Reset the number of bytes collected
    numBytesCollected = 0;

    checkState();
}

/*
This method copies the contents of a memory block from a full buffer into an empty buffer
*/
static void copyMemBlock(void *emptyMemPool, Node *memBlock)
{
    unsigned char *addressToCopy = &(heapMemory.currentBuffer[memBlock->startAddress]);
    unsigned char *tempEmptyPool = (unsigned char *)emptyMemPool;

    Ref index = 0;
    while (index < memBlock->numBytes)
    {
        tempEmptyPool[index] = addressToCopy[index];
        index++;
    }

    // Update the start address of each node
    memBlock->startAddress = heapMemory.freePtr;

    // Set the free pointer to point to the next available memory address to insert into
    heapMemory.freePtr = heapMemory.freePtr + index;

    checkState();
}

static void checkState()
{
    // Verify that the free pointer is still within the size limit
    assert(heapMemory.freePtr >= 0 && heapMemory.freePtr < MEMORY_SIZE);

    Node *temp = heapMemory.top;
    Ref currNumBytes = 0;
    while (NULL != temp)
    {
        // Verify that the every Node in the linked list is still being used(pointed to)
        assert(temp->refCount > 0);

        currNumBytes += temp->numBytes;
        temp = temp->next;
    }

    // assert that the number of bytes being used from the memory pool is within the valid range
    assert(currNumBytes >= 0 && currNumBytes < MEMORY_SIZE);

    // assert that the current buffer is always pointing to one of the two available buffers
    assert(heapMemory.currentBuffer == heapMemory.buffer1 || heapMemory.currentBuffer == heapMemory.buffer2);
}
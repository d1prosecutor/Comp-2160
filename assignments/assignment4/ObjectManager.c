/***************************************************************************************
 * NAME: Chukwunaza Chukwuocha
 * STUDENT NUMBER: 7928676
 * COURSE: COMP 2160, SECTION: A01
 * INSTRUCTOR: Saulo dos Santos
 * ASSIGNMENT: Assignment 4
 *
 * REMARKS: Implements a memory pool which mimics the heap memory in languages like Java
 ***************************************************************************************/

#include "ObjectManager.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
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
    uint8_t *buffer1;
    uint8_t *buffer2;
    uint8_t *currentBuffer;
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
    heapMemory = (memPool){
        .top = NULL,
        .numNodes = 1,
        .freePtr = 0,
        .buffer1 = (uint8_t *)malloc(MEMORY_SIZE),
        .buffer2 = (uint8_t *)malloc(MEMORY_SIZE),
    };

    // Initialize the current buffer to the first buffer
    heapMemory.currentBuffer = heapMemory.buffer1,

    checkState();
}

/******************************************************************************
 * insertObject
 *
 * PURPOSE: This function trys to allocate a block of given size from my buffer.
 *          It will fire the garbage collector as required.


 * INPUT PARAMETERS:
 *      size: The size of bytes to be allocated
 *
 *  OUTPUT PARAMETERS:
 *      refResult: The reference number for the memory block allocated
 *******************************************************************************/
Ref insertObject(const int size)
{
    // Verify that the size is within the bounds
    assert(size > 0 && size < MEMORY_SIZE);

    Ref refResult = NULL_REF;

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

/************************************************************************************
 * retrieveObject
 *
 * PURPOSE: Returns a pointer to the object being requested given by the reference id
 *
 * INPUT PARAMETERS:
 *      ref: the reference ID for the object being requested
 *
 *  OUTPUT PARAMETERS:
 *      result: a pointer to the object being requested given by the reference id
 ************************************************************************************/
void *retrieveObject(const Ref ref)
{
    // assert that the reference passed in is valid
    assert(ref > 0);

    int objectNotFound = 1; // boolean variable for searching for the object
    void *result = NULL;

    Node *curr = heapMemory.top;

    if (ref > 0)
    {
        assert(NULL != curr);
        while ((NULL != curr) && objectNotFound)
        {
            checkState();
            if (ref == curr->referenceID)
            {
                assert(ref == curr->referenceID);

                result = (void *)&(heapMemory.currentBuffer[curr->startAddress]);
                objectNotFound = 0;
            }
            curr = curr->next;
        }
        return result;
    }
    else
    {
        printf("The reference ID passed in is invalid (The object with ID:%lu does not exist).\n", ref);
        exit(1);
    }
}

/************************************************************************
 * addReference
 *
 * PURPOSE: update the reference count to indicate that another reference
 *          was added to the given object
 *
 * INPUT PARAMETERS:
 *      ref: the reference ID for the object being requested
 ************************************************************************/
void addReference(const Ref ref)
{
    // assert that the reference passed in is valid
    assert(ref > 0);

    int objectNotFound = 1; // boolean variable for searching for the object

    if (ref > 0)
    {
        Node *curr = heapMemory.top;
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

/******************************************************************
 * dropReference
 *
 * PURPOSE: update the reference count to indicate that a reference
 *          was removed from the given object
 *
 * INPUT PARAMETERS:
 *      ref: the reference ID for the object being requested
 ******************************************************************/
void dropReference(const Ref ref)
{
    // assert that the reference passed in is valid
    assert(ref > 0);

    int objectNotFound = 1; // boolean variable for searching for the object

    if (ref > 0)
    {
        Node *curr = heapMemory.top;
        Node *prev = NULL;

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

/*******************************************************
 * destroyPool
 *
 * PURPOSE: clean up the object manager (before exiting)
 *
 ******************************************************/
void destroyPool()
{
    assert(NULL != heapMemory.top);
    // Free all the Nodes in the linked list
    Node *prevNode = NULL;
    if (NULL != heapMemory.top)
    {
        while (NULL != heapMemory.top)
        {
            // Save a reference to each node in order to free it
            prevNode = heapMemory.top;

            // Move the top to the next Item thereby unlinking the previous item so it can be freed
            heapMemory.top = heapMemory.top->next;

            free(prevNode);
        }
    }
    assert(NULL == heapMemory.top);

    // Free the two buffers and set the current buffer to NULL
    free(heapMemory.buffer1);
    free(heapMemory.buffer2);

    // Reset the global variables
    numBytesCollected = 0;

    heapMemory.buffer1 = NULL;
    heapMemory.buffer2 = NULL;

    assert(NULL == heapMemory.buffer1);
    assert(NULL == heapMemory.buffer2);
}

/******************************************************************************
 * dumpPool
 *
 * PURPOSE: This function traverses the index and prints the info in each entry
 *          corresponding to a block of allocated memory.
 *
 ******************************************************************************/
// You should print the block's reference id, it's starting address, and it's size (in bytes).
void dumpPool()
{
    Node *curr = heapMemory.top;
    assert(NULL != curr);

    checkState();

    printf("\n------ BLOCK INFO ------\n");

    while (NULL != curr)
    {
        assert(NULL != curr);

        printf("Block ID: %lu\n", curr->referenceID);
        printf("Starting Address: %lu\n", curr->startAddress);
        printf("Block Size: %lu bytes\n\n", curr->numBytes);

        curr = curr->next;
    }
    printf("------------------------\n\n");
}

/***********************************************************************************
 * compact
 *
 * PURPOSE: This function copies over the objects still in use into the empty buffer,
 *          effectively freeing the memory taken up by the objects no longer in use
 *
 ***********************************************************************************/

static void compact()
{
    Node *currNode = heapMemory.top;
    Ref prevNumBytes = heapMemory.freePtr;

    // Check to see which memory pool is filled and which one should be copied into
    uint8_t *emptyPool;

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

    checkState();

    while (NULL != currNode)
    {
        assert(NULL != currNode);

        // Copy each (valid) block left in the linked list into the free buffer
        copyMemBlock(emptyPool, currNode);

        // Save the details of the exisiting blocks
        numExistingObjects += currNode->refCount;

        currNode = currNode->next;
    }

    // Set the Active buffer to the buffer which was just copied into
    heapMemory.currentBuffer = emptyPool;

    printf("\n--------------- GARBAGE COLLECTION STATISTIC ----------------\n");
    printf("Number of existing Objects after Garbage Collection: %d objects\n", numExistingObjects);
    printf("Current number of Bytes in Use: %lu bytes\n", heapMemory.freePtr);
    printf("Number of Bytes Collected: %lu bytes\n", prevNumBytes - heapMemory.freePtr);
    printf("Number of Bytes Available/Free: %lu bytes\n", MEMORY_SIZE - heapMemory.freePtr);
    printf("-------------------------------------------------------------\n\n");

    // Reset the number of bytes collected
    numBytesCollected = 0;

    checkState();
}

/***************************************************************************************
 * copyMemBlock
 *
 * PURPOSE: This helper function copies a the contents of a single memory block from one
 *          buffer to another.
 *
 ***************************************************************************************/
/*
This method copies the contents of a memory block from a full buffer into an empty buffer
*/
static void copyMemBlock(void *emptyMemPool, Node *memBlock)
{
    uint8_t *addressToCopy = &(heapMemory.currentBuffer[memBlock->startAddress]);
    uint8_t *tempEmptyPool = (uint8_t *)emptyMemPool;

    // Update the start address of each node
    memBlock->startAddress = heapMemory.freePtr;

    Ref index = 0;
    while (index < memBlock->numBytes)
    {
        tempEmptyPool[heapMemory.freePtr++] = addressToCopy[index];
        index++;
    }

    checkState();
}

/******************************************************************************************
 * checkState
 *
 * PURPOSE: This is the invariant on the object manager that checks that the state is valid
 *
 ******************************************************************************************/
static void checkState()
{
    // assert that the buffers are still valid
    assert(NULL != heapMemory.buffer1 && NULL != heapMemory.buffer2);

    // assert that the current buffer is always pointing to one of the two available buffers
    assert(heapMemory.currentBuffer == heapMemory.buffer1 || heapMemory.currentBuffer == heapMemory.buffer2);

    // Verify that the free pointer is still within the size limit
    assert(heapMemory.freePtr >= 0 && heapMemory.freePtr < MEMORY_SIZE);

    // Node *temp = heapMemory.top;

    // Uncomment if assertions are enabled
    // Ref currNumBytes = 0;
    // while (NULL != temp)
    // {
    //     // Verify that the every Node in the linked list is still being used(pointed to)
    //     // and has a valid allocated memory
    //     assert(temp->refCount > 0);
    //     assert(temp->numBytes >= 0 && temp->numBytes < MEMORY_SIZE);

    //     // Uncomment if assertions are enabled
    //     // currNumBytes += temp->numBytes;

    //     temp = temp->next;
    // }

    /*
     assert that the number of bytes being used from the memory pool is within the valid range
     commented out because the variable 'currNumBytes' will give a warning: "variable set but never used"
     should be uncommented only when assertions are on so as not to get the warning
     */
    // assert(currNumBytes >= 0 && currNumBytes < MEMORY_SIZE);
}
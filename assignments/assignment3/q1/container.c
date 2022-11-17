/***************************************************************************
 * NAME: Chukwunaza Chukwuocha
 * STUDENT NUMBER: 7928676
 * COURSE: COMP 2160, SECTION: A01
 * INSTRUCTOR: Saulo dos Santos
 * ASSIGNMENT: assignment 3
 *
 * REMARKS: Implements The container ADT to create a linked list of strings
 **************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "container.h"

//--------------------------------------------------------------
// TYPES
//--------------------------------------------------------------

// The struct which acts as the node of the container
typedef struct NODE Node;
struct NODE
{
    char *data;
    Node *next;
};

struct CONTAINER
{
    Node *top;
    size_t size;
    Node *iterator;
};

//--------------------------------------------------------------
// INVARIANT PROTOTYPE
//--------------------------------------------------------------

void checkList(Container *, Node *);

//----------------------------------------------------------------
// FUNCTIONS
//----------------------------------------------------------------

/******************************************************************
 *  createContainer
 *
 *  PURPOSE: Creates the container for the linked list of Strings
 *
 *  OUTPUT PARAMETERS:
 *      newContainer: The newly created Container for a linked list
 ******************************************************************/
Container *createContainer()
{
    Container *newContainer = malloc(sizeof(Container));

    // If the space was successfully allocated, then initailize the variables of the container
    if (NULL != newContainer)
    {
        newContainer->top = NULL;
        newContainer->size = 0;
        newContainer->iterator = NULL;
    }
    else
    {
        printf("No memory available\n");
        exit(1);
    }

    // Verify that the container was successfully created
    assert(newContainer != NULL);

    return newContainer;
}

/********************************************************************************
 * destroyContainer
 *
 * PURPOSE: Clears the contents of the container and also destroys the Container
 *
 * INPUT PARAMETERS:
 *      tempContainer: The Container to be destroyed
 *
 *  OUTPUT PARAMETERS:
 *      destroyed: Returns if the container was successfully destroyed or not
 *******************************************************************************/
Boolean destroyContainer(Container **tempContainer)
{
    Boolean destroyed = false;

    // Uses the clear method to first clear the contents of the container
    // If the container is valid then it will be destroyed after the contents have been cleared
    if (clear(*tempContainer))
    {
        free(*tempContainer);
        *tempContainer = NULL;

        // Verify that the container was successfully destroyed
        assert(*tempContainer == NULL);

        destroyed = true;
    }

    return destroyed;
}

/*************************************************************************
 * insertItem
 *
 * PURPOSE: inserts new item into the linkedList
 *
 * INPUT PARAMETERS:
 *      tempContainer: The Container to be inserted into
 *      newString: The data to be inserted into the Container
 *
 *  OUTPUT PARAMETERS:
 *      inserted: Returns if the new item was inserted successfully or not
 * ***********************************************************************/
Boolean insertItem(Container *tempContainer, char *newString)
{
    assert(NULL != tempContainer);
    assert(NULL != newString);

    Boolean inserted = false;

    Node *newNode = malloc(sizeof(Node));

    if (NULL != newNode)
    {
        newNode->data = newString;

        // Check that the newly created Node is valid
        checkList(tempContainer, newNode);

        if (NULL != tempContainer)
        {
            newNode->next = tempContainer->top;

            tempContainer->top = newNode;

            inserted = true;

            // Update the size of the container
            tempContainer->size++;

            // Validate that the size of the container is still valid
            assert(tempContainer->size >= 0);

            // assert that the item was inserted
            assert(contains(tempContainer, newString));

            // Invalidate the iterator because a new item has been inserted
            tempContainer->iterator = NULL;
        }
        else
        {
            // if the container is null and the newItem cannot be inserted,
            // free the space allocated for that new item
            free(newNode);
        }

        return inserted;
    }
    else
    {
        printf("No memory available\n");
        exit(1);
    }
}

/*******************************************************************
 * deleteItem
 *
 * PURPOSE: deletes a particular item from the linkedList
 *
 * INPUT PARAMETERS:
 *      tempContainer: The Container to be deleted from
 *      deleteString: The Item to be deleted from the Container
 *
 *  OUTPUT PARAMETERS:
 *      deleted: Returns if the item was deleted successfully or not
 * ****************************************************************/
Boolean deleteItem(Container *tempContainer, char *deleteString)
{
    assert(NULL != tempContainer);
    assert(NULL != deleteString);

    Boolean deleted = false;

    if (NULL != tempContainer)
    {
        Node *prev = NULL;
        Node *curr = tempContainer->top;

        // Search for the item in the linked list
        while (NULL != curr && strcmp(deleteString, curr->data) != 0)
        {
            checkList(tempContainer, curr);

            prev = curr;
            curr = curr->next;
        }

        // if the item was found, unlink it from the list
        if (NULL != curr)
        {
            // if the item is not the first item
            if (NULL != prev)
            {
                prev->next = curr->next;
            }
            else
            {
                // If the item is the first in the list
                tempContainer->top = curr->next;
            }

            // update the size of the container
            tempContainer->size--;

            deleted = true;

            // Validate that the size of the container is still valid
            assert(tempContainer->size >= 0);

            // clear the contents of the node deleted
            free(curr);

            // If the item was found and deleted, invalidate the iterator
            tempContainer->iterator = NULL;
        }
    }

    // Verify that the item is no longer (or was not) in the list
    assert(!contains(tempContainer, deleteString));
    assert(tempContainer->size >= 0);

    return deleted;
}

/***********************************************************************
 * find an item in the linkedList that has given item
 *  return true if it is found
 * stop the program when trying to find a null
 * insertItem
 *
 * PURPOSE: Checks if the Container (Linked list) contains a given item
 *
 * INPUT PARAMETERS:
 *      tempContainer: The Container to be searched
 *      keyString: The item being searched for
 *
 *  OUTPUT PARAMETERS:
 *      inserted: Returns if the item was found or not
 * ***********************************************************************/

Boolean contains(Container *tempContainer, char *keyString)
{
    assert(NULL != keyString);
    assert(NULL != tempContainer);

    Boolean found = false;

    // if the Container is not empty, loop through and look for the key string
    if (NULL != tempContainer)
    {
        Node *curr = tempContainer->top;
        while (NULL != curr && found == false)
        {
            // Verifies that the container and the current Item are still valid

            // Verifies that the container and the current Item are still valid
            checkList(tempContainer, curr);

            if (strcmp(curr->data, keyString) == 0)
            {
                found = true;
            }

            curr = curr->next;
        }
    }
    return found;
}

/******************************************************************************************
 * firstItem
 *
 * PURPOSE: starts iterating through the linked list and returns the first item in the list
 *
 * INPUT PARAMETERS:
 *      tempContainer: The Container to be iterated over
 *
 *  OUTPUT PARAMETERS:
 *      char *: The first item in the linked list
 ******************************************************************************************/
char *firstItem(Container *tempContainer)
{
    char *result = NULL;

    if (NULL != tempContainer)
    {
        assert(NULL != tempContainer);

        if (NULL != tempContainer->top)
        {
            assert(NULL != tempContainer->top);

            // Sets/Resets the iterator to the first item in the list(starts iterating through the list)
            tempContainer->iterator = tempContainer->top;

            // Invariant on the iterator which is currently the first item in the list
            checkList(tempContainer, tempContainer->iterator);

            result = tempContainer->iterator->data;
        }
    }

    return result;
}

/*********************************************************************************************
 * nextItem
 *
 * PURPOSE: Goes to the next item in the linkedList and returns its data (or null if the next
 *          item is out of bounds or the list is empty)
 *
 * INPUT PARAMETERS:
 *      tempContainer: The Container to be iterated over
 *
 *  OUTPUT PARAMETERS:
 *      char *: The next item in the linked list
 *********************************************************************************************/

char *nextItem(Container *tempContainer)
{
    char *result = NULL;

    if (NULL != tempContainer)
    {
        assert(NULL != tempContainer);

        // If the iterator's position is valid (within the size of the list)
        if (NULL != tempContainer->iterator)
        {
            // Continues iterating through the list
            tempContainer->iterator = tempContainer->iterator->next;

            // Invariant on the iterator which is currently the next item in the list
            checkList(tempContainer, tempContainer->iterator);

            // Update the result to the data of the next item if the iterator is still within the list,
            // otherwise the iterator has gone through all the items in the list and the result should be null
            if (NULL != tempContainer->iterator)
            {
                result = tempContainer->iterator->data;
            }
        }
    }

    return result;
}

/****************************************************************
 * size
 *
 * PURPOSE: return size of the linkedList
 *
 * INPUT PARAMETERS:
 *      tempContainer: The Container whose size is to be returned
 *
 *  OUTPUT PARAMETERS:
 *      size: The number of elements in the linkedList
 * **************************************************************/
int size(Container *tempContainer)
{
    // size is represented as -1 when container is null;
    int size = -1;

    // ensures the list is initialized and the size is valid
    assert(tempContainer != NULL);
    assert(tempContainer->size >= 0);

    if (NULL != tempContainer)
    {
        size = tempContainer->size;
    }

    return size;
}

/************************************************************************************
 * clear
 *
 * PURPOSE:  delete every items inside linkedList (but not the container itself)
 *           return true if the linkedList is cleared, false when the initial linkedList is null
 *
 * INPUT PARAMETERS:
 *      tempContainer: The Container whose contents are to be cleared
 *
 *  OUTPUT PARAMETERS:
 *      cleared: Returns if the the contents of the linked list was successfully cleared
 ************************************************************************************/
Boolean clear(Container *tempContainer)
{
    Boolean cleared = false;

    // If the container is initialized, iterate through and free all items
    if (NULL != tempContainer)
    {
        assert(NULL != tempContainer);

        Node *prev = NULL;
        while (NULL != tempContainer->top)
        {
            prev = tempContainer->top;

            // Verifies that the container and the current Item are valid
            checkList(tempContainer, prev);

            // Move to the next Item thereby unlinking the previous item so it can be freed
            tempContainer->top = tempContainer->top->next;

            free(prev);
        }

        // Set the iterator to null and the size to 0 because the list is empty
        tempContainer->iterator = NULL;
        tempContainer->size = 0;

        // Validate that the container is not destroyed
        assert(NULL != tempContainer);

        // Verifies the list has been cleared
        cleared = true;
    }
    else
    {
        // return false if the container is not initialized
        assert(NULL == tempContainer);
        cleared = false;
    }

    return cleared;
}

/************************************************************************************************
 * checkList
 *
 * PURPOSE: Invariant on the Container, the List Nodes and the data of the Nodes
 *            - Checks if all these items are valid
 *
 * INPUT PARAMETERS:
 *      tempContainer: The Container and the Node (containing the data) to be verified to be valid
 ************************************************************************************************/
void checkList(Container *tempContainer, Node *currNode)
{
    // Verify that the container is valid
    assert(NULL != tempContainer);

    // Check that the node of the linked list is valid
    assert(NULL != currNode);

    // Check that the data of the node is valid
    assert(NULL != currNode->data);
}

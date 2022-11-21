/**************************************************************
 * NAME: Chukwunaza Chukwuocha
 * STUDENT NUMBER: 7928676
 * COURSE: COMP 2160, SECTION: A01
 * INSTRUCTOR: Saulo dos Santos
 * ASSIGNMENT: Assignment 3, Question 1
 *
 * REMARKS: The interface for the Container ADT
 *************************************************************/

#ifndef CONTAINER_H
#define CONTAINER_H

//--------------------------------------------------------------
// TYPES
//--------------------------------------------------------------
typedef struct CONTAINER Container;
typedef enum BOOL
{
    false,
    true
} Boolean;

//--------------------------------------------------------------
// FUNTION PROTOTYPES
//--------------------------------------------------------------

// Container constructor. Returns NULL if memory could not be allocated for the Container,
// else it returns a pointer to the newly created Container.
Container *createContainer();

// Container destructor. Returns NULL false if the container does not exist.
Boolean destroyContainer(Container **);

// Insert an item into a container. Returns true if the item was added to the Container.
Boolean insertItem(Container *, char *);

// Delete a given item, if it appears in the Container. Returns true if the item was removed from the Container.
Boolean deleteItem(Container *, char *);

// Delete all items from the Container, but does not destroy the container.
// Returns true if the list is empty (either before or after calling the function).
Boolean clear(Container *);

// Return the first item in the list. Returns NULL if the Container is empty or Container doesn't exist.
char *firstItem(Container *);

// Return the next item in the list. Returns NULL if the container doesn't exist, is empty,
// or the entire Container has been iterated over.
char *nextItem(Container *);

// Returns true if the container exists and contains the given item, false otherwise.
Boolean contains(Container *, char *);

// Returns the size of the container (if it exists), or -1 if the container doesn't exist.
int size(Container *);

#endif
/*
 * Container.h
 * COMP 2160 Programming Practices
 * Assignment 3
 *
 * Header file for a Container
 */
#ifndef __CONTAINER_H
#define __CONTAINER_H
//-------------------------------------------------------------------------------------
// CONSTANTS and TYPES
//-------------------------------------------------------------------------------------

typedef enum BOOL { false, true } Boolean;

typedef struct CONTAINER Container;

//-------------------------------------------------------------------------------------
// PROTOTYPES
//-------------------------------------------------------------------------------------

// create a new empty Container and return a pointer to it
Container *createContainer();

// deallocate and destroy the Container so that we clear all memory
Container *destroyContainer( Container * );

// add an element to the beginning of the linked list
Boolean insert( Container *, char * );

// remove an element with the given string
Boolean delete( Container *, char * );

// clear all entries from the container, but don't destroy it
void clear( Container * );

// starts a list traversal by getting the data at head
char * firstItem( Container * );

// gets the data at the current traversal node and increments the traversal
char * nextItem( Container * );

// does the container contain this item?
Boolean contains( Container *, char * );

// how many items are in this container?
int size( Container * );

#endif

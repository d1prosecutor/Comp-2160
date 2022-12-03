/*
 * Container.h
 * COMP 2160 Programming Practices
 * Assignment 3
 *
 * Implementation file for a Container
 * Implemented as an unsorted linked list
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "container.h"

//-------------------------------------------------------------------------------------
// CONSTANTS and TYPES
//-------------------------------------------------------------------------------------

typedef struct NODE{
  char *item;
  struct NODE *next;
} Node;

// Container definition
struct CONTAINER{
  Node *head;

  // used to track where we are for the list traversal methods
  Node *traverseNode;
  
  // used to track testing values
  int numNodes;
  int numTraversals;  
};

//-------------------------------------------------------------------------------------
// FUNCTIONS
//-------------------------------------------------------------------------------------

static void validateContainer( Container *theContainer ){
  assert( theContainer != NULL );
  
  if ( theContainer->numNodes == 0 )
    assert( theContainer->head == NULL );
  else if ( theContainer->numNodes == 1 )
    assert( theContainer->head->next == NULL );
  else // numNodes > 1
    assert( theContainer->head != NULL && theContainer->head->next != NULL );
  // how far should we really go???
}// validateContainer

// make an empty container that we can start working with
Container * createContainer(){
  Container *newContainer = NULL;
  
  newContainer = (Container *)malloc( sizeof(Container) );
  assert( newContainer != NULL );
  
  if ( newContainer ){
    // make sure all of our internals are initialized
    newContainer->head = NULL;
    newContainer->traverseNode = NULL;
    newContainer->numNodes = 0;
    newContainer->numTraversals = 0;
  }
  
  return newContainer;
}// createContainer

// deallocate and destroy the Container so that we clear all memory
Container *destroyContainer( Container *theContainer ){
  assert( theContainer != NULL );
  if ( theContainer != NULL )
  {
    clear( theContainer );
    free( theContainer );
    theContainer = NULL;
  }
  
  return theContainer;
}// destroyContainer

// clear all entries from the container, but don't destroy it
void clear( Container *theContainer ){
  Node *curr = NULL;
  
  assert( theContainer != NULL );
  if ( theContainer != NULL )
  {
    curr = theContainer->head;
    
    while ( theContainer->head != NULL )
    {
      theContainer->head = theContainer->head->next;
      free( curr->item );
      free( curr );
      curr = theContainer->head;
      
      theContainer->numNodes--;
    }
    
    validateContainer( theContainer );
  }
}// clear 


// add an element to the beginning of the linked list
Boolean insert( Container *intoContainer, char *new_string ){
  Boolean rc = false;
  Node *newNode = NULL;
  
  assert( intoContainer != NULL );
  if ( intoContainer != NULL ){
    assert( new_string != NULL );
    if ( new_string ){
      newNode = (Node *)malloc( sizeof( Node ) );
      assert( newNode != NULL );
      
      if ( newNode ){
        // note that we need to have space for the string as well!
        newNode->item = strdup(new_string);
        assert( newNode->item != NULL );
        
        if ( newNode->item ){
          newNode->next = intoContainer->head;
          intoContainer->head = newNode;        
          intoContainer->numNodes++;
          
          rc = true;
          
          // make sure the list is scontainer
          validateContainer( intoContainer );
        } else
          free( newNode );
      }// if ( newNode )
    }// if ( new_string )
  }// if ( intoContainer != NULL )
  
  return rc;
}// insert

// remove an element with the given string
Boolean delete( Container *fromContainer, char *target ){
  Boolean deleted = false;
  Node *curr = NULL;
  Node *prev = NULL;
  
  assert( fromContainer != NULL );
  if ( fromContainer != NULL ){
    curr = fromContainer->head;
    
    assert( target != NULL );
    if ( target != NULL  ){
      assert( (curr == NULL) || (curr->item != NULL) );
      while ( curr != NULL && strcmp( target, curr->item ) != 0 ){
        prev = curr;
        curr = curr->next;
      }// while
      
      if ( curr != NULL ){
        if ( prev != NULL )
          prev->next = curr->next;
        else
          fromContainer->head = curr->next;
        
        free( curr->item );
        free( curr );
        deleted = true;
        fromContainer->numNodes--;
        
        // make sure the list is scontainer
        validateContainer( fromContainer );
      }// if ( curr != NULL )
    }// if ( target != NULL  )
  }// if ( fromContainer != NULL )
  
  return deleted;
}// delete

// starts a list traversal by getting the data at head
char * firstItem( Container *inContainer ){
  char *the_item = NULL;
  
  assert( inContainer != NULL );
  if ( inContainer != NULL )  {
    if ( inContainer->head != NULL ){
      inContainer->traverseNode = inContainer->head;
      the_item = inContainer->head->item;
      assert( the_item != NULL );
      
      inContainer->numTraversals = 1;
      // make sure we're still in our list...
      assert( inContainer->numTraversals <= inContainer->numNodes );
    }//  if ( inContainer->head != NULL )
  }// if ( inContainer != NULL )
  
  // this isn't the safest (caller can modify the string) but we don't have to worry about extra memory mgmt...
  return the_item;
}// firstItem


// increments the traversal and gets the data at the current traversal node 
char *nextItem( Container *inContainer ){
  char *the_item = NULL;
  
  assert( inContainer != NULL );
  if ( inContainer != NULL ){
		// try to advance the traversal first
		if ( inContainer->traverseNode != NULL ) {
			inContainer->traverseNode = inContainer->traverseNode->next;
			inContainer->numTraversals++;
		}
		// if we are still in the list, get the item
		if ( inContainer->traverseNode != NULL ) {
			the_item = inContainer->traverseNode->item;
			assert( the_item != NULL );
			// make sure we're still in our list...
			assert( inContainer->numTraversals <= inContainer->numNodes );
		}
    
  }// if ( inContainer != NULL )
  // this isn't the safest (caller can modify the string), 
  // but we don't have to worry about extra memory mgmt...
  return the_item;
}// nextItem

// tells us whether or not the given string is in the list
Boolean contains( Container *inContainer, char *target ){
  Boolean found = false;
  Node *curr = NULL;
  int search_count = 0;     // how far in the list do we go?
  
  assert( inContainer != NULL );
  if ( inContainer != NULL ){
    curr = inContainer->head;
    
    assert( target != NULL );
    if ( target != NULL ){
      while ( curr != NULL && !found ){
        assert( curr->item != NULL );
        if ( strcmp( target, curr->item ) == 0 ){
          found = true;
          // make sure we're still in our list...
          assert( search_count <= inContainer->numNodes );
        } else {
          curr = curr->next;
          search_count++;
        }// if/else
      }// while
    }// if ( target != NULL )
  }// if ( inContainer != NULL )
  
  // if it's not found then we should be at the end of the list
  assert( found || (search_count == inContainer->numNodes) );
  
  return found;
}// search

int size( Container *theContainer ){
    int nodes = -1;
    validateContainer( theContainer );
    nodes = theContainer->numNodes;
    validateContainer( theContainer );
    return nodes;
}

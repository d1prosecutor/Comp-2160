/*
 * main.c
 * COMP 2160 Programming Practices
 *
 * Assignment 3 sample solution
 */

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "container.h"

void testEmpty();
void testAdd();
void testRemove();
void testLeaks();
void initSuite();
void cleanSuite();
void testFound( int size, char *strings[] );
void testNotFound( int size, char *strings[] );
void testSize();

static int testsPassed;
static int testsFailed;
static int currentSize;

static Container *testContainer = NULL;

int main( int argc, char *argv[] )
{
  initSuite();
  
  printf( "Initiating tests.\n\n" );
  testEmpty();
  testAdd();
  testRemove();
  testLeaks();
  
  cleanSuite();
  printf( "\nTests completed successfully.\n" );
  
  return EXIT_SUCCESS;
}

// The suite setup function.

void initSuite()
{
  testsPassed = 0;
  testsFailed = 0;
  currentSize = 0;
  
  testContainer = createContainer();
}

// Test boundary conditions on an empty container

void testEmpty()
{
  char *emptyStrings[1] = {"Nothing there"};
  
  testNotFound( 1, emptyStrings );
  delete( testContainer, "No Nodes" );
  testSize();
}

// Test adding elements to container

void testAdd()
{
#define ADD_TEST_SIZE 4
  char *inStrings[ADD_TEST_SIZE] = {"Node4", "Node3", "Node2", "Node1"};
  char *notStrings[1] = {"Not"};
  int i;
  
  printf( "\nTesting insertions:\n" );
  for ( i=0; i<ADD_TEST_SIZE ; i++ )
  {
    printf( "\"%s\"\n", inStrings[i] );
    insert( testContainer, inStrings[i] );
    currentSize++;
  }
  
  testFound( ADD_TEST_SIZE, inStrings );
  testNotFound( 1, notStrings );
  testSize();
}

// Test removing elements from container

void testRemove()
{
#define REMOVE_TEST_SIZE 2
  char *outStrings[REMOVE_TEST_SIZE] = {"Node4", "Node1"};  // delete first and last in the container
  char *newStrings[REMOVE_TEST_SIZE] = {"Node3", "Node2"};
  int i;
  
  printf( "\nTesting deletions:\n" );
  for ( i=0 ; i<REMOVE_TEST_SIZE ; i++ )
  {
    printf( "\"%s\"\n", outStrings[i] );
    delete( testContainer, outStrings[i] );
    currentSize--;
  }
  
  testFound( REMOVE_TEST_SIZE, newStrings );
  testNotFound( REMOVE_TEST_SIZE, outStrings );
  testSize();
}

// do a bunch of inserts and deletes to see if there's a leak

void testLeaks()
{
  int i;
  char *leakStrings[1] = { "hi" };
  
  for ( i=0 ; i<1000000 ; i++ )
  {
    insert( testContainer, leakStrings[0] );
    currentSize++;
  }
  
  testFound( 1, leakStrings );
  testSize();
  
  for ( i=0 ; i<1000000 ; i++ )
  {
    delete( testContainer, leakStrings[0] );
    currentSize--;
  }
  
  testNotFound( 1, leakStrings );
  testSize();
  
  // we should add a pause so we can check the memory footprint...
}

// The suite cleanup function.

void cleanSuite()
{
  clear( testContainer );
  currentSize = 0;
  testSize();
  destroyContainer( testContainer );
  
  printf( "\nTest results:\n" );
  printf( "%d tests were run.\n", testsPassed+testsFailed );
  printf( "%d tests passed.\n", testsPassed );
  printf( "%d tests failed.\n", testsFailed );
}

// Ensure that a set of elements is in the container

void testFound( int size, char *strings[] )
{
  char *searchString;
  Boolean result;
  int i;
  
  printf("\nTesting search for elements that are in the container:\n");
  for ( i=0 ; i<size ; i++ )
  {
    searchString = strings[i];
    result = contains( testContainer, searchString );
    
    if (result)
    {
      printf( "\"%s\" was found\n", searchString );
      testsPassed++;
    }
    else
    {
      printf( "\"%s\" was not found\n", searchString );
      testsFailed++;
    }
  }
}

// Ensure that a set of elements is not in the container

void testNotFound( int size, char *strings[] )
{
  char *searchString;
  Boolean result;
  int i;
  
  printf( "\nTesting search for elements not in the container:\n" );
  for ( i=0 ; i<size ; i++ )
  {
    searchString = strings[i];
    result = contains( testContainer, searchString );
    
    if (result)
    {
      printf( "\"%s\" was found\n", searchString );
      testsFailed++;
    }
    else
    {
      printf( "\"%s\" was not found\n", searchString );
      testsPassed++;
    }
  }
}

// Print the elements in the container

void testSize()
{
  char *string;
  int size;
  
  printf( "\nTesting size of container:\n" );
  string = firstItem( testContainer );
  size = 0;
  while ( string != NULL )
  {
    //printf("%s\n", string);
    size++;
    string = nextItem( testContainer );
  }
  printf( "Size of container is %d\n", size );
  
  if ( size == currentSize )
  {
    testsPassed++;
  }
  else
  {
    testsFailed++;
  }
}

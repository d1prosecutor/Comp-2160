#ifndef MAIN_H
#define MAIN_H

#include "container.h"

//--------------------------------------------------------------
// PROTOTYPES
//--------------------------------------------------------------
void testCreateContainer(Container *, Boolean);
void testDestroyContainer(Container **, Boolean);
void testInsertItem(Container *, char *, int);
void testDeleteItem(Container *, char *, int);
void testClear(Container *, Boolean);
void testFirstItem(Container *, char *);
void testNextItem(Container *, char *);
void testContains(Container *, char *, Boolean);
void testSize(Container *, int);

#endif
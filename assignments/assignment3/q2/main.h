#ifndef MAIN_H
#define MAIN_H

#include "set.h"

//--------------------------------------------------------------
// PROTOTYPES
//-------------------------------------------------------------
void testNewSet(Set *, Boolean);

void testDeleteSet(Set *, Boolean);

void testInsertItem(Set *const, const int, Boolean);

void testRemoveItem(Set *const testSet, const int givenItem, Boolean expected);

void testAreEqual(Set const *, Set const *, Boolean);

void testAreDisjoint(Set const *, Set const *, Boolean);

void testUnionOf(Set const *, Set const *, Set const *);

void testSymmetricDifferenceOf(Set const *, Set const *, Set const *);

void testValidateMemUse(Boolean);

#endif
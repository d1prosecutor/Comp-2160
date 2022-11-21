Set1.o
=====
* The are_Equal method is buggy.
  * It reports that 2 sets are not equal when they in fact are equal
  * Error encountered while testing with same set (twice - same memory address),
    sets containing same elements (different addresses in memory), 2 empty sets.

* The are_Disjoint method is buggy.
  * It reports that 2 sets are not disjoint when they in fact are disjoint.
  * Error encountered while testing with a non-empty and an empty set, 2 empty sets, two disjointed non-empty sets.

* The union method **might or might not** be buggy.
  * The result of the method differs from what should be the union of the sets.
  * ***Some bugs might be because the are_Equal method is buggy and I tested the union method using the are_Equal method***.

* The symmetric difference method **might or might not** be buggy.
  * The result of the method differs from what should be the symmetric difference of the sets.
  * ***Some bugs might be because the are_Equal method is buggy and I tested the symmetric difference method using the are_Equal method***.
		
Set2.o
=====
* The insert method is buggy. 
  * Inserts an item even when the item already exists in the set.
  * Error encountered while testing with inserting 1,2,3,4,5 in a set already containing those numbers.

* The remove method is buggy. 
  * Does not find the item to be removed from the set when that item is in fact in the set.
  * Error encountered while testing with removing 1 and 3 from a set which should be containing 1,2,3,4,5.

* The are_Equal method is buggy.
  * It reports that 2 sets are not equal when they in fact are equal - it only compares memory addresses and empty sets.
  * Error encountered while testing with non-empty sets containing same elements but different addresses in memory.

* The union method **might or might not** be buggy.
  * The result of the method differs from what should be the union of the sets.
  * It only reports that the union of a set with itself is itself (same memory addresses), and the union of 2 empty sets is an empty set.
  * ***Some bugs might be because the are_Equal method is buggy and I tested the union method using the are_Equal method***.

* The symmetric difference method **might or might not** be buggy.
  * The result of the method differs from what should be the symmetric difference of the sets.
  * It only reports correctly when the returned result (symmetric difference set) is the empty set, or when one of the sets passed in as an argument is empty.
  * ***Some bugs might be because the are_Equal method is buggy and I tested the symmetric difference method using the are_Equal method***.
				
Set3.o
=====
* The are_Disjoint method is buggy (It reports that 2 sets are not disjoint when they in fact are disjoint).
  * Error encountered while testing with a non-empty and an empty set, two disjointed non-empty sets.

* The symmetric difference method is buggy. 
  * The result of the method differs from what should be the symmetric difference of the sets.
  * Error in cases where the two sets are non-empty (works if at least one of the sets is empty).

Set4.o
=====
* The are_Disjoint method is buggy.
  * It reports that 2 sets are disjoint when they in fact aren't.
  * Error encountered while testing with same set twice (same memory address). In general two non-disjointed, non-empty sets.
		
Set5.o
=====
* The are_Disjoint method is buggy.
  * It allocates memory for new set(s) and doesn't free the memory when done with it.

	
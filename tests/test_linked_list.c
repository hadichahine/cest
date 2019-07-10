#include "primitive_testing_environment.h"
#include "linkedlist.h"

void testThatProcessLinkedListHasItem3WhenAdded(){
	LinkedList *linkedList = createLinkedList();
	int x = 3;
	addItemToLinkedList(linkedList,&x);
	primitiveAssertTrue(x == *((int*) next(linkedList)));
}

void testThatProcessLinkedListHasItem3And4WhenAdded(){
	LinkedList *linkedList = createLinkedList();
	int x = 3;
	int y = 4;
	addItemToLinkedList(linkedList,&x);	
	addItemToLinkedList(linkedList,&y);
	primitiveAssertTrue(x == *((int*) next(linkedList)));	
	primitiveAssertTrue(y == *((int*) next(linkedList)));
}

void testThatProcessLinkedListHasItem3And4And5WhenAdded(){
	LinkedList *linkedList = createLinkedList();
	int x = 3;
	int y = 4;	
	int z = 5;
	addItemToLinkedList(linkedList,&x);	
	addItemToLinkedList(linkedList,&y);	
	addItemToLinkedList(linkedList,&z);
	primitiveAssertTrue(x == *((int*) next(linkedList)));	
	primitiveAssertTrue(y == *((int*) next(linkedList)));		
	primitiveAssertTrue(z == *((int*) next(linkedList)));
}

void testReachedEnd(){
	LinkedList *linkedList = createLinkedList();
	int x = 3;
	addItemToLinkedList(linkedList,&x);
	primitiveAssertTrue(x == *((int*) next(linkedList)));
	primitiveAssertTrue(reachedEnd(linkedList));
}

void testResetIterator(){
	LinkedList *linkedList = createLinkedList();
	int x = 4;
	int y = 3;
	addItemToLinkedList(linkedList,&x);
	addItemToLinkedList(linkedList,&y);
	primitiveAssertTrue(x == *((int*) next(linkedList)));
	reset(linkedList);
	primitiveAssertTrue(x == *((int*) next(linkedList)));
}

int main(){
    runPrimitiveTest("testThatProcessLinkedListHasItem3WhenAdded",
		testThatProcessLinkedListHasItem3WhenAdded);
	runPrimitiveTest("testThatProcessLinkedListHasItem3And4WhenAdded",
		testThatProcessLinkedListHasItem3And4WhenAdded);	
	runPrimitiveTest("testThatProcessLinkedListHasItem3And4And5WhenAdded",
		testThatProcessLinkedListHasItem3And4And5WhenAdded);	
	runPrimitiveTest("testReachedEnd",
		testReachedEnd);
	runPrimitiveTest("testResetIterator",
		testResetIterator);	
    return 0;
}
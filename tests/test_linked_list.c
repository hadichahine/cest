#include "primitive_testing_environment.h"
#include "linkedlist.h"
#include <stdarg.h>

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
	return !(
    runPrimitiveTest("Test that linked list has item 3 when added.",
		testThatProcessLinkedListHasItem3WhenAdded) &&
	runPrimitiveTest("Test that linked list has item 3 and 4 when added.",
		testThatProcessLinkedListHasItem3And4WhenAdded) &&
	runPrimitiveTest("Test that linked list has item 3, 4, and 5 when added.",
		testThatProcessLinkedListHasItem3And4And5WhenAdded) &&
	runPrimitiveTest("Test reached end.",
		testReachedEnd) &&
	runPrimitiveTest("Test reset iterator.",
		testResetIterator));
}

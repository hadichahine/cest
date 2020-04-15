#include <stdlib.h>
#include <strings.h>
#include "mem_alloc.h"

typedef struct node {
	void *data;
	struct node *next;
}LinkedListNode;

typedef struct {
	LinkedListNode *head,*tail,*currentReadCursor;
	void *data;
}LinkedList;

LinkedList* createLinkedList(){
	return (LinkedList*)mem_alloc(sizeof(LinkedList));
}

LinkedListNode* createLinkedListNode(){
	return (LinkedListNode*)mem_alloc(sizeof(LinkedListNode));
}

int isEmpty(LinkedList* list){
	return (list->tail == 0);
}

void addItemToLinkedList(LinkedList *list,void* data){
	LinkedListNode* newNode = createLinkedListNode();
	newNode->data = data;
	if(!isEmpty(list))
		list->tail->next = newNode;
	else {		
		list->head = newNode;
		list->currentReadCursor = newNode;
	}
	list->tail = newNode;
}

void* next(LinkedList *list){
	void* ret = list->currentReadCursor->data;
	list->currentReadCursor = list->currentReadCursor->next;
	return ret;
}

int reachedEnd(LinkedList *list){
	return list->currentReadCursor == NULL;
}

void reset(LinkedList *list){
	list->currentReadCursor = list->head;
}
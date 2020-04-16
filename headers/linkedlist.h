typedef struct _LinkedList LinkedList;

LinkedList* createLinkedList();
int isEmpty(LinkedList* list);
void addItemToLinkedList(LinkedList *list,void* data);
void* next(LinkedList *list);
int reachedEnd(LinkedList *list);
void reset(LinkedList *list);
void destructList(LinkedList *list);


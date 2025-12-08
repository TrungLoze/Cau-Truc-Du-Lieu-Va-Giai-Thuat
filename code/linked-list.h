

typedef struct __ListElement {
    void* data;
    int size;   // size of data
    struct __ListElement* next;
} ListElement;

typedef ListElement* LinkedList;

void llInit(LinkedList* pl);
void llInsertHead(LinkedList* pl, void* v, int size);
void llInsertTail(LinkedList* pl, void* v, int size);
void llInsertAfter(LinkedList* pl, ListElement* a, void* v, int size);
void llDeleteHead(LinkedList* pl);
void llDeleteTail(LinkedList* pl);
void llDeleteAfter(LinkedList* pl, ListElement* a);
void llDeleteAll(LinkedList* pl);
int llCount(LinkedList l);
ListElement* llSeek(LinkedList l, int i);
void llForEach(LinkedList l, void (*func)(void* data, int size));
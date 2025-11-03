

typedef struct __ListElement {
    float data;
    struct __ListElement* next;
} ListElement;

typedef ListElement* LinkedList;

void llInit(LinkedList* pl);
void llInsertHead(LinkedList* pl, float v);
void llInsertTail(LinkedList* pl, float v);
void llInsertAfter(LinkedList* pl, ListElement* a, float v);
void llDeleteHead(LinkedList* pl);
void llDeleteTail(LinkedList* pl);
void llDeleteAfter(LinkedList* pl, ListElement* a);
void llDeleteAll(LinkedList* pl);
int llCount(LinkedList l);
ListElement* llSeek(LinkedList l, int i);
void llForEach(LinkedList l, void (*func)(float data));
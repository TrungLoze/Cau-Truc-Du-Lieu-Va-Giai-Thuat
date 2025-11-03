
#include <stdlib.h>
#include "linked-list.h"


void llInit(LinkedList* pl) {
    *pl = NULL;
}

void llInsertHead(LinkedList* pl, float v) {
    ListElement* e = (ListElement*)malloc(sizeof(ListElement));
    e->data = v;
    e->next = *pl;

    *pl = e;
}


void llInsertTail(LinkedList* pl, float v) {
    ListElement* e = (ListElement*)malloc(sizeof(ListElement));
    e->data = v;
    e->next = NULL;

    if (*pl == NULL) {
        *pl = e;
    } else {
        ListElement* last;
        for (last = *pl; last->next != NULL; last = last->next);

        last->next = e;
    }
}


void llInsertAfter(LinkedList* pl, ListElement* a, float v) {
    if (a == NULL) return;
    
    ListElement* e = (ListElement*)malloc(sizeof(ListElement));
    e->data = v;
    e->next = a->next;

    a->next = e;
}


void llDeleteHead(LinkedList* pl) {
    if (*pl == NULL) return;
    
    ListElement* e = (*pl)->next;
    free(*pl);
    *pl = e;
}


void llDeleteTail(LinkedList* pl) {
    if (*pl == NULL) return;

    if ((*pl)->next == NULL) {
        free(*pl);
        *pl = NULL;
        return;
    }

    ListElement* last2;
    for (last2 = *pl; last2->next->next != NULL; last2 = last2->next);

    free(last2->next);
    last2->next = NULL;
}


void llDeleteAfter(LinkedList* pl, ListElement* a) {
    if (a == NULL || a->next == NULL) return;

    ListElement* p = a->next->next;
    free(a->next);
    a->next = p;
}


void llDeleteAll(LinkedList* pl) {
    ListElement *p, *q;
    for (p = *pl; p != NULL; p = q) {
        q = p->next;
        free(p);
    }

    *pl = NULL;
}


int llCount(LinkedList l) {
    int n = 0;
    for (ListElement* p = l; p != NULL; p = p->next)
        n++;

    return n;
}


ListElement* llSeek(LinkedList l, int i) {
    ListElement* p;
    for (p = l; i > 0 && p != NULL; p = p->next)
        i--;

    return p;
}


void llForEach(LinkedList l, void (*func)(float data)) {
    for (ListElement* p = l; p != NULL; p = p->next)
        func(p->data);
}



// void llInsertBefore(LinkedList* pl, ListElement* a, float v) {
//     // to do
// }

// void llDeleteAt(LinkedList* pl, ListElement* a) {
//     // to do
// }


#include <stdlib.h>
#include <memory.h>
#include "linked-list.h"


void llInit(LinkedList* pl) {
    *pl = NULL;
}


void freeNode(ListElement* p) {
    free(p->data);
    free(p);
}

void llInsertHead(LinkedList* pl, void* v, int size) {
    ListElement* e = (ListElement*)malloc(sizeof(ListElement));
    e->data = malloc(size);
    memcpy(e->data, v, size);
    e->next = *pl;

    *pl = e;
}


void llInsertTail(LinkedList* pl, void* v, int size) {
    ListElement* e = (ListElement*)malloc(sizeof(ListElement));
    e->data = malloc(size);
    memcpy(e->data, v, size);
    e->next = NULL;

    if (*pl == NULL) {
        *pl = e;
    } else {
        ListElement* last;
        for (last = *pl; last->next != NULL; last = last->next);

        last->next = e;
    }
}


void llInsertAfter(LinkedList* pl, ListElement* a, void* v, int size) {
    if (a == NULL) return;
    
    ListElement* e = (ListElement*)malloc(sizeof(ListElement));
    e->data = malloc(size);
    memcpy(e->data, v, size);
    e->next = a->next;

    a->next = e;
}


void llDeleteHead(LinkedList* pl) {
    if (*pl == NULL) return;
    
    ListElement* e = (*pl)->next;
    freeNode(*pl);
    *pl = e;
}


void llDeleteTail(LinkedList* pl) {
    if (*pl == NULL) return;

    if ((*pl)->next == NULL) {
        freeNode(*pl);
        *pl = NULL;
        return;
    }

    ListElement* last2;
    for (last2 = *pl; last2->next->next != NULL; last2 = last2->next);

    freeNode(last2->next);
    last2->next = NULL;
}


void llDeleteAfter(LinkedList* pl, ListElement* a) {
    if (a == NULL || a->next == NULL) return;

    ListElement* p = a->next->next;
    freeNode(a->next);
    a->next = p;
}


void llDeleteAll(LinkedList* pl) {
    ListElement *p, *q;
    for (p = *pl; p != NULL; p = q) {
        q = p->next;
        freeNode(p);
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


void llForEach(LinkedList l, void (*func)(void* data, int size)) {
    for (ListElement* p = l; p != NULL; p = p->next)
        func(p->data, p->size);
}



void llInsertBefore(LinkedList* pl, ListElement* a, void* v, int size) {
    if (a == NULL || *pl == NULL) return;

    if (a == *pl) {
        llInsertHead(pl, v, size);
        return;
    }

    ListElement* prev;
    for (prev = *pl; prev->next != a && prev->next != NULL; prev = prev->next);

    if (prev->next == a) {
        llInsertAfter(pl, prev, v, size);
    }
}

void llDeleteAt(LinkedList* pl, ListElement* a) {
    if (a == NULL || *pl == NULL) return;

    if (a == *pl) {
        llDeleteHead(pl);
        return;
    }

    ListElement* prev;
    for (prev = *pl; prev->next != a && prev->next != NULL; prev = prev->next);

    if (prev->next == a) {
        llDeleteAfter(pl, prev);
    }
}

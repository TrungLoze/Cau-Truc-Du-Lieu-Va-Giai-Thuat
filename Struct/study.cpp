#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node* next;
}LinkedElement;


typedef LinkedElement* LinkedList;

void llInit(LinkedList* pl) {
    *pl = NULL;
}

void llInsertHead(LinkedList* pl, int v) {
    LinkedElement* e = (LinkedElement*)malloc(sizeof(LinkedElement));
    e->data =v;
    e->next = *pl;

    *pl = e;
}

void llInsertTail(LinkedList* pl, int v) {
    LinkedElement* e = (LinkedElement*)malloc(sizeof(LinkedElement));
    e->data =v;
    e->next = NULL;

    if (*pl == NULL) {
        *pl = e;
    }else{
        LinkedElement* last;
        for(last = *pl; last->next != NULL; last = last->next);
        last->next = e;
    }
}

void llInsertAfter(LinkedList* pl, LinkedElement* a, int v) {
    if (a == NULL) return;
    
    LinkedElement* e = (LinkedElement*)malloc(sizeof(LinkedElement));
    e->data = v;
    e->next = a->next;

    a->next = e;
}

void llDeleteAt(LinkedList* pl, ListElement* a) {
    if (a == NULL || *pl == NULL) return; 
    if (a == *pl) { 
        llDeleteHead(pl);   
        }
    }

int main() {
    LinkedList l;

    llInit(&l);
    return 0;
}
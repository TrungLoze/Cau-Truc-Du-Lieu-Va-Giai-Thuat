#include <stdio.h>
#include <stdlib.h>

typedef struct __ListElement {
    float data;
    struct __ListElement* next;
} ListElement;

typedef ListElement* LinkedList;

void llInit(LinkedList* pl){
    *pl=NULL;
}

void llInsertHead(LinkedList* pl, float v){
    ListElement* e=(ListElement*)malloc(sizeof(ListElement));
    e->data=v;
    e->next=*pl;
    *pl=e;
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

void llInsertBefore(LinkedList* pl, ListElement* a, float v){
    ListElement* e = (ListElement*)malloc(sizeof(ListElement));
    e->data = v;
    e->next = a;
    if(a == NULL) return;

    for(ListElement* p = *pl; p != NULL; p = p->next){
        if(p->next == a){
            p->next = e;
            return;
        }
    }

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
    if(a == NULL || a->next == NULL) return;

    // ListElement* e= a->next;
    // a->next = e->next;
    // free(e);

    ListElement* e = a->next->next;
    free(a->next);
    a->next = e;
}

void llDeleteAll(LinkedList* pl) {
    ListElement *p, *q;
    for(p = *pl; p != NULL; p=q){
        q = p->next;
        free(p);
    }

    *pl = NULL;
}

int llCount(LinkedList l){
    int count=0;
    for(ListElement* p= l; p!=NULL; p=p->next)
        count++;

    return count;
}

ListElement* llSeek(LinkedList l, int i){
    ListElement* p;
    for(p = l; i > 0 && p!= NULL;p = p->next){
        i--;
    }
    return p;
}

void llForEach(LinkedList l, void (*func)(float data)) {
    for(ListElement* p = l; p != NULL; p = p->next) {
        func(p->data);
    }
}

void printfElement(float data) {
    printf("%f ", data);
}

int main(){
    int m[]={1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    const int mn= sizeof(m)/sizeof(m[0]);
    LinkedList l;

    llInit(&l);

    for(int i=0;i<5;i++)
        llInsertTail(&l,(float)(i));
    
    llInsertTail(&l, 60);

    llInsertHead(&l, 10);
    llInsertHead(&l, 20);

    llInsertTail(&l, 50);

    ListElement* a = llSeek(l, 2);
    llInsertAfter(&l, a, 100);

    printf("m: ");
    for(int i=0;i<mn;i++){
        printf("%d ", m[i]);
    }
    printf("\n");

    printf("m: ");
    for(int* p = m; p< m+mn; p++){
        printf("%d ", *p);
    }
    printf("\n");

    // printf("l: ");
    // for(ListElement* p = l; p != NULL; p = p->next){
    //     printf("%f ", p->data);
    // }
    // printf("\n");
    
    printf("l: ");
    llForEach(l, printfElement);
    printf("\n");

    llDeleteAll(&l);
    
   return 0;
}
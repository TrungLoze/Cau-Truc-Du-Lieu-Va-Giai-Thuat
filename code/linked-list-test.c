#include <stdio.h>
#include "linked-list.h"

void printElement(float data) {
    printf("%f ", data);
}


int main() {
    int m[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    const int mn = sizeof(m) / sizeof(m[0]);

    LinkedList l;

    llInit(&l);

    llInsertTail(&l, 60);

    llInsertHead(&l, 10);
    llInsertHead(&l, 20);

    llInsertTail(&l, 50);

    ListElement* a = llSeek(l, 2);
    llInsertAfter(&l, a, 100);

    printf("m: ");
    for (int i = 0; i < mn; i++)
        printf("%d ", m[i]);
    printf("\n");

    printf("m: ");
    for (int* p = m; p < m + mn; p++)
        printf("%d ", *p);
    printf("\n");

    printf("l: ");
    for (ListElement* p = l; p != NULL; p = p->next)
        printf("%f ", p->data);
    printf("\n");

    printf("l: ");
    llForEach(l, printElement);
    printf("\n");

    llDeleteAll(&l);
    
    return 0;
}
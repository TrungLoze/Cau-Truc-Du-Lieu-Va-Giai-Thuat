#include <stdio.h>
#include "linked-list.h"

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
    llInsertBefore(&l, a, 200);
    llInsertAfter(&l, a, 100);

    llDeleteAll(&l);
    
    return 0;
}
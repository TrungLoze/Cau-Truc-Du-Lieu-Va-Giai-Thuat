#include <stdio.h>
#include "queue-list.h"

int main() {
    Queue q;

    quInit(&q);
    quPrintQueue(&q);

    quEnqueue(&q, 10);
    quPrintQueue(&q);

    quEnqueue(&q, 20);

    quPrintQueue(&q);

    quEnqueue(&q, 30);

    quPrintQueue(&q);
    
    quEnqueue(&q, 40);

    quPrintQueue(&q);

    quDequeue(&q);
    quPrintQueue(&q);

    quDestroy(&q);

    return 0;
}
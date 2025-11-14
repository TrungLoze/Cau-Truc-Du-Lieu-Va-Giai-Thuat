#include <stdio.h>
#include "queue-list.h"

void quInit(Queue* q) {
    llInit(q);
}

void quDestroy(Queue* q) {
    llDeleteAll(q);
}

void quEnqueue(Queue* q, float v) {
    llInsertHead(q, v);
}

void quDequeue(Queue* q) {
    llDeleteTail(q);
}

float quHead(Queue* q) {
    return (*q)->data;
}


int quFull(Queue* q) {
    return 0;
}

int quEmpty(Queue* q) {
    return *q == NULL;
}


void printElement(float data) {
    printf("%f ", data);
}

void quPrintQueue(Queue* q) {
    printf("[ ");

    llForEach(*q, printElement);

    printf("]\n");
}

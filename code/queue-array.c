#include <stdio.h>
#include "queue-array.h"

void quInit(Queue* q, int n) {
    q->data = (float*)malloc(n * sizeof(float));
    q->n = n;
    q->head = 0;
    q->count = 0;
}

void quDestroy(Queue* q) {
    free(q->data);
    q->data = NULL;
    q->n = 0;
    q->count = 0;
}

void quEnqueue(Queue* q, float v) {
    if (q->count == q->n) return;

    q->data[(q->head + q->count) % q->n] = v;
    q->count++;
}

void quDequeue(Queue* q) {
    if (q->count == 0) return;

    q->count--;
}

float quHead(Queue* q) {
    return q->data[q->head];
}


int quFull(Queue* q) {
    return q->count == q->n;
}

int quEmpty(Queue* q) {
    return q->count == 0;
}


void quPrintQueue(Queue* q) {
    printf("[ ");

    for (int i = q->head, c = 0; c < q->n; i++, c++) {
        if (i >= q->n) i -= q->n;
        printf("%f ", q->data[i]);
    }

    printf("]\n");
}

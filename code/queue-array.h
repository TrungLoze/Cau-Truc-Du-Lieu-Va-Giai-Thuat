
#include <stdlib.h>

typedef struct {
    float* data;
    int n;
    int head, count;
} Queue;

void quInit(Queue* s, int n);
void quDestroy(Queue* s);
void quEnqueue(Queue* s, float v);
void quDequeue(Queue* s);
float quHead(Queue* s);
int quFull(Queue* s);
int quEmpty(Queue* s);
void quPrintQueue(Queue* s);
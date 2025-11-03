#include <stdlib.h>

typedef struct {
    float* data;
    int n;
    int head, count;

}Queue;

void qhInit(Queue* s, int n);
void qhDestroy(Queue* s);
void qhPush(Queue* s,float v);
void qhPop(Queue* s);
void qhPrintQueue(Queue* );
float qhTop(Queue* s);
int qhFull(Queue* s);
int qhEmpty(Queue* s);
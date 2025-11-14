
#include <stdlib.h>
#include "linked-list.h"

typedef LinkedList Queue;

void quInit(Queue* s);
void quDestroy(Queue* s);
void quEnqueue(Queue* s, float v);
void quDequeue(Queue* s);
float quHead(Queue* s);
int quFull(Queue* s);
int quEmpty(Queue* s);
void quPrintQueue(Queue* s);
#include <stdlib.h>
#include "linked-list.h"

typedef LinkedList Stack;

void stInit(Stack* s);
void stDestroy(Stack* s);
void stPush(Stack* s, float v);
void stPop(Stack* s);
float stTop(Stack* s);
int stFull(Stack* s);
int stEmpty(Stack* s);
void stPrintStack(Stack* s);
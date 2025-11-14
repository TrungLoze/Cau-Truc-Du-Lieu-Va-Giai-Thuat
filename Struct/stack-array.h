#include <stdlib.h>

typedef struct {
    float* data;
    int n;
    int top;

}Stack;

void stInit(Stack* s, int n);
void stDestroy(Stack* s);
void stPush(Stack* s,float v);
void stPop(Stack* s);
void stPrintStack(Stack* );
float stTop(Stack* s);
int stFull(Stack* s);
int stEmpty(Stack* s);
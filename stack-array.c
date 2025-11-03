#include <stdio.h>
#include "stack-array.h"


void stInit(Stack* s, int n){
    s-> data = (float*)malloc(n * sizeof(float));
    s->n = n;
    s->top = -1;
}

void stDestroy(Stack* s){
    free(s->data);
    s->data = NULL;
    s->n = 0;
    s->top = -1;
}

void stPush(Stack* s,float v){
    if(s->top == s->n-1) return;
    s->top++;
    s->data[s->top] = v;
}

void stPop(Stack* s){
    if(s->top == -1) return;
    s->top--;
}

void stPrintStack(Stack* s){
    for(int i = 0; i<= s->top; i++){
        printf("%f ", s->data[i]);
    }
}

float stTop(Stack* s){
    return s->data[s->top];
}

int stFull(Stack* s){
    if(s->top == s->n-1) return 1;
    return 0;
}

int stEmpty(Stack* s){
    if(s->top == -1) return 1;
    return 0;
}
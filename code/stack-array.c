#include <stdio.h>
#include "stack-array.h"

void stInit(Stack* s, int n) {
    s->data = (float*)malloc(n * sizeof(float));
    s->n = n;
    s->top = -1;
}

void stDestroy(Stack* s) {
    free(s->data);
    s->data = NULL;
    s->n = 0;
    s->top = -1;
}

void stPush(Stack* s, float v) {
    if (s->top == s->n - 1) return;

    s->top++;
    s->data[s->top] = v;
}

void stPop(Stack* s) {
    if (s->top < 0) return;

    s->top--;
}

float stTop(Stack* s) {
    return s->data[s->top];
}


int stFull(Stack* s) {
    return s->top == s->n -1;
}

int stEmpty(Stack* s) {
    return s->top < 0;
}


void stPrintStack(Stack* s) {
    printf("[ ");

    for (int i = s->top; i >= 0; i--)
        printf("%f ", s->data[i]);

    printf("]\n");
}

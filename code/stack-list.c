#include <stdio.h>
#include <stdlib.h>
#include "stack-list.h"

typedef LinkedList Stack;


void stInit(Stack* s) {
    llInit(s);
}

void stDestroy(Stack* s) {
    llDeleteAll(s);
}

void stPush(Stack* s, float v) {
    llInsertHead(s, v);
}

void stPop(Stack* s) {
    llDeleteHead(s);
}

float stTop(Stack* s) {
    return (*s)->data;
}


int stFull(Stack* s) {
    return 0;
}

int stEmpty(Stack* s) {
    return *s == NULL;
}


void printElement(float data) {
    printf("%f ", data);
}

void stPrintStack(Stack* s) {
    printf("[ ");

    llForEach(*s, printElement);

    printf("]\n");
}


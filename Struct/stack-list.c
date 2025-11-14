#include <stdio.h>
#include <stdlib.h>
#include "linked-list.h"

typedef LinkedList Stack;

void stInit(Stack* s){
    llInit(s);
}

void stDestroy(Stack* s){
    llDeleteAll(s);
}

void stPush(Stack* s,float v){
    llInsertHead(s,v);
}

void stPop(Stack* s){
    llDeleteHead(s)
}

void printStack(Stack* s){
    for(int i = 0; i<= s->top; i++){
        printf("%f ", s->data[i]);
    }
}

float stTop(Stack* s){
    return (*s)->data;
}

int stFull(Stack* s){
    return 0;
}

int stEmpty(Stack* s){
    return (*s) == NULL;
}

int main(){

    Stack s;
    
    stInit(&s);
    for(int i = 1; i <= 10; i++){
        stPush(&s, (float)i * 10.0);
        printStack(&s);
        printf("\n");
        printf("%f \n", stTop(&s));
    }

    stPop(&s);
    printStack(&s);

    stDestroy(&s);

    return 0;
}
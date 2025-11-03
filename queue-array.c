#include <stdio.h>
#include "queue-array.h"


void qhInit(Queue* s, int n){
    
}

void qhDestroy(Queue* s){
    free(s->data);
    s->data = NULL;
    s->n = 0;
    s->count = 0;
}

void qhEnqueue(Queue* s,float v){
    if(s->count == s->n) return;

    s->data[(s->head + s->count) % s->n] = v;
    s->count++;
}

void qhDequeue(Queue* s){
    if(s->count==0)return;
    s->count--;
}

void qhPrintQueue(Queue* s){
    for(int i = s->head, c=0;c< s->n; i++,c++){
        if(i >= s->n) i-=s->n;
        printf("%f ", s->data[i]);
    }
}

float qhTop(Queue* s){
    return s->data[s->head];
}

int qhFull(Queue* s){
    if(s->count == s->n) return 1;
    return 0;
}

int qhEmpty(Queue* s){
    if(s->count == 0) return 1;
    return 0;
}
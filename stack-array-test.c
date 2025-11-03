#include <stdio.h>
#include "stack-array.h"


int main(){

    Stack s;
    
    stInit(&s, 10);
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
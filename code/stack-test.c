#include <stdio.h>
#include "stack-list.h"

int main() {
    Stack s;

    stInit(&s);
    while(1){
        int t;
        printf("Co muon nhap tiep khong [0,1] :");
        scanf("%d",&t);
        if(t){
            float v;
            printf("Nhap so :");
            scanf("%f",&v);
            stPush(&s, v);
        }else{
            break;
        }
    }

    stPrintStack(&s);

    stDestroy(&s);

    return 0;
}
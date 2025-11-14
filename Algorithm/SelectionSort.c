#include <stdio.h>
#include <stdlib.h>

void swap(int* a,int i, int j){
    int t = a[i];
    a[i] = a[j];
    a[j] = t;
}

// void Selectionsort(int*a, int n){
//     for(int i=0;i<n;i++){
//         for(int j=i+1;j<n;j++){
//             if(a[i] < a[j]){
//                 swap(a,i,j);
//             }
//         }
//     }
// }

void Selectionsort(int*a, int n){
    int index_min,j;
    for(int i=0;i<n;i++){
        for(index_min = i,j=i+1;j<n;j++){
            if(a[j] < a[index_min]){
                index_min=j;
            }
        }
        if(index_min != i) swap(a,i,index_min);
    }
}

void printArray(int* a, int n){
    printf("[ ");
    for(int i=0;i<n;i++){
        printf("%d ",a[i]);
    }
    printf("]\n");
}

int main(){
    int a[]={5,1,6,2,4,3};

    printArray(a,6);

    Selectionsort(a,6);    

    printArray(a,6);
}
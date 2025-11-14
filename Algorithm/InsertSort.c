#include <stdio.h>
#include <stdlib.h>

void swap(int* a,int i, int j){
    int t = a[i];
    a[i] = a[j];
    a[j] = t;
}

// void Insertsort(int*a, int n){
//     for(int i=1;i<n;i++){
//         for(int j=i;j>0 && a[j]<a[j-1];j--){
//             swap(a,j,j-1);
//         }
//     }
// }

void Insertsort(int*a, int n){
    int j,t;
    for(int i=1;i<n;i++){
        t=a[i];
        for(j=i;j>0 && t<a[j-1];j--){
            a[j] = a[j-1];
        }
        a[j]=t;
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

    Insertsort(a,6);    

    printArray(a,6);
}
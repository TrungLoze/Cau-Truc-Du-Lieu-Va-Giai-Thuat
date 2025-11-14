#include <stdio.h>

void swap(int* a, int i, int j) {
    int t = a[i];
    a[i] = a[j];
    a[j] = t;
}

void correctMaxHeapNode(int* a, int n, int i){
    int li = 2*i + 1,
    ri = li + 1;

    int mi = i;
    if(li < n && a[li] > a[mi]) mi = li;
    if(ri < n && a[ri] > a[mi]) mi = ri;

    if(mi == i) return;

    swap(a,i,mi);

    correctMaxHeapNode(a, n,mi);
}

void buildMaxHeap(int* a, int n){
    for(int i=n/2;i>=0;i--){
        correctMaxHeapNode(a,n,i);
    }
}

void printArray(int* a, int n) {
    printf("[ ");
    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    printf("]\n");
}

void HeapSort(int* a,int n){
    buildMaxHeap(a,n);

    for(;n >= 1;){
        swap(a,0,n-1);
        n--;
        correctMaxHeapNode(a,n,0);
    }
}

int main(){
    int a[]={5, 1, 7, 3, 4, 9, 6, 8, 2};
    int n= sizeof(a)/sizeof(a[0]);

    printArray(a,n);

    buildMaxHeap(a,n);

    printArray(a,n);

    HeapSort(a,n);

    printArray(a,n);
    
    return 0;
}
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

void MaxHeapSort(int* a,int n){
    buildMaxHeap(a,n);

    for(;n >= 1;){
        swap(a,0,n-1);
        n--;
        correctMaxHeapNode(a,n,0);
    }
}

void correctMinHeapNode(int* a, int n, int i) {
    int li = 2*i + 1,
    ri = li + 1;

    int mi = i;
    if(li < n && a[li] < a[mi]) mi = li;
    if(ri < n && a[ri] < a[mi]) mi = ri;

    if(mi == i) return;

    swap(a,i,mi);
    correctMinHeapNode(a,n,mi);
}


void buildMinHeap(int* a, int n) {
    for(int i=n/2;i>=0;i--){
        correctMinHeapNode(a,n,i);
    }
}


void minHeapSort(int* a, int n) {
    buildMinHeap(a,n);

    for(int i=n-1;i>=1;i--){
        swap(a,0,i);
        correctMinHeapNode(a,i,0);
    }
}

void printArray(int* a, int n) {
    printf("[ ");
    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    printf("]\n");
}

void printReverArray(int* a,int n){
    printf("[ ");
    for (int i = n-1; i>=0; i--){
        printf("%d ", a[i]);
    }
    printf("]\n");
}

int main(){
    int a[]={5, 1, 7, 3, 4, 9, 6, 8, 2};
    int n= sizeof(a)/sizeof(a[0]);

    printArray(a,n);

    buildMaxHeap(a,n);

    printArray(a,n);

    // MaxHeapSort(a,n);
    minHeapSort(a,n);

    printReverArray(a,n);
    
    
    return 0;
}
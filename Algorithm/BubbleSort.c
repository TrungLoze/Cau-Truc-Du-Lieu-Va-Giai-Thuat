#include <stdio.h>


void swap(int* a, int i, int j) {
    int t = a[i];
    a[i] = a[j];
    a[j] = t;
}

void bubbleSort(int* a, int n) {
    int i, j;

    for (i = n; i > 1; i--) {
        for (int j = 0; j < i - 1; j++) {
            if (a[j] > a[j+1])
                swap(a, j, j + 1);
        }
    }
}


void bubbleSortImproved(int* a, int n) {
    int i, j, sorted = 0;
    for (i = n; !sorted && i > 0; i--) {
        sorted = 1;
        for (j = 0; j < i - 1; j++) {
            if (a[j] > a[j + 1]) {
                swap(a, j, j + 1);
                sorted = 0;
            }
        }
    }
}

void De_quy(int* a, int n){
    if(n==1) return;

    int sorted=0;
    for(int j=0;j<n-1;j++){
        if(a[j] > a[j+1]){
            swap(a,j,j+1);
            sorted=1;
        }
    }

    if(!sorted) return;

    De_quy(a,n-1);
}


void printArray(int* a, int n) {
    printf("[ ");
    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    printf("]\n");
}



int main() {
    int a[] = { 5, 1, 7, 3, 4, 9, 6, 8, 2};
    int n = sizeof(a) / sizeof(a[0]);

    printArray(a, n);

    De_quy(a, n);

    printArray(a, n);

    return 0;
}
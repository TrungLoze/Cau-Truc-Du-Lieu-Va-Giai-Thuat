#include <stdio.h>
#include <stdlib.h>

void quicksortRange(int* a, int l, int r) {
    if (l < r) {
        int pi = qsPartitionHoare(a, l, r);
        quicksortRange(a, l, pi - 1);
        quicksortRange(a, pi + 1, r);
    }
}
void quicksort(int* a, int n) {
    quicksortRange(a, 0, n - 1);
}

int qsPartitionLomuto(int* a, int l, int r) {
    int pivot = a[r];
    int i, j;
    for (i = l, j = l; j < r; j++) {
        if (a[j] < pivot)
            swap(a, i++, j);
    }
    swap(a, i, r);
    return i;
}

int qsPartitionHoare(int* a, int l, int r) {
    int pivot = a[r];
    int i, j;
    for (i = l, j = r - 1; i < j;) {
        for (; a[i] < pivot && i < j; i++);
        for (; a[j] >= pivot && i < j; j--);
        swap(a, i, j);
    }
    if (a[r] > a[i]) return r;
    swap(a, i, r);
    return i;
}


int main(){
    
} 
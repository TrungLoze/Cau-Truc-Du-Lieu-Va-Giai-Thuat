#include <stdio.h>

void swap(int* a, int i, int j){
    int tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
}

void SelectSort(int* a, int n){
    int i, j, index_min;
    for(i=0;i<n;i++){
        for(index_min=i, j=i+1;j<n;j++){
            if(a[index_min] > a[j]){
                index_min = j;
            }
        }

        if(i!=index_min) swap(a, index_min, i);
    }
}

void InsertSort(int* a, int n){
    for(int i=1;i<n;i++){
        for(int j=i;j>0 && a[j] < a[j-1];j--){
            swap(a, j-1,j);
        }
    }
}

int main(){
    int a[] = {5, 7, 1, 3, 9, 12};
    int n = sizeof(a)/ sizeof(a[0]);

    //SelectSort(a, n);
    InsertSort(a, n);
    //BubbleSort(a, n);

    for(int i=0;i<n;i++){
        printf("%d ",a[i]);
    }
}
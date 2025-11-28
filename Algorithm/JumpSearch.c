#include <stdio.h>
#include <math.h>

int jump_search(int a[], int n, int v) {
    int i, j = 0, m = (int)sqrt(n);

    for (i = 0; i < n && a[i] <= v; j = i, i += m)
        if (a[i] == v) return i;

    if (i >= n) {
        i = n - 1;
        if (a[i] < v) return -1;
    } else i--;

    for (; i >= j; i--)
        if (a[i] == v) return i;

    return -1;
}

int main(){
    
    return 0;
}
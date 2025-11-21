#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap(int* a, int i, int j) {
    int t = a[i];
    a[i] = a[j];
    a[j] = t;
}

void sortMergePart(int* a, int l, int r) {
    int m = (l + r)/2;
    if (m > l) sortMergePart(a, l, m);
    if (m + 1 < r) sortMergePart(a, m + 1, r);
    mergeParts_inPlace(a, l, m, r);
}

void sortMerge(int* a, int n) {
    sortMergePart(a, 0, n-1);
}

void mergeParts_aux(int* a, int l, int m, int r) {
    int pn = m - l + 1, qn = r - m;
    int *p = (int*)malloc(pn * sizeof(int)),
        *q = (int*)malloc(qn * sizeof(int));
    memcpy(p, a + l, pn * sizeof(int));
    memcpy(q, a + m + 1, qn * sizeof(int));
    for (int i = 0, j = 0; i < pn || j < qn; ) {
        if ((i == pn) || (j < qn && p[i] > q[j])) {
            a[l + i + j] = q[j];
            j++;
        } else {
            a[l + i + j] = p[i];
            i++;
        }
    }
    free(p);
    free(q);
}

void mergeParts_inPlace(int* a, int l, int m, int r) {
    int i, t;
    for (; m < r; m++) {
        t = a[m+1];
        for (i = m; i >= l && a[i] > t; i--)
            a[i+1] = a[i];
        a[i+1] = t;
    }
}


int main(){
    
}
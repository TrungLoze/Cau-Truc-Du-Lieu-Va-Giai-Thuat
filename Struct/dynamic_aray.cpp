#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printArray(int* p, int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", p[i]);
    printf("\n");
}


void addElement(int** pp, int* pn, int t, int v) {
    int* q = (int*)malloc((*pn + 1) * sizeof(int));

    for (int i = 0; i < t; i++)
        q[i] = (*pp)[i];

    for (int i = t; i < *pn; i++)
        q[i + 1] = (*pp)[i];

    q[t] = v;

    free(*pp);

    *pp = q;
    (*pn)++;
}

void deleteElement(int** pp, int* pn, int t) {
    int* q = (int*)malloc((*pn - 1) * sizeof(int));

    // for(int i = 0; i < t; i++)
    //     q[i] = (*pp)[i];

    memcpy(q, *pp, t * sizeof(int));

    // for(int i = t + 1; i < *pn; i++)
    //     q[i - 1] = (*pp)[i];

    memcpy(q + t, *pp + t + 1, (*pn - t - 1) * sizeof(int));

    free(*pp);

    *pp = q;
    (*pn)--;
}


int main() {
    int n = 10;
    int* p = (int*)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++)
        p[i] = i + 100;

    printArray(p, n);

    addElement(&p, &n, 2, 200);
    addElement(&p, &n, 4, 300);
    addElement(&p, &n, 8, 400);

    printArray(p, n);

    deleteElement(&p, &n, 4);
    
    printArray(p, n);

    free(p);
}
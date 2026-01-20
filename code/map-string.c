#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linked-list.h"

typedef int (*StringMapHashFunc)(const char*, int);

typedef struct {
    int n;
    LinkedList* table;
    StringMapHashFunc hashFunc;
} StringMap;

typedef struct {
    char* key;
    float value;
} StringMapData;


int defaultHash(const char* s, int n) {
    // also works with empty strings
    return s[0] % n;
}

void mapCreate(StringMap* m, int n, StringMapHashFunc hashFunc) {
    m->n = n;
    m->table = (LinkedList*)malloc(n * sizeof(LinkedList));
    m->hashFunc = hashFunc == NULL ? defaultHash : hashFunc;

    for (int i = 0; i < n; i++)
        llInit(&(m->table[i]));
}

void mapDestroy(StringMap* m) {
    for (int i = 0; i < m->n; i++) {
        for (ListElement* p = m->table[i]; p != NULL; p = p->next) {
            free(((StringMapData*)(p->data))->key);
            free(p->data);
        }

        llDeleteAll(&(m->table[i]));
    }

    free(m->table);
    m->table = NULL;
}

void mapSet(StringMap* m, const char* key, float value) {
    int h = m->hashFunc(key, m->n);
    LinkedList* l = &(m->table[h]);

    for (ListElement* p = *l; p != NULL; p = p->next) {
        if (strcmp(((StringMapData*)p->data)->key, key) == 0) {
            ((StringMapData*)p->data)->value = value;
            return;
        }
    }

    StringMapData* d = (StringMapData*)malloc(sizeof(StringMapData));
    d->key = (char*)malloc(strlen(key) + 1);
    strcpy(d->key, key);
    d->value = value;
    llInsertHead(l, d, sizeof(StringMapData));
}

void mapUnset(StringMap* m, const char* key) {
    int h = m->hashFunc(key, m->n);
    LinkedList* l = &(m->table[h]);

    for (ListElement* p = *l, *q = NULL; p != NULL; q = p, p = p->next) {
        if (strcmp(((StringMapData*)p->data)->key, key) == 0) {
            if (q == NULL)
                llDeleteHead(l);
            else llDeleteAfter(l, q);
            return;
        }
    }
}

float* mapGet(StringMap* m, const char* key) {
    int h = m->hashFunc(key, m->n);
    LinkedList* l = &(m->table[h]);

    for (ListElement* p = *l; p != NULL; p = p->next) {
        if (strcmp(((StringMapData*)p->data)->key, key) == 0) {
            return &(((StringMapData*)p->data)->value);
        }
    }

    return NULL;
}

void mapForEach(StringMap* m, void (*func)(const StringMapData* data)) {
    for (int i = 0; i < m->n; i++){
        for (ListElement* p = m->table[i]; p != NULL; p = p->next) {
            func((StringMapData*)p->data);
        }
    }
}


int myHash(const char* s, int n) {
    int m = 0;
    for (; *s != 0; s++)
        m += *s;

    return m % n;
}

void printElement(const StringMapData* e) {
    printf("%s: %g\n", e->key, e->value);
}

int main() {
    StringMap m;

    mapCreate(&m, 4, myHash);
    mapSet(&m, "John", 5.4);
    mapSet(&m, "Bob", 4.1);
    mapSet(&m, "Smith", 4.6);
    mapSet(&m, "Peter", 1.4);
    mapSet(&m, "Viet", 7.4);
    mapSet(&m, "Van", 5.2);
    mapSet(&m, "Bac", 3.9);
    mapSet(&m, "Son", 2.7);

    float* v = mapGet(&m, "Peter");

    if (v == NULL) printf("Not found\n");
    else {
        printf("Value: %g\n", *v);
        *v = 22.22;
    }

    v = mapGet(&m, "Peter");

    if (v == NULL) printf("Not found\n");
    else printf("Value: %g\n", *v);

    mapUnset(&m, "Peter");

    mapForEach(&m, printElement);

    mapDestroy(&m);

    return 0;
}
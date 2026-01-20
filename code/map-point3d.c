#include <stdio.h>
#include <stdlib.h>
#include "linked-list.h"

typedef struct {
    float x,y,z;
} Point3D;


typedef int (*Point3DMapHashFunc)(const Point3D, int);

typedef struct {
    int n;
    LinkedList* table;
    Point3DMapHashFunc hashFunc;
} Point3DMap;

typedef struct {
    Point3D key;
    float value;
} Point3DMapData;


int defaultHash(const Point3D p, int n) {
    return ((int)p.x+ (int)p.y + (int)p.z) % n;
}

void mapCreate(Point3DMap* m, int n, Point3DMapHashFunc hashFunc) {
    m->n = n;
    m->table = (LinkedList*)malloc(n * sizeof(LinkedList));
    m->hashFunc = hashFunc == NULL ? defaultHash : hashFunc;

    for (int i = 0; i < n; i++)
        llInit(&(m->table[i]));
}

void mapDestroy(Point3DMap* m) {
    for (int i = 0; i < m->n; i++) {
        for (ListElement* p = m->table[i]; p != NULL; p = p->next) {
            free(p->data);
        }

        llDeleteAll(&(m->table[i]));
    }

    free(m->table);
    m->table = NULL;
}

void mapSet(Point3DMap* m, const Point3D key, float value) {
    int h = m->hashFunc(key, m->n);
    LinkedList* l = &(m->table[h]);

    for (ListElement* p = *l; p != NULL; p = p->next) {
        Point3D pnt = ((Point3DMapData*)p->data)->key;
        if (pnt.x == key.x && pnt.y == key.y && pnt.z == key.z) {
            ((Point3DMapData*)p->data)->value = value;
            return;
        }
    }

    Point3DMapData* d = (Point3DMapData*)malloc(sizeof(Point3DMapData));
    d->key = key;
    d->value = value;
    llInsertHead(l, d, sizeof(Point3DMapData));
}

void mapUnset(Point3DMap* m, const Point3D key) {
    int h = m->hashFunc(key, m->n);
    LinkedList* l = &(m->table[h]);

    for (ListElement* p = *l, *q = NULL; p != NULL; q = p, p = p->next) {
        Point3D pnt = ((Point3DMapData*)p->data)->key;
        if (pnt.x == key.x && pnt.y == key.y && pnt.z == key.z) {
            if (q == NULL)
                llDeleteHead(l);
            else llDeleteAfter(l, q);
            return;
        }
    }
}

float* mapGet(Point3DMap* m, const Point3D key) {
    int h = m->hashFunc(key, m->n);
    LinkedList* l = &(m->table[h]);

    for (ListElement* p = *l; p != NULL; p = p->next) {
        Point3D pnt = ((Point3DMapData*)p->data)->key;
        if (pnt.x == key.x && pnt.y == key.y && pnt.z == key.z) {
            return &(((Point3DMapData*)p->data)->value);
        }
    }

    return NULL;
}

void mapForEach(Point3DMap* m, void (*func)(const Point3DMapData* data)) {
    for (int i = 0; i < m->n; i++){
        for (ListElement* p = m->table[i]; p != NULL; p = p->next) {
            func((Point3DMapData*)p->data);
        }
    }
}


int myHash(const Point3D p, int n) {
    unsigned char* px = (unsigned char*)&p.x;
    unsigned char* py = (unsigned char*)&p.y;
    unsigned char* pz = (unsigned char*)&p.z;

    int m = px[0] + px[1] + px[2] +
            py[0] + py[1] + py[2] +
            pz[0] + pz[1] + pz[2];
    
    return m % n;
}

void printElement(const Point3DMapData* e) {
    printf("(%g, %g, %g): %g\n", e->key.x, e->key.y, e->key.z, e->value);
}

Point3D createPoint3D(float px, float py, float pz){
    Point3D p = {px,py,pz};
    return p;
}

int main() {
    Point3DMap m;

    mapCreate(&m, 4, myHash);

    mapSet(&m, createPoint3D(1.2, 3.5, 2.6), 5.4);
    mapSet(&m, createPoint3D(6.3, 5.4, 3.4), 4.1);
    mapSet(&m, createPoint3D(4.2, 5.3, 8.5), 4.6);
    mapSet(&m, createPoint3D(7.4, 2.5, 5.8), 1.4);
    mapSet(&m, createPoint3D(6.4, 2.9, 3.6), 7.4);
    mapSet(&m, createPoint3D(6.2, 6.8, 9.1), 5.2);
    mapSet(&m, createPoint3D(2.3, 4.8, 2.5), 3.9);
    mapSet(&m, createPoint3D(7.3, 3.6, 8.2), 2.7);

    float* v = mapGet(&m, createPoint3D(7.4, 2.5, 5.8));

    if (v == NULL) printf("Not found\n");
    else {
        printf("Value: %g\n", *v);
        *v = 22.22;
    }

    v = mapGet(&m, createPoint3D(7.4, 2.5, 5.8));

    if (v == NULL) printf("Not found\n");
    else printf("Value: %g\n", *v);

    mapUnset(&m, createPoint3D(7.4, 2.5, 5.8));

    mapForEach(&m, printElement);

    mapDestroy(&m);

    return 0;
}
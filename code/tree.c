#include <stdio.h>
#include <stdlib.h>
#include "linked-list.h"

typedef struct {
    int data;
    LinkedList children;
} TreeNode;



TreeNode* trCreateNode(int data) {
    TreeNode* t = (TreeNode*)malloc(sizeof(TreeNode));
    t->data = data;
    llInit(&(t->children));
    return t;
}


TreeNode* trDuplicateNode(TreeNode* n){
    TreeNode* t= trCreateNode(n->data);
    for(ListElement* p=n->children;p != NULL; p=p->next){
        TreeNode* c = trDuplicateNode(*(TreeNode**)p->data);
        trAddChildNode(t,c);
    }

    return t;
}


void trDestroyNode(TreeNode* t, int recursive);

void __destroyChildNode(void* data, int size) {
    TreeNode* child = *(TreeNode**)data;
    trDestroyNode(child, 1);
}

void trDestroyNode(TreeNode* t, int recursive) {
    if (recursive) {
        llForEach(t->children, __destroyChildNode);
    }

    llDeleteAll(&(t->children));
    free(t);
}


// non-possessive
void trAddChildNode(TreeNode* p, TreeNode* c) {
    llInsertTail(&(p->children), &c, sizeof(TreeNode*));
}


void trRemoveChildNode(TreeNode* p, TreeNode* c, int recursive) {
    ListElement* prev = NULL;
    for (ListElement* curr = p->children; curr != NULL;prev = curr, curr = curr->next) {
        TreeNode* child = *(TreeNode**)(curr->data);
        if (child == c) {
            if (prev == NULL) {
                llDeleteHead(&(p->children));
            } else {
                llDeleteAfter(&(p->children), prev);
            }

            if (recursive) {
                trDestroyNode(c, 1);
            }

            return;
        }
    }
}


TreeNode* trFindNode(TreeNode* r, int data){
    if(r->data == data) return r;

    for(ListElement* p = r->children; p!= NULL, p = p->next){
        TreeNode* f= trFindNode(*(TreeNode**)p->data,data);
        if(f != NULL) return f;
    }

    return NULL;
}


int main() {

    TreeNode* a = trCreateNode(10);
    TreeNode* b = trCreateNode(20);
    TreeNode* c = trCreateNode(30);

    TreeNode* d = trCreateNode(40);
    TreeNode* e = trCreateNode(50);

    TreeNode* f = trCreateNode(60);
    TreeNode* g = trCreateNode(70);
    
    trAddChildNode(a, b);
    trAddChildNode(a, c);

    trAddChildNode(b, d);
    trAddChildNode(b, e);

    trAddChildNode(e,f);
    trAddChildNode(e,g);

    printf("a: %d\n", a->data);

    printf("b: %d\n", (*(TreeNode**)(a->children->data))->data);

    printf("c: %d\n", (*(TreeNode**)(a->children->next->data))->data);

    trRemoveChildNode(
        *(TreeNode**)(a->children->data),
        *(TreeNode**)(
                (*
                    (TreeNode**)(
                        a->children->data
                    )
                )->children->data
        ),0);


    TreeNode* a2= trDuplicateNode(a);
    
    printf("d: %d\n",
        (*
            (TreeNode**)(
                (*
                    (TreeNode**)(
                        a2->children->data
                    )
                )->children->data
            )
        )->data);

    
    printf("e: %d\n",
        (*
            (TreeNode**)
                (*
                    (TreeNode**)(
                        a2->children->data
                    )
                )->children->next->data
            )->data);
    
    
    return 0;
}
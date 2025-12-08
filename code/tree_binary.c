#include <stdio.h>
#include <memory.h>
#include <stdlib.h>

typedef struct __BTNode{
    int data;
    struct __BTNode *left,*right;
}BTNode;

BTNode* btCreatNode(int data){
    BTNode* t = (BTNode*)malloc(sizeof(BTNode));
    t->data=data;
    t->left=NULL;
    t->right=NULL;
    return t;
}

BTNode* btCreatNodeWithChildern(int data, BTNode* left, BTNode* right){
    BTNode* t = (BTNode*)malloc(sizeof(BTNode));
    t->data=data;
    t->left=left;
    t->right=right;
    return t;
}

void btSetLeftChild(BTNode* p,BTNode* c){
    p->left=c;
}

void btSetRightChild(BTNode* p, BTNode* c){
    p->right=c;
}

void btDestroyNode(BTNode*n,int recursive){
    if(recursive){
        if(n->left) btDestroyNode(n->left,1);
        if(n->right) btDestroyNode(n->right,1);
    }

    free(n);
}

int btIsLeaf(BTNode* n){
    return (n->left == NULL) && (n->right == NULL);
}

int btChildCount(BTNode* n){
    // int count=0;
    // if(n->left != NULL) count++;
    // if(n->right != NULL) count++;

    // return count;

    return (n->left != NULL) + (n->right != NULL);
}

BTNode* btLeftMost(BTNode* n){
    if(n == NULL) return NULL;
    while(n->left != NULL){
        n = n->left;
    }
    return n;
}

BTNode* btRightMost(BTNode* n){
    if(n == NULL) return NULL;
    while(n->right != NULL){
        n = n->right;
    }
    return n;
}

int main(){
    // BTNode* a=btCreatNode(10);
    // BTNode* b=btCreatNode(20);
    // BTNode* c=btCreatNode(30);
    // BTNode* d=btCreatNode(40);
    // BTNode* e=btCreatNode(50);
    // BTNode* f=btCreatNode(60);

    // btSetLeftChild(a,b);
    // btSetRightChild(a,c);

    // btSetLeftChild(b,d);
    // btSetRightChild(b,e);

    // btSetRightChild(e,f);

    BTNode* a= btCreatNodeWithChildern(10,
        btCreatNodeWithChildern(20,
            btCreatNodeWithChildern(40,
                NULL,
                NULL
            ),
            btCreatNodeWithChildern(50,
                NULL,
                btCreatNodeWithChildern(60,
                    NULL,
                    NULL
                )
            )
        ),
        btCreatNodeWithChildern(30,
            NULL,
            NULL
        )
    );

    // printf("a: %d\n",a->data);
    // printf("c: %d\n",a->right->data);
    // printf("f: %d\n",a->left->right->right->data);

    printf("Left: %d\n", btLeftMost(a)->data);
    printf("Right: %d\n", btRightMost(a)->data);

    return 0;
}
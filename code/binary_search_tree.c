#include <stdio.h>
#include <memory.h>
#include <stdlib.h>

typedef struct __BSTNode {
    int data;
    struct __BSTNode *left, *right;
} BSTNode;


void bstInsertNode(BSTNode** n, int x) { 
  if (*n == NULL) {
    *n = (BSTNode*)malloc(sizeof(BSTNode));
    (*n)->data = x;
    (*n)->left = NULL;
    (*n)->right = NULL;
  } else if (x < (*n)->data)
    bstInsertNode(&(*n)->left, x);
  else if (x > (*n)->data)
    bstInsertNode(&(*n)->right, x);
} 

BSTNode* bstSearch(BSTNode* n, int x) {
  if (n == NULL) return NULL;
  if (n->data == x) return n;

  if (n->data > x) return bstSearch(n->left, x);
  return bstSearch(n->right, x);
}

void bstDestroy(BSTNode* n) {
    if (n->left) bstDestroy(n->left);
    if (n->right) bstDestroy(n->right);
    free(n);
}

void bstDeleteNode(BSTNode** n, int value) {//khai báo hàm xóa 1 node
    while ((*(n))->data != value) {//viết vòng lặp tìm địa chỉ của node có giá trị là v
        if (value < (*(n))->data) {// nếu v < giá trị của node hiện tại đang xét
            n = &(*(n))->left;//đi về bên trái
        } else {
            n = &(*(n))->right;//đi về bên phải
        }
    }
    BSTNode* node = *n;//lưu lại địa chỉ của node hiện tại
    if((*n)->left == NULL && (*n)->right==NULL){//Nếu node tìm được không có con
        *n = NULL;//gán địa chỉ của node bằng NULL
        free(node);//Xóa node đó đi
        return;
    }
    if((*n)->left != NULL && (*n)->right == NULL){//Nếu có con bên trái
        *n = (*n)->left;//gán địa chỉ của node hiện tại bằng con bên trái
        free(node);//xóa node đó
        return;
    }
    if((*n)->left == NULL && (*n)->right != NULL){//Nếu có con bên phải
        *n = (*n)->right;//gán địa chỉ của node hiện tại bằng con bên phải
        free(node);//xóa node đó đi
        return;
    }
}

int main() {
    BSTNode* b = NULL;
    bstInsertNode(&b, 6);
    bstInsertNode(&b, 2);
    bstInsertNode(&b, 7);
    bstInsertNode(&b, 5);
    bstInsertNode(&b, 3);
    bstInsertNode(&b, 9);
    bstInsertNode(&b, 1);
    bstInsertNode(&b, 8);
    bstInsertNode(&b, 4);

    BSTNode* n = bstSearch(b, 4);
    printf("%d\n", n->data);

    bstDestroy(n);
    return 0;
}
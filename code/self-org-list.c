#include <stdio.h>
#include "linked-list.h"

typedef LinkedList SelfOrgList;

void solInit(SelfOrgList* l) {// viết hàm khởi tạo SelOrg
    llInit(l);// viết lệnh khởi tạo như khởi tạo Linked List
}


void solAppend(SelfOrgList* l, float v) {// viết hàm thêm dữ liệu vào SelOrg
    llInsertHead(l,v);// thêm dữ liệu như thêm dữ vào đầu đầu LinkedList
}


void solSearch(SelfOrgList* l, float v) { // viết hàm solSearch
    // ListElement* now;
    // for(now = *l;now->data != v && now->next != NULL; now = now->next);
    
    // llDeleteAt(l,now);

    // llInsertHead(l,v);

    llInsertHead(l,v);//Tạo 1 ListElement mới với giá trị cần Search vào đầu của List 

    ListElement* now;// khởi tạo 1 ListElement tên now
    for(now = (*l);now->next->data != v && now->next->next != NULL; now = now->next);
    // vòng lặp for để đi tìm phần tử đứng trước phần tử mang giá trị cần tìm
    //gán now là phần tử đầu của list
    // lặp với điều kiện giá trị của listElement tiếp theo không phải giá trị cần tìm và listElement tiếp theo chưa NULL
    // sau mỗi vòng lặp gán con trỏ now vào phần tử tiếp theo
    
    llDeleteAfter(l,now);// xóa listElement đằng sau con trỏ now

}

void solDestroy(SelfOrgList* l) {// viết hàm xóa toàn bộ SelfOrg
    llDeleteAll(l);// gọi hàm xóa toàn bộ list
}

int main() {
    SelfOrgList l;
    solInit(&l);

    solAppend(&l, 1);
    solAppend(&l, 7);
    solAppend(&l, 5);
    solAppend(&l, 8);
    solAppend(&l, 2);
    solAppend(&l, 4);

    printList(l);
    // print list

    solSearch(&l, 5);
    printList(l);
    solSearch(&l, 5);
    printList(l);
    solSearch(&l, 2);
    printList(l);

    // print list

    solDestroy(&l);

    return 0;
}
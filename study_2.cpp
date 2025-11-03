#include <stdio.h>
#include <stdlib.h>
typedef struct __ListElement {
    float data;
    struct __ListElement* next;
} ListElement;
typedef ListElement* LinkedList;
void llInit(LinkedList* pl) {
    *pl = NULL;
}
void llInsertHead(LinkedList* pl, float v) {
    ListElement* e = (ListElement*)malloc(sizeof(ListElement));
    e->data = v;
    e->next = *pl;
    *pl = e;
}
void llInsertTail(LinkedList* pl, float v) {
    ListElement* e = (ListElement*)malloc(sizeof(ListElement));
    e->data = v;
    e->next = NULL;

    if (*pl == NULL) {
        *pl = e;
    } else {
        ListElement* last;
        for (last = *pl; last->next != NULL; last = last->next);
        last->next = e;
    }
}
void llInsertAfter(LinkedList* pl, ListElement* a, float v) {
    if (a == NULL) return;   
    ListElement* e = (ListElement*)malloc(sizeof(ListElement));
    e->data = v;
    e->next = a->next;
    a->next = e;
}
void llDeleteHead(LinkedList* pl) {
    if (*pl == NULL) return;//nếu danh sách rỗng bỏ qua hàm xóa phần tử đầu
    ListElement* e = (*pl)->next;//tạo con trỏ tạm e trỏ đến phần tử thứ 2
    free(*pl);//xóa phần tử đầu tiên
    *pl = e;//gán ptu đầu tiên bằng con trỏ e
}
void llDeleteTail(LinkedList* pl) {
    if (*pl == NULL) return;//nếu danh sách rỗng bỏ qua hàm xóa phần tử cuối
    if ((*pl)->next == NULL) {//nếu sau phần tử đầu là null
        free(*pl);//xóa luôn ptu đầu
        *pl = NULL;//cho danh sách rỗng
        return;
    }
    ListElement* last2;//tạo con trỏ last2
    for (last2 = *pl; last2->next->next != NULL; last2 = last2->next);//for(khởi tạo last2 trỏ đến ptu đầu
                                                                    //kiểm tra ptu kế tiếp của ptu kế tiếp khác NULL không
                                                                    //gán last2 = ptu kế tiếp)

    free(last2->next);//giải phóng ptu cuối cùng last2->last->NULL
    last2->next = NULL;//gán ptu cuối thứ 2 thành NULL
}
void llDeleteAfter(LinkedList* pl, ListElement* a) {
    if (a == NULL || a->next == NULL) return;//kiểm tra con trỏ a có NULL 
                                             //hoặc a->next có NULL không
                                             //bỏ qua hàm xóa sau vị trí a
    ListElement* p = a->next->next;//tạo con trỏ p trỏ đến ptu sau ptu cần xóa
    free(a->next);//giải phóng phần tử sau a(phần tử cần xóa)
    a->next = p;//gấn con trỏ a-> next đến ptu p(ptu sau ptu đã xóa)
}
void llDeleteAll(LinkedList* pl) {
    ListElement *p, *q;//tạo 2 con trỏ p và q
    for (p = *pl; p != NULL; p = q) {//for(khởi tạo con trỏ p trỏ đến ptu đầu tiên
                                     //    kiểm tra p có bằng NULL  không
                                     //    gán p = q)
        q = p->next;//gán q trỏ đến ptu kế tiếp của p
        free(p);//giải phóng ptu mà p trỏ
    }
    *pl = NULL;//gán danh sách rỗng
}
int llCount(LinkedList l) {
    int n = 0;
    for (ListElement* p = l; p != NULL; p = p->next)
        n++;
    return n;
}
// ListElement* llSeek(LinkedList l, int i) {
//     ListElement* p;
//     for (p = l; i > 0 && p != NULL; p = p->next)
//         i--;
//     return p;
// }
// void llForEach(LinkedList l, void (*func)(float data)) {
//     for (ListElement* p = l; p != NULL; p = p->next)
//         func(p->data);
// }
// void printElement(float data) {
//     printf("%f ", data);
// }
void llDeleteAt(LinkedList* pl, ListElement* a) {
    if (a == NULL || *pl == NULL) return;//kiểm tra con trỏ a có NULL không hoặc là danh sách rỗng 
                                         //bỏ qua hàm xóa tại vị trí
    if (a == *pl) { //nếu con trỏ a trỏ đến phần tử đầu tiên
        llDeleteHead(pl);//gọi hàm xóa phần tử đầu tiên
    }
}

int main() {
    LinkedList l;

    llInit(&l);

    llInsertTail(&l, 60);//p->60->NULL

    // llInsertHead(&l, 10);//p->10->60->NULL
    // llInsertHead(&l, 20);//p->20->10->60->NULL

    // llInsertTail(&l, 50);//p->20->10->60->50->NULL

    ListElement* a = l;
    // llInsertAfter(&l, a, 100);
    llDeleteAt(&l, a);

    llDeleteAll(&l);
    
    return 0;
}
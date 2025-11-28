#include<stdio.h>
#include<string.h>

int __search_range(const char* a[], int l,int r,const char* v){
    if (l > r) return -1;

    int m = (l+r) / 2;

    int check = strcmp(a[m],v);

    if(check == 0) return m;

    if(check < 0) return __search_range(a,m+1,r,v);

    return __search_range(a,l, m-1,v);
}

int binary_search(const char* a[], int n,const char* v){
    return __search_range(a,0,n-1,v);
}

int main(){
    const char* a[]={
        "about",
        "car",
        "cat",
        "dog",
        "foot",
        "football",
        "group",
        "hat",
        "ten",
        "yell",
        "zoo"
    };

    const int n =sizeof(a)/ sizeof(a[0]);

    int i = binary_search(a,n,"football");

    printf("%d",i);
}
#include <stdio.h>

int search(char* str, int n, char v) {
    str[n] = v;

    int t;

    for (t = 0; v != str[t]; t++);

    str[n] = 0;
    
    return t < n ? t : -1;
}

int main(){
    
    return 0;
}
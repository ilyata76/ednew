#include <iostream>
#include <string.h>

int my_strlen1(char a[]) {
    int i;
    for (i = 0; a[i] != 0; i++);
    return i;
}

void my_strcpy1(char a[], char b[]) {
    for (int i = 0; (a[i] = b[i]) != 0; i++);
}

int my_strcmp1(char a[], char b[]) {
    int i;
    for (i = 0; a[i] == b[i] != 0; i++);
    if (a[i] == 0) return 0;
    return a[i] - b[i];
}

void my_strcat1(char a[], char b[]) {
    my_strcpy1(a + my_strlen1(a), b);
}


int my_strlen2(char* a) {
    char* b = a;
    while (*b++);
    return b-a-1;
}

void my_strcpy2(char* a, char* b) {
    while (*a++ = *b++);
}

int my_strcmp2(char* a, char* b) {
    while (*a++ == *b++)
        if (*(a - 1) == 0) 
            return 0;

    return *(a - 1) - *(b - 1);
}

void demonstrate() {
    char a[255] = "aaa\0";
    char b[255] = "bbb\0";
    std::cout << my_strlen1("abobus") << '\n'; // 6
    std::cout << my_strcmp1(a, b) << '\n'; // -1
    my_strcpy1(a, b);    
    std::cout << a << '\n'; // bbb

    my_strcat1(a, b);
    std::cout << a << '\n'; // bbbbbb
    
    std::cout << my_strlen2(a) << '\n'; // 6
    my_strcpy2(b, a);      
    std::cout << b << '\n'; // bbbbbb

    std::cout << my_strcmp2(a , b); // 0
}


static const int N = 10000;

int main(int argc, char** argv) {
    // demonstrate();


    // ищем вхождение слова в текст

    int i; char t;
    char a[N], *p = argv[1];

    for (i = 0; i < N - 1; a[i] = t, i++)
        if (!std::cin.get(t)) /*ctrl Z*/ {
            break;
        }

    a[i] = 0;

    for (i = 0; a[i] != 0; i++) {
        int j;
        for (j = 0; p[j] != 0; j++)
            if (a[i + j] != p[j])
                break;

        if (p[j] == 0) 
            std::cout << i << " ";
    }
    std::cout << std::endl;

    //asdgl;'jsdaf gk;ljdfg k;jdfg l;kcgl; dfg;l abob asdkjsadfgk jsadglk abob
    //^Z
    //43 68

    // asdfkjsaflkabobaskdlfjnasdlk asdfklj abob
    // ^Z
    // 11 37

}
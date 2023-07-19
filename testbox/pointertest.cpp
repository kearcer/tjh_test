#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <climits>
#include <string.h>

int main()
{
    char C[4] = {4, 3, 2, 1};
    char *p;
    C[0] = '0';
    C[1] = '1';
    C[2] = '2';
    C[3] = '3';
    C[4] = '4';
    C[5] = '5';
    C[6] = '6';
    C[7] = '\n';

    printf("sizeof:%d\n", sizeof(C));
    printf("strlen:%d\n", strlen(C)); //不管C定义的多长，会一直在内存中访问直到获取一个\n
    printf("string C is %c\n", *C);
    printf("string C+1 is %c\n", *C + 1);
    printf("string C[2] is %c\n", C[2]);

    printf("string address C is %p\n", C);
    printf("string address C+1 is %p\n", (C + 1));

    p = C;

    printf("P address:%p\n", p);
    printf("P++ address:%p\n", p + 1);

    char A[2][3] = {{1, 2, 3},
                    {4, 5, 6}};
    printf("A address: %p\n", A);
    printf("A + 1 address: %p\n", A + 1);
    printf("A[0][1] address: %p\n", &A[0][1]);
    printf("A[1] address: %p\n", A[1]);
    printf("A[1][0] address: %p\n", &A[1][0]);

    printf("--------------------------------\n");

    printf("A: %d\n", *A[0]);
    printf("A + 1 : %d\n", *A[0] + 1);
    printf("A[0][1] : %d\n", A[0][1]);
    printf("A[1] : %d\n", *A[1]);
    printf("A[1][0] : %d\n", A[1][0]);
    printf("A[2][0] : %d\n", A[2][0]);

    printf("--------------------------------\n");

    char(*b)[3] = A;
    printf("b: %d\n", *b[0]);
    printf("b + 1 : %d\n", *b[0] + 1);
    printf("b[0][1] : %d\n", b[0][1]);
    printf("b[1] : %d\n", *b[1]);
    printf("b[1][0] : %d\n", b[1][0]);
    printf("b[2][0] : %d\n", b[2][0]);

    return 0;
}
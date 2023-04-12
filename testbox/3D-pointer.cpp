#include <stdio.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <climits>

int main()
{
    int A[3][2][2] = {{{1, 4}, {6, 8}}, {{1, 2}, {3, 4}}, {{12, 14}, {16, 18}}};
    printf("A = %p\n", A);
    printf("*A = %p\n", *A);
    printf("&A[0] = %p\n", &A[0]);
    printf("&A[0][0] = %p\n", &A[0][0]);
    printf("&A[0][0][0] = %p\n", &A[0][0][0]);
    printf("&A[1] = %p\n", &A[1]);
    printf("&A[1][0] = %p\n", &A[1][0]);
    printf("&A[1][0][0] = %p\n", &A[1][0][0]);
    printf("&A[2] = %p\n", &A[2]);
    printf("&A[2][0] = %p\n", &A[2][0]);
    printf("&A[2][0][0] = %p\n", &A[2][0][0]);

    printf("\n");
    printf("{{{%p,%p},\n{%p,%p}}\n,{{%p,%p}\n,{%p,%p}}\n,{{%p,%p}\n,{%p,%p}}}\n",
           &A[0][0][0], &A[0][0][1], &A[0][1][0], &A[0][1][1],
           &A[1][0][0], &A[1][0][1], &A[1][1][0], &A[1][1][1],
           &A[2][0][0], &A[2][0][1], &A[2][1][0], &A[2][1][1]);

    printf("&A[2][1][1] = %p\n", &A[2][1][1]);
    printf("A = %p\n", A);
    printf("*A = %p\n", *A);

    return 0;
}
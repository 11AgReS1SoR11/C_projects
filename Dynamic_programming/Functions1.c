#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "Laba1.h"
#pragma warning(disable:4996)

/*
* Create massive N*M
*/
int** dynamic_array_alloc(int N, int M) 
{    
    int** A = (int**)malloc(N * sizeof(int*));
    if (A == NULL) return NULL;
    for (int i = 0; i < N; i++) 
    {
        A[i] = (int*)calloc(M, sizeof(int));
        if (A == NULL) return NULL;
    }
    return A;
}

/*
* free massive N*M
*/
void dynamic_array_free(int** A, int N) 
{
    for (int i = 0; i < N; i++) free(A[i]);
    free(A);
}

/*
* the function finds the minimum in the array
*/
int search_min(int n, int* A) 
{
    int MIN = A[1];
    for (int i = 1; i <= n; i++)
        if (A[i] < MIN) MIN = A[i];

    return MIN;
}

void solve(int n, int m, int** A) 
{
    int** dp = dynamic_array_alloc(n + 1, m + 2);
    for (int i = 0; i <= n; i++) dp[i][0] = 10e8;      // base
    for (int i = 0; i <= n; i++) dp[i][m + 1] = 10e8;  // base

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            dp[i][j] = min(min(dp[i - 1][j + 1], dp[i - 1][j]), dp[i - 1][j - 1]) + A[i][j];

    printf("Ответ: %d\n", search_min(m, dp[n]));
    dynamic_array_free(dp, n + 1);
}
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "Laba1.h"
#pragma warning(disable:4996)

int main() {
    setlocale(LC_ALL, "Rus");
    int n, m;
    printf("¬ведите\nn = ");
    scanf("%d", &n);
    printf("m = ");
    scanf("%d", &m);
    int** A = dynamic_array_alloc(n+1, m+1);
    printf("¬ведите матрицу:\n");
    for (int i = 1; i <= n; i++) 
        for (int j = 1; j <= m; j++) 
            scanf("%d", &A[i][j]);

    solve(n, m, A);
    dynamic_array_free(A, n);
	return 0;
}
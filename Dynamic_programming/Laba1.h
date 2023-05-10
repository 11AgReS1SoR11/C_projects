#pragma once

int** dynamic_array_alloc(int N, int M);
void dynamic_array_free(int** A, int N);
void solve(int n, int m, int** A);
int search_min(int n, int* A);

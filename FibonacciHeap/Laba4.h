#pragma once
#include <stdbool.h>

typedef struct _NODE {
    int key;
    int degree;
    struct _NODE* left;
    struct _NODE* right;
    struct _NODE* parent;
    struct _NODE* child;
    bool mark;
    bool visited;
} NODE;

typedef struct _Fibanocci_Heap {
    int size;
    NODE* min;
} Fibanocci_Heap;

Fibanocci_Heap* Create_heap();
void Insert(Fibanocci_Heap* H, int val);
Fibanocci_Heap* unionHeap(Fibanocci_Heap* H1, Fibanocci_Heap* H2);
void swap(NODE* a, NODE* b);
int extract_min(Fibanocci_Heap* H);
void Delete_Node(Fibanocci_Heap* H, int del_key);
void print_heap(NODE* head);
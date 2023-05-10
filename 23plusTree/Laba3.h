#pragma once

typedef struct _Tree_plus {
	int data_1;
	int data_2;
	struct _Tree_plus* left;
	struct _Tree_plus* middle;
	struct _Tree_plus* right;
}Tree_plus;

typedef struct _Listlink {
	int size;
	Tree_plus* head;
	Tree_plus* tail;
} Listlink;

typedef Listlink* List;

List Create_List();
Tree_plus* Find(Tree_plus* A, int val);
void Push_front(List List_of_tree, Tree_plus* new_node);
void Push_back(List List_of_tree, Tree_plus* new_node);
void Insert_Tree(Tree_plus** A, int val, List List_of_tree);
int** dynamic_array_alloc(int N, int M);
void dynamic_array_free(int** arr, int N);
void height(Tree_plus* A, int* h);
void Print_Tree(Tree_plus* A, int n);
void Print_List(List list);
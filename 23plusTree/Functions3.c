#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>
#include "Laba3.h"
#pragma warning(disable:4996)
#define INF INT_MAX
#define INT_NULL INT_MIN
#define INT_EMPTY INT_MIN + 1

/*
* A little bit about the concept of a tree: each vertex has 2 or 3 sons => 
* if there are 2 sons, then they will be written to the left and middle subtree.
* At the same time, the leaves are linked into a doubly linked list. For leaves, 
* all 3 pointers are NULL, and without creating any additional data structures, 
* you can write a pointer to the left leaf in the left subtree, and to the 
* right - to the right.
* Now the leaf has an average pointer equal to NULL - a check on the leaf, 
* and in other cases the average pointer is always != NULL.
*/

/*
* node creation function: since there can be from 1 to 2 values in a node, 
* by default the second value is equal to infinity (this means that there 
* is no second value)
*/
Tree_plus* Create_node(int val) 
{
	Tree_plus* A = (Tree_plus*)malloc(sizeof(Tree_plus));
	if (A == NULL) 
	{
		puts("No memory abailable");
		return NULL;
	}
	A->data_1 = val;
	A->data_2 = INF;
	A->left = NULL;
	A->middle = NULL;
	A->right = NULL;
	return A;
}


/*
* Creating a List
*/
List Create_List() 
{
	List tmp = (List)malloc(sizeof(Listlink));
	if (tmp == NULL) 
	{ 
		printf("No memory avaible.\n"); 
		return NULL; 
	}
	tmp->size = 0;
	tmp->head = tmp->tail = NULL;

	return tmp;
}

/*
* checking on a leaf 
*/
int Check_for_leaf(Tree_plus* A) 
{
	return A != NULL && (A->middle == NULL);
}

/*
* checking on an empty tree 
*/
int Is_empty(Tree_plus* A) 
{
	return (A == NULL);
}

/*
* checking on 2 sons
*/
int Check_for_two_sons(Tree_plus* A) 
{
	return (A->right == NULL) && Check_for_leaf(A->middle);
}

/*
* checking on 3 sons
*/
int Check_for_tree_sons(Tree_plus* A) 
{
	return (A->right != NULL) && Check_for_leaf(A->middle);
}

/*
* swaps the values of elements in places
*/
void swap(int* a, int* b) 
{
	(*a) ^= (*b) ^= (*a) ^= (*b);
}

/*
* the function finds a sheet with the value val and returns a pointer to it
*/
Tree_plus* Find(Tree_plus* A, int val) 
{
	if (A == NULL) return NULL;
	if (Check_for_leaf(A) && A->data_1 == val) return A;
	if (val <= A->data_1) return Find(A->left, val);
	else if (val > A->data_2) return Find(A->right, val);
	else return Find(A->middle, val);
}

/*
* the function of adding to the tree
* The forward recursion path finds a node to which a new leaf with the value 
* val will be added. 2 cases can be realized: 1) this node has 2 sons - I
* add a third one 2) node has 3 sons - I do balancing. On the reverse course 
* of the recursion, I correct all the vertices so that all the leaves are 
* at the same height
*/
Tree_plus* Add_Tree(Tree_plus** A, int val) 
{
	// The forward recursion path finds a node to which a new leaf with the 
	// value val will be added. 2 cases can be realized : 1) this node has 
	// 2 sons - we add a third one 2) node has 3 sons - we do balancing.
	// On the reverse course of the recursion, we correct all the vertices 
	// so that all the leaves are at the same height
	if (Check_for_two_sons(*A)) 
	{
		if (val < (*A)->data_1) 
		{
			(*A)->right = (*A)->middle;
			(*A)->middle = (*A)->left;
			(*A)->left = Create_node(val);
		}
		else if (val <= (*A)->middle->data_1) 
		{
			(*A)->right = (*A)->middle;
			(*A)->middle = Create_node(val);
		}
		else 
		{
			(*A)->right = Create_node(val);
		}

		(*A)->data_2 = (*A)->middle->data_1;
		(*A)->data_1 = (*A)->left->data_1;
		return NULL;
	}

	// If there are 3 sons, then now the node has 2 sons, and they, in turn, 
	// have 2 leaves.Depending on where you need to add a new sheet, different 
	// options may be implemented
	if (Check_for_tree_sons(*A)) 
	{
		Tree_plus* A_left, * A_middle;

		if (val < (*A)->data_1) 
		{
			A_left = Create_node(val);
			A_middle = Create_node((*A)->data_2);

			A_left->left = Create_node(val);
			A_left->middle = (*A)->left;
			A_middle->left = (*A)->middle;
			A_middle->middle = (*A)->right;

		}
		else if (val > (*A)->right->data_1) 
		{
			A_left = Create_node((*A)->data_1);
			A_middle = Create_node((*A)->right->data_1);

			A_left->left = (*A)->left;
			A_left->middle = (*A)->middle;
			A_middle->left = (*A)->right;
			A_middle->middle = Create_node(val);

			(*A)->data_1 = (*A)->data_2;
		}
		else if (val > (*A)->middle->data_1) 
		{
			A_left = Create_node((*A)->data_1);
			A_middle = Create_node(val);

			A_left->left = (*A)->left;
			A_left->middle = (*A)->middle;
			A_middle->left = Create_node(val);
			A_middle->middle = (*A)->right;

			(*A)->data_1 = (*A)->data_2;
		}
		else 
		{
			A_left = Create_node((*A)->data_1);
			A_middle = Create_node((*A)->data_2);

			A_left->left = (*A)->left;
			A_left->middle = Create_node(val);
			A_middle->left = (*A)->middle;
			A_middle->middle = (*A)->right;

			(*A)->data_1 = val;
		}

		(*A)->data_2 = INF;
		(*A)->right = NULL;
		(*A)->left = A_left;
		(*A)->middle = A_middle;
		return (*A);
	}

	Tree_plus* check;
	if (val < (*A)->data_1) 
	{
		check = Add_Tree(&((*A)->left), val);
	}
	else if (val > (*A)->data_2) 
	{
		check = Add_Tree(&((*A)->right), val);
	}
	else 
	{
		check = Add_Tree(&((*A)->middle), val);
	}

	// reverse recursion
	// This recursive function returns a pointer to the node that was raised 
	// after balancing(otherwise a pointer to NULL).If there is only 1 value 
	// in the node, then I simply add the node that has risen, otherwise, I 
	// do balancingand raise it further(Depending on where the node has risen 
	// from, various variations can be implemented)

	if (check == NULL) return NULL; // Nothing went up

	// It has risen, but in node 1 value
	if (check != NULL && (*A)->data_2 == INF) 
	{ 
		(*A)->data_2 = check->data_1;
		if (check->data_1 > (*A)->data_1) 
		{
			(*A)->middle = check->left;
			(*A)->right = check->middle;
		}
		else 
		{
			swap(&(*A)->data_1, &(*A)->data_2);
			(*A)->right = (*A)->middle;
			(*A)->middle = check->middle;
			(*A)->left = check->left;
		}
		return NULL;
	}

	// It has risen, but in node 2 value
	if (check != NULL && (*A)->data_2 != INF) 
	{ 
		if (check == (*A)->left) 
		{
			Tree_plus* extra = Create_node((*A)->data_2);
			extra->middle = (*A)->right;
			extra->left = (*A)->middle;

			(*A)->data_2 = INF;
			(*A)->right = NULL;
			(*A)->left = check;
			(*A)->middle = extra;
		}
		else if (check == (*A)->right) 
		{
			Tree_plus* extra = Create_node((*A)->data_1);
			extra->middle = (*A)->middle;
			extra->left = (*A)->left;

			(*A)->data_1 = (*A)->data_2;
			(*A)->data_2 = INF;
			(*A)->right = NULL;
			(*A)->left = extra;
			(*A)->middle = check;
		}
		else 
		{
			Tree_plus* extra = Create_node((*A)->data_2);
			extra->left = check->right;
			extra->middle = (*A)->right;
			check->data_1 = (*A)->data_1;
			check->middle = check->left;
			check->left = (*A)->left;

			(*A)->data_2 = INF;
			(*A)->data_1 = check->data_1;
			(*A)->right = NULL;
			(*A)->left = extra;
			(*A)->middle = check;
		}
		return (*A);
	}
}

/*
* The function of adding to the top of the list
*/
void Push_front(List List_of_tree, Tree_plus* new_node) 
{
	new_node->right = List_of_tree->head;
	List_of_tree->head->left = new_node;
	List_of_tree->head = new_node;
	List_of_tree->size++;
}

/*
* The function of adding to the end of the list
*/
void Push_back(List List_of_tree, Tree_plus* new_node) 
{
	new_node->left = List_of_tree->tail;
	List_of_tree->tail->right = new_node;
	List_of_tree->tail = new_node;
	List_of_tree->size++;
}

/*
* The function of adding to the list
*/
void Insert_List(List List_of_tree, Tree_plus* new_node) 
{
	// If the list is empty
	if (List_of_tree == NULL) 
	{
		List_of_tree = Create_List();
		return;
	}
	if (List_of_tree->head == NULL) 
	{
		List_of_tree->tail = List_of_tree->head = new_node;
		List_of_tree->size++;
		return;
	}

	// Search for the element after which to insert
	Tree_plus* B = List_of_tree->head;
	while (B != NULL && B->data_1 < new_node->data_1)
		B = B->right;

	if (B == List_of_tree->head) 
	{
		Push_front(List_of_tree, new_node);
	}
	else if (B == NULL)
	{
		Push_back(List_of_tree, new_node);
	}
	else 
	{
		B->left->right = new_node;
		new_node->left = B->left;
		new_node->right = B;
		B->left = new_node;
		List_of_tree->size++;
	}
}

/*
* This is a general function that first adds an element 
* to the tree, and then to the list
*/
void Insert_Tree(Tree_plus** A, int val, List List_of_tree) 
{
	// If there are less than two elements in the tree, 
	// then it is not a 2-3+ tree -> processed separately
	if (List_of_tree->size < 2) 
	{
		// an empty tree
		if (Is_empty(*A)) 
		{ 
			(*A) = Create_node(val);
			Insert_List(List_of_tree, (*A));
		}
		// tree has 1 element
		else 
		{ 
			if (val > (*A)->data_1) 
			{
				(*A)->left = Create_node((*A)->data_1);
				(*A)->middle = Create_node(val);
			}
			else 
			{
				(*A)->left = Create_node(val);
				(*A)->middle = Create_node((*A)->data_1);
				(*A)->data_1 = val;
			}
			List_of_tree->head = (*A)->left;
			List_of_tree->tail = (*A)->middle;
			List_of_tree->head->right = List_of_tree->tail;
			List_of_tree->tail->left = List_of_tree->head;
			List_of_tree->size++;
		}
		return;
	}
	Add_Tree(A, val);
	Tree_plus* new_node = Find(*A, val);
	if (new_node == NULL) return;
	Insert_List(List_of_tree, new_node);
}

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
		if (A[i] == NULL) return NULL;
		for (int j = 0; j < M; j++) A[i][j] = INT_EMPTY;
	}
	return A;
}

/*
* Free massive N*M
*/
void dynamic_array_free(int** arr, int N) {
	while (N--) free(arr[N]);
	free(arr);
}

/*
* Fills auxiliary matrices with tree values
*/
void Take_elems(Tree_plus* A, int** arr1, int** arr2, int y, int x, int delta) 
{
	// If there is no son, then reflect it in auxiliary matrices
	if (A == NULL) 
	{
		arr1[y][x] = arr2[y][x] = INT_NULL;
		return;
	}

	// If you have reached the sheet, then write down the values and return
	if (Check_for_leaf(A)) 
	{
		arr1[y][x] = A->data_1;
		arr2[y][x] = A->data_2;
		return;
	}

	Take_elems(A->left, arr1, arr2, y + 1, x - delta, delta / 3);
	// Reverse recursion - fill in the values of the parents
	arr1[y][x] = A->data_1;
	arr2[y][x] = A->data_2;
	Take_elems(A->middle, arr1, arr2, y + 1, x, delta / 3);
	Take_elems(A->right, arr1, arr2, y + 1, x + delta, delta / 3);
}

/*
* The function returns the height of the tree (a tree from one element: 
* height = 0, from 2 = 1, and so on)
*/
void height(Tree_plus* A, int* h) 
{
	if (Check_for_leaf(A)) return;
	(*h)++;
	height(A->left, h);
}

/*
* Tree Printing
* I calculate the width and height of the tree, build auxiliary matrices 
* and fill them with tree values, then output each node to |*node*|
* (Due to the width alignment, the numbers may not be displayed exactly in the center)
*/
void Print_Tree(Tree_plus* A, int n) 
{
	int hight = 0;
	height(A, &hight);
	int width = (int)pow(3, hight) + 1;
	int** Matrix_data_1 = dynamic_array_alloc(hight + 1, width);
	int** Matrix_data_2 = dynamic_array_alloc(hight + 1, width);
	Take_elems(A, Matrix_data_1, Matrix_data_2, 0, width / 2, (int)pow(3, hight - 1));

	puts("Your Tree:");
	for (int i = 0; i <= hight; i++) 
	{
		for (int j = 1; j < width; j++) 
		{
			if (Matrix_data_1[i][j] == INT_NULL) printf("| NUL |");
			else if (Matrix_data_1[i][j] == INT_EMPTY) printf("       ");
			else if (Matrix_data_2[i][j] == INF) printf("| %3d |", Matrix_data_1[i][j]);
			else printf("|%2d:%2d|", Matrix_data_1[i][j], Matrix_data_2[i][j]);
		}
		puts("");
	}
	dynamic_array_free(Matrix_data_1, hight + 1);
	dynamic_array_free(Matrix_data_2, hight + 1);
}

/*
* Printing a list (in this case, printing leaves)
*/
void Print_List(List list) 
{
	Tree_plus* cur = list->head;
	if (cur == NULL) 
	{
		puts("List is empty.");
	}
	else 
	{
		printf("The list is: ");
		while (cur->right != NULL) 
		{
			printf("%d<->", cur->data_1);
			cur = cur->right;
		}
		printf("%d\n", cur->data_1);
	}
}
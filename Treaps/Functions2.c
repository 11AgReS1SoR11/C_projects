#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "Laba2.h"
#pragma warning(disable:4996)

/*
* outputs a random number from the interval a b
*/
int Random(int a, int b) 
{
	return (int)((double)rand() / RAND_MAX * (max(a, b) - min(a, b)) + min(a, b));
}

/*
* creates a treaps' node
*/
treaps* Create_node(treaps* parent, char val) 
{
	treaps* A = (treaps*)malloc(sizeof(treaps));
	if (A == NULL) 
	{
		puts("No memory abailable");
		return;
	}
	A->key = val;
	A->priority = Random(-(RAND_MAX - 2), RAND_MAX - 2);
	A->right = NULL;
	A->left = NULL;
	A->parent = parent;
	return A;
}

/*
* right turn: the right son turns counterclockwise
*/
treaps** Rotate_left(treaps* a)
{
	treaps* b = a->right;
	a->right = b->left;
	b->left = a;
	if (a->parent != NULL) 
	{
		if (a->key >= a->parent->key)
			a->parent->right = b;
		else
			a->parent->left = b;
	}
	b->parent = a->parent;
	a->parent = b;
	return &b;
}


/*
* left turn: the left son turns clockwise
*/
treaps** Rotate_right(treaps* a)
{
	treaps* b = a->left;
	a->left = b->right;
	b->right = a;
	if (a->parent != NULL) 
	{
		if (a->key >= a->parent->key)
			a->parent->right = b;
		else
			a->parent->left = b;
	}
	b->parent = a->parent;
	a->parent = b;

	return &b;
}


/*
* the function of adding a node to treaps: first we go down
* to the very bottom according to the rule of the binary search
* tree (if the key is >, then we go down to the right, otherwise to the left).
* Next, we give this node a random number (priority) and raise it
* until the priority of the parent is less
*/
void Insert_Tree(treaps** A, char val) 
{
	treaps** sheet = A;
	treaps* parent = NULL;

	// go down to the leaf
	while (*sheet != NULL) 
	{
		parent = (*sheet);
		if (val >= (*sheet)->key)
			sheet = &((*sheet)->right);
		else
			sheet = &((*sheet)->left);
	}

	(*sheet) = Create_node(parent, val);
	if (*sheet == NULL) return;

	// going up 
	while (((*sheet)->parent != NULL) && ((*sheet)->parent->priority >= (*sheet)->priority)) 
	{
		if ((*sheet)->parent->key > (*sheet)->key)
			sheet = Rotate_right((*sheet)->parent);
		else
			sheet = Rotate_left((*sheet)->parent);
	}
}

/*
* the function finds the first node with the specified key
* (if there is no such key in the tree, it returns NULL)
*/
treaps** Find_Tree(treaps** A, char val) 
{
	if ((*A) == NULL) return NULL;
	treaps** a = A;
	while (((*a) != NULL) && ((*a)->key != val)) 
	{
		if (val >= (*a)->key)
			a = &((*a)->right);
		else
			a = &((*a)->left);
	}
	if ((*a) == NULL) return NULL;
	if ((*a)->key == val) return a;
	else return NULL;
}

/*
* the function finds a node with the val value, then drops
* it to the very bottom, where it is deleted (if we want to
* delete the root, then key = 1 and a new root will be overwritten in the root)
*/
void Remove_Tree(treaps** A, char val) 
{
	// finding
	treaps** a = Find_Tree(A, val);
	if (a == NULL) 
	{
		puts("Not such value");
		return;
	}

	// root check
	int key = 0;
	if ((*A)->key == val) 
	{
		key = 1;
		if ((*A)->left == NULL && (*A)->right == NULL) 
		{
			free((*A));
			(*A) = NULL;
			return;
		}
	}

	(*a)->priority = RAND_MAX;

	// go down
	while ((*a)->left != NULL || (*a)->right != NULL) 
	{
		if ((*a)->left == NULL) 
		{
			a = Rotate_left(*a);
			a = &((*a)->left);
		}
		else 
		{
			a = Rotate_right(*a);
			a = &((*a)->right);
		}
	}

	// new root
	treaps* top = (*a);
	while (key && top->parent != NULL)
		top = top->parent;

	free((*a));   // removal
	(*a) = NULL;  // Now there is no leaf, write NULL instead
	if (key) (*A) = top; // if we del root
}


void Print_Tree(treaps* A) 
{
	if (A != NULL)
	{
		Print_Tree(A->left);
		printf("%d ", A->key);
		Print_Tree(A->right);
	}
}
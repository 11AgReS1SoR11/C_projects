#pragma once


typedef struct _treaps {
	char key;
	int priority;
	struct _treaps* left;
	struct _treaps* right;
	struct _treaps* parent;
} treaps;

void Insert_Tree(treaps** A, char val);
void Remove_Tree(treaps** A, char val);
void Print_Tree(treaps* A);
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "Laba4.h"
#define INF INT_MAX

/*
* The function creates a heap
*/
Fibanocci_Heap* Create_heap()
{
    Fibanocci_Heap* Heap = (Fibanocci_Heap*)malloc(sizeof(Fibanocci_Heap));
    if (Heap == NULL) return NULL;
    Heap->size = 0;
    Heap->min = NULL;

    return Heap;
}

/*
* The function creates a node of heap
*/
NODE* Create_node(val) 
{
    NODE* NEW = (NODE*)malloc(sizeof(NODE));
    if (NEW == NULL) return;
    NEW->key = val;
    NEW->degree = 0;
    NEW->mark = NEW->visited = false;
    NEW->parent = NEW->child = NULL;
    NEW->left = NEW->right = NEW;

    return NEW;
}

/*
* Swaps the values of two nodes
*/
void swap(NODE** a, NODE** b)
{
    NODE* c = (*a);
    (*a) = (*b);
    (*b) = c;
}

/*
* Removes the node's connection to the heap
*/
void Remove(NODE* a)
{
    a->right->left = a->left;
    a->left->right = a->right;
    if (a->parent != NULL && a->parent->child == a) 
    {
        if (a == a->right)
            a->parent->child = NULL;
        else
            a->parent->child = a->right;
    }

    a->left = a;
    a->right = a;
}

/*
* Inserts a before b
*/
void Inmove(NODE* a, NODE* b)
{
    a->right = b;
    a->left = b->left;
    b->left->right = a;
    b->left = a;
}


/*
* Function adding an element to the heap (adding occurs in constant 
* time - the element is simply inserted before H->min)
*/
void Insert(Fibanocci_Heap* H, int val) 
{
    NODE* NEW = Create_node(val);
    
    if (H->min == NULL) 
    {
        H->min = NEW;
    }
    else 
    {
        Inmove(NEW, H->min);
        if (NEW->key < H->min->key)
            H->min = NEW;
    }
    ++(H->size);
}

/*
* The function of combining two heaps - returns one heap consisting of two
*/
Fibanocci_Heap* unionHeap(Fibanocci_Heap* H1, Fibanocci_Heap* H2) {
    if (H1->min == NULL)
        return H2;
    else if (H2->min == NULL)
        return H1;

    // I also associate the minima of the heap, the left element of the first heap, 
    // with the right element of the second - as a result, I get one large looped list
    NODE* L = H1->min->left;
    NODE* R = H2->min->right;
    H2->min->right = H1->min;
    H1->min->left = H2->min;
    L->right = R;
    R->left = L;
    
    H1->size += H2->size;
    if (H2->min->key < H1->min->key)
        H1->min = H2->min;

    free(H2);
    return H1;
}

/*
* Finds Degree Heaps
*/
int Degree(Fibanocci_Heap* H) {
    int count = 0, n = H->size;
    while (n) 
    {
        n /= 2;
        count++;
    }
    return count;
}

/*
* Moving a under b (a > b) otherwise vice versa
*/
void Replace(NODE* a, NODE* b) {
    if (a->key < b->key) 
        swap(&a, &b);

    Remove(a);
    // establishing a relationship with b
    a->parent = b;

    // establishing a relationship with b->child
    if (b->child == NULL)
    {
        b->child = a;
    }
    else
    {
        Inmove(a, b->child);
        if (a->key < b->child)
            b->child = a;
    }

    (b->degree)++;
}


/*
* The function of combining all vertices with the same degree
*/
void consolidate(Fibanocci_Heap* H) {
    int degree = Degree(H);
    // auxiliary array
    NODE** arr = (NODE**)malloc(sizeof(NODE*) * (degree+1));
    if (arr == NULL) return;
    for (int i = 0; i <= degree; i++)
        arr[i] = NULL;

    // pass through all vershniki
    // If same degree -> connect
    NODE* cur = H->min;
    do {
        int d = cur->degree;
        while (arr[d] != NULL) 
        {
            Replace(arr[d], cur);
            if (arr[d]->key < cur->key)
            {
                cur = arr[d];
            }
            arr[d++] = NULL;
        }
        arr[d] = cur;
        cur = cur->right;
    } while (cur != H->min);


    // Connect all the elements from the auxiliary array into one heap
    H->min = NULL;
    for (int i = 0; i < degree; i++) 
    {
        if (arr[i] != NULL) 
        {
            if (H->min == NULL) 
            {
                arr[i]->left = arr[i];
                arr[i]->right = arr[i];
                H->min = arr[i];
            }
            else 
            {
                Inmove(arr[i], H->min);
                if (arr[i]->key < H->min->key) 
                    H->min = arr[i];
            }
        }
    }
    free(arr);
}

/*
* The function removes the minimum element and returns its key
*/
int extract_min(Fibanocci_Heap* H) 
{
    if (H->min == NULL)
    {
        puts("Куча пуста");
        return INF;
    }
    else if (H->min == H->min->right && H->min->child == NULL) // checking for one element
    {
        int tmp = H->min->key;
        free(H->min);
        H->min = NULL;
        return tmp;
    }
    else 
    {
        NODE* Del_node = H->min,* Del_node_child_right = Del_node,* Del_node_child = Del_node->child;
        if (Del_node_child != NULL)
        {
            // pulling children out of the minimum element and establishing their connection with the rest
            do {
                Del_node_child_right = Del_node_child->right;
                Inmove(Del_node_child, H->min);
                Del_node_child->parent = NULL;
                Del_node_child = Del_node_child_right;
            } while (Del_node_child_right != Del_node->child);
        }

        // moving the pointer from the element being deleted
        H->min = Del_node->right; 
        // removing an element from the heap
        Remove(Del_node);
        
        // Grouping the subtrees
        consolidate(H);
        --(H->size);
        int tmp = Del_node->key;
        free(Del_node);
        return tmp;
    }
}

/*
* Cuts an element from the heap and returns it to the first level next to H->min
*/
void cut(Fibanocci_Heap* H, NODE* Del_node) 
{
    Remove(Del_node);
    --(Del_node->parent->degree);
    Del_node->mark = false;

    Inmove(Del_node, H->min);
}

/*
* Cuts out the parents of the deleted element, if necessary (mark == true)
*/
void cascading_cut(Fibanocci_Heap* H, NODE* Parents_Del_node)
{
    while (Parents_Del_node->mark)
    {
        cut(H, Parents_Del_node);
        if (Parents_Del_node->parent == NULL) break;
        Parents_Del_node = Parents_Del_node->parent;
    }
    // This element is marked as an element with a deleted child
    Parents_Del_node->mark == true;
}

/*
* Reduces the key of the transferred node and balances the heap
*/
void decrease_key(Fibanocci_Heap* H, NODE* Dec_node, int new_key)
{
    Dec_node->key = new_key;
    if ((Dec_node->parent != NULL) && (Dec_node->key < Dec_node->parent->key))
    {
        cut(H, Dec_node);
        cascading_cut(H, Dec_node->parent);
    }

    if (Dec_node->key < H->min->key)
        H->min = Dec_node;
}


/*
* Passes through all the elements and if there is a match, then raises it up
*/
void* Find(Fibanocci_Heap* H, NODE* Finding, int key)
{
    Finding->visited = true;
    if (Finding->key == key) 
    {
        decrease_key(H, Finding, -INF);
        Finding->visited = false;
    }
    if (Finding->child != NULL) 
        Find(H, Finding->child, key);

    if ((Finding->right->visited != true)) 
        Find(H, Finding->right, key);

    Finding->visited = false;
}

/*
* Deletes an element with the value dec_key
*/
void Delete_Node(Fibanocci_Heap* H, int key) 
{
    if (H == NULL || H->min == NULL)
    {
        puts("Куча пуста");
        return;
    }
    // Raising the element we want to delete
    Find(H, H->min, key);
    // Delete
    if (H->min->key != -INF)
        puts("Такого значения нет");
    else
        extract_min(H);
}

/*
* Heap output (recursively)
*/
void print_heap(NODE* head) 
{
    for (NODE* cur = head;; cur = cur->right)
    {
        if (cur->child == NULL) 
        {
            printf("Узел без ребёнка (%d) \n", cur->key);
        }
        else 
        {
            printf("Узел(%d) с ребёнком (%d)\n", cur->key, cur->child->key);
            print_heap(cur->child);
        }
        if (cur->right == head) {
            break;
        }
    }
}
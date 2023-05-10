#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "Laba4.h"
#pragma warning(disable:4996)

int main() {
    setlocale(LC_ALL, "Rus");
    int val, a;
    Fibanocci_Heap* MyHeap = NULL;

    printf("�������:\n1 - �������� �������\n2 - ������� min\n3 - ����������\n4 - �������\n5 - ������� ������\n6 - ��������� ������\n");
    scanf("%d", &a);
    while (a != 6)
    {
        if (a == 1)
        {
            printf("������� ��������: ");
            scanf("%d", &val);
            if (MyHeap == NULL) 
            {
                MyHeap = Create_heap();
            }
            Insert(MyHeap, val);
        }
        else if (a == 2)
        {
            if (MyHeap == NULL || MyHeap->min == NULL)
            {
                puts("���� �����");
            }
            else
            {
                int extracted_min = extract_min(MyHeap);
                printf("Min = %d\n", extracted_min);
            }
        }
        else if (a == 3) 
        {
            Fibanocci_Heap* Uni = Create_heap();
            printf("������� ���-�� ��������� ������ ����: ");
            int size;
            scanf("%d", &size);
            printf("������� ����� ������ ��������: ");
            for (int i = 0; i < size; i++)
            {
                scanf("%d", &val);
                Insert(Uni, val);
            }
            MyHeap = unionHeap(MyHeap, Uni);
        }
        else if (a == 4)
        {
            printf("������� ��������: ");
            scanf("%d", &val);
            Delete_Node(MyHeap, val);
        }
        else if (a == 5) 
        {
            if (MyHeap == NULL || MyHeap->min == NULL)
            {
                puts("���� �����");
            }
            else 
            {
                print_heap(MyHeap->min);
            }
        }
        else
        {
            puts("�������� ��������");
        }
        printf("�������:\n1 - �������� �������\n2 - ������� min\n3 - ����������\n4 - �������\n5 - ������� ������\n6 - ��������� ������\n");
        scanf("%d", &a);
    }
    return 0;
}
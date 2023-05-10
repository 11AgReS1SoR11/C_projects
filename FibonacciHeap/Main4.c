#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "Laba4.h"
#pragma warning(disable:4996)

int main() {
    setlocale(LC_ALL, "Rus");
    int val, a;
    Fibanocci_Heap* MyHeap = NULL;

    printf("Введите:\n1 - Добавить элемент\n2 - Забрать min\n3 - Объединить\n4 - Удалить\n5 - Вывести дерево\n6 - Закончить работу\n");
    scanf("%d", &a);
    while (a != 6)
    {
        if (a == 1)
        {
            printf("Введите значение: ");
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
                puts("Куча пуста");
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
            printf("Введите кол-во элементов второй кучи: ");
            int size;
            scanf("%d", &size);
            printf("Введите через пробел значений: ");
            for (int i = 0; i < size; i++)
            {
                scanf("%d", &val);
                Insert(Uni, val);
            }
            MyHeap = unionHeap(MyHeap, Uni);
        }
        else if (a == 4)
        {
            printf("Введите значение: ");
            scanf("%d", &val);
            Delete_Node(MyHeap, val);
        }
        else if (a == 5) 
        {
            if (MyHeap == NULL || MyHeap->min == NULL)
            {
                puts("Куча пуста");
            }
            else 
            {
                print_heap(MyHeap->min);
            }
        }
        else
        {
            puts("Неверное значение");
        }
        printf("Введите:\n1 - Добавить элемент\n2 - Забрать min\n3 - Объединить\n4 - Удалить\n5 - Вывести дерево\n6 - Закончить работу\n");
        scanf("%d", &a);
    }
    return 0;
}
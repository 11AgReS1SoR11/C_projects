#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "Laba2.h"
#pragma warning(disable:4996)

int main() {
    setlocale(LC_ALL, "Rus");
	int val, a;
	treaps* MyTree = NULL;

	printf("Введите:\n1 - Добавить элемент\n2 - Удалить элемент\n3 - Вывести дерево\n4 - Закончить работу\n");
	scanf("%d", &a);
	while (a != 4) 
	{
		if (a == 1) 
		{
			printf("Введите значение: ");
			scanf("%d", &val);
			Insert_Tree(&MyTree, val);
		}
		else if (a == 2) 
		{
			printf("Введите значение: ");
			scanf("%d", &val);
			Remove_Tree(&MyTree, val);
		}
		else if (a == 3) 
		{
			if (MyTree == NULL)
			{
				puts("Дерево пусто");
			}
			else 
			{
				printf("Значения в дереве: ");
				Print_Tree(MyTree);
				puts("");
			}
		}
		else 
		{
			puts("Неверное значение");
		}
		printf("Введите:\n1 - Добавить элемент\n2 - Удалить элемент\n3 - Вывести дерево\n4 - Закончить работу\n");
		scanf("%d", &a);
	}
	return 0;
}
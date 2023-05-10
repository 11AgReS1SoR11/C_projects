#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "Laba3.h"
#pragma warning(disable:4996)

int main() {
	setlocale(LC_ALL, "Rus");
	int val, a;
	Tree_plus* MyTree = NULL;
	List List_of_tree = Create_List();

	printf("Введите:\n1 - Добавить элемент\n2 - Вывести дерево\n3 - Закончить работу\n");
	scanf("%d", &a);
	while (a != 3) 
	{
		if (a == 1) 
		{
			printf("Введите значение: ");
			scanf("%d", &val);
			Insert_Tree(&MyTree, val, List_of_tree);
		}
		else if (a == 2) 
		{
			if (MyTree == NULL) 
			{
				puts("Дерево пусто");
			}
			else 
			{
				Print_Tree(MyTree, List_of_tree->size);
				Print_List(List_of_tree);
			}
		}
		else 
		{
			puts("Неверное значение");
		}
		printf("Введите:\n1 - Добавить элемент\n2 - Вывести дерево\n3 - Закончить работу\n");
		scanf("%d", &a);
	}
	return 0;
}
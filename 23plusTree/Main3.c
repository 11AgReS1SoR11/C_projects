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

	printf("�������:\n1 - �������� �������\n2 - ������� ������\n3 - ��������� ������\n");
	scanf("%d", &a);
	while (a != 3) 
	{
		if (a == 1) 
		{
			printf("������� ��������: ");
			scanf("%d", &val);
			Insert_Tree(&MyTree, val, List_of_tree);
		}
		else if (a == 2) 
		{
			if (MyTree == NULL) 
			{
				puts("������ �����");
			}
			else 
			{
				Print_Tree(MyTree, List_of_tree->size);
				Print_List(List_of_tree);
			}
		}
		else 
		{
			puts("�������� ��������");
		}
		printf("�������:\n1 - �������� �������\n2 - ������� ������\n3 - ��������� ������\n");
		scanf("%d", &a);
	}
	return 0;
}
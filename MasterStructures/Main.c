#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include "Basics.h"


int main()
{
	FILE* f = fopen("Data.txt", "r");
	if (!f) return -1;
	Info* curr;

	SLNode* head = NULL;

	while (!feof(f))
	{
		curr = readOneInfo(f);
		head = SLInsertStart(head, curr);
	}

	printSListForwards(head);
	//deleteSL(&head);      <- does work but commenting it out to keep the structure
}
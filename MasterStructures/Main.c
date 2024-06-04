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

	SLNode* headSL = NULL;

	DList dlist = { .head = NULL, .tail = NULL };

	while (!feof(f))
	{
		curr = readOneInfo(f);

		headSL = SLInsertStart(headSL, curr);
		dlist.head = DLInsertStart(dlist.head, curr);
		if (dlist.head->next == NULL) 
			dlist.tail = dlist.head; //shouldn't i allocate memory for tail here? i mean it works but...

	}
	
	//printSList(headSL);
	printDListForwards(dlist.head);
	printf("\n\n");
	printDListBackwards(dlist.tail);


	//deleteSL(&headSL); 
	//deleteDL(&dlist.head);
}
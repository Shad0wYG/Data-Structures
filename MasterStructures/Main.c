#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include "Basics.h"
#include "Hashes.h"


int main()
{
	FILE* f = fopen("Data.txt", "r");
	if (!f) return -1;
	Info* curr;

	SLNode* headSL = NULL;
	DList dlist = { .head = NULL, .tail = NULL };
	HT hashT = initTable(26);

	while (!feof(f))
	{
		curr = readOneInfo(f);

		headSL = SLInsertStart(headSL, curr);
		dlist.head = DLInsertStart(dlist.head, curr);
		if (dlist.head->next == NULL) 
			dlist.tail = dlist.head; //shouldn't i allocate memory here? i mean it works but...
		
		addToHT(hashT, curr);
	}
	
	//printSList(headSL);
	//printDListForwards(dlist.head);
	//printf("\n\n");
	//printDListBackwards(dlist.tail);
	printHT(hashT);

	Info* testSeek = seekByKey(hashT, "Pink"); //this is deep-copied, so make sure to free()
	printf("\nThe Seeked element is:\n");
	printInfo(testSeek);
	free(testSeek->name);
	free(testSeek);


	deleteSL(&headSL); 
	deleteDL(&dlist.head);
	deleteHT(&hashT);
}
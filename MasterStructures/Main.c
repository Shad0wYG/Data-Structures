#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include "Basics.h"
#include "Hashes.h"
#include "BST.h"

int main()
{
	FILE* f = fopen("Data.txt", "r");
	if (!f) return -1;
	Info* curr;

	SLNode* headSL = NULL;
	DList dlist = { .head = NULL, .tail = NULL };
	HT hashT = initTable(26);
	BSTNode* root = NULL;

	while (!feof(f))
	{
		curr = readOneInfo(f);

		headSL = SLInsertStart(headSL, curr);
		dlist.head = DLInsertStart(dlist.head, curr);
		if (dlist.head->next == NULL) 
			dlist.tail = dlist.head; //shouldn't i allocate memory here? i mean it works but...
		
		addToHT(hashT, curr);
		addBSTNode(&root, curr);
	}
	
	//printSList(headSL);
	//printDListForwards(dlist.head);
	//printf("\n\n");
	//printDListBackwards(dlist.tail);
	//printHT(hashT);

	printInOrder(root);
	//printPreOrder(root);
	//printPostOrder(root);



	/// This below is for Hash Table 
	//Info* testSeek = seekByKey(hashT, "Pink"); //this is deep-copied, so make sure to free()
	//printf("\nThe Seeked element is:\n");
	//printInfo(testSeek);
	//free(testSeek->name);
	//free(testSeek);


	/*Info* testSeek = seekInBST(root, "Dread");
	if (testSeek)
	{
		printf("\nThe Seeked element is:\n");
		printInfo(testSeek);
		free(testSeek->name);
		free(testSeek);
	}
	else printf("no such elem");
*/

	deleteSL(&headSL); 
	deleteDL(&dlist.head);
	deleteHT(&hashT);
}
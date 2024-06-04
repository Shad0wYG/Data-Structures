#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include "Basics.h"

///will use the SList stuff from Basics.h for the lists themselves
typedef struct ChainHashTable
{
	int size;
	SLNode** arr;
}HT;

HT initTable(int size)
{
	HT tmp;
	tmp.size = size;
	tmp.arr = (SLNode**)malloc(sizeof(SLNode*) * size);

	for (int i = 0; i < size; i++) {
		tmp.arr[i] = NULL;
	}

	return tmp;
}
//this is kind of up in the air, you can use almost whatever as long as it can return a 
// number in [0, maxHT] and the distribution is fairly even
int hashFunc(char* key, int size)
{
	return key[0] % size; //basic asf
}

SLNode* insertAtEnd(SLNode* head, Info* info)
{
	if (!head) 
		return createNode(info);

	while (head->next) {
		head = head->next;
	}

	SLNode* tmp = createNode(info);
	head->next = tmp;
	return head;
}


void addToHT(HT ht, Info* inf)
{
	if (ht.size > 0)
	{
		int index = hashFunc(inf->name, ht.size);
		if (index >= 0 && index < ht.size)
		{
			ht.arr[index] = insertAtEnd(ht.arr[index], inf);
		}
	}
}

void printHT(HT ht)
{
	for (int i = 0; i < ht.size; i++)
	{
		printf("\nPosition %d:\n", i);
		printSList(ht.arr[i]);
	}
}

Info* seekByKey(HT ht, char* key)
{
	int index = hashFunc(key, ht.size);
	while (strcmp(ht.arr[index]->info->name, key) != 0 && ht.arr[index] != NULL)
	{
		ht.arr[index] = ht.arr[index]->next;
	}

	if (strcmp(ht.arr[index]->info->name, key) == 0) return deepCopyInfo(ht.arr[index]->info);
	else return NULL;
}

void deleteHT(HT* ht) 
{
	//if (!ht) return;   <- nah, vreau sa crape sa stiu ca nu fac bine
	for (int i = 0; i < ht->size; i++)
	{
		while (ht->arr[i])
		{
			SLNode* del = ht->arr[i];
			ht->arr[i] = ht->arr[i]->next;
			free(del->info->name);
			free(del->info);
			free(del);
			del = NULL;
		}
	}
}
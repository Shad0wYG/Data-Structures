#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include "Basics.h"


#pragma region Basic Definitions and File Reading

//info field
typedef struct Info {
	int id;
	char* name;
	double nonInt;
	char letter;
};
typedef struct Info Info;

Info* createInfo()
{
	Info* tmp = (Info*)malloc(sizeof(Info));
	//tmp->name = (char*)malloc(sizeof(char) * 256); //maybe realloc later
}

void printInfo(Info* info)
{
	printf("Int: %d, String: %s, Double: %5.2lf, Letter: %c\n", info->id, info->name, info->nonInt, info->letter);
}

//SL
typedef struct SLNode {
	Info* info;
	struct SLNode* next;
};
typedef struct SLNode SLNode;


//DL
typedef struct DLNode {
	struct DLNode* prev;
	Info* info;
	struct DLNode* next;
}DLNode;

typedef struct DList {
	DLNode* head;
	DLNode* tail;
}DList;


//files
Info* readOneInfo(FILE* f)
{
	Info* tmp = createInfo();
	char buffer[256];
	char* token;
	fgets(buffer, 256, f);

	token = strtok(buffer, " ,\n");
	tmp->id = atoi(token);

	token = strtok(NULL, " ,\n");
	tmp->name = (char*)malloc(sizeof(char) * strlen(token));
	strcpy(tmp->name, token);

	token = strtok(NULL, " ,\n");
	tmp->nonInt = atof(token);

	token = strtok(NULL, " ,\n");
	tmp->letter = token[0];

	return tmp;
}
#pragma endregion


#pragma region Utilities - SL

SLNode* createEmptyNode()
{
	SLNode* tmp = (SLNode*)malloc(sizeof(SLNode));
	tmp->info = tmp->next = NULL;
}

SLNode* createNode(Info* info)
{
	SLNode* tmp = (SLNode*)malloc(sizeof(SLNode));
	tmp->info = info;
	tmp->next = NULL;
}

SLNode* SLInsertStart(SLNode* head, Info* info)
{
	SLNode* tmp = createNode(info);
	tmp->next = head;
	return tmp;
}


void printSListForwards(SLNode* head)
{
	while (head)
	{
		printInfo(head->info);
		head = head->next;
	}
}

void deleteNode(SLNode** node)
{
	free((*node)->info->name);
	free((*node)->info);
	free(*node);
	(*node) = NULL;
}

void deleteSL(SLNode** head)
{
	while (*head)
	{
		SLNode* tmp = (*head);
		(*head) = tmp->next;
		//deleteNode(tmp);
		free(tmp->info->name);
		free(tmp->info);
		free(tmp);
		//tmp = NULL;
	}
}

#pragma endregion


#pragma region Utilities - DL

#pragma endregion

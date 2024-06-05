#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>


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
	return tmp;
}

void printInfo(Info* info)
{
	printf("Int: %d, String: %s, Double: %5.2lf, Letter: %c\n", info->id, info->name, info->nonInt, info->letter);
}

Info* deepCopyInfo(Info* inf)
{
	Info* tmp = createInfo();
	tmp->id = inf->id;
	tmp->name = (char*)malloc( sizeof(char) * (strlen(inf->name) + 1) );
	strcpy(tmp->name, inf->name);
	tmp->nonInt = inf->nonInt;
	tmp->letter = inf->letter;
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
	tmp->name = (char*)malloc(sizeof(char) * strlen(token) + 1);
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
	tmp->info = NULL;
	tmp->next = NULL;
	return tmp;
}

SLNode* createNode(Info* info)
{
	SLNode* tmp = (SLNode*)malloc(sizeof(SLNode));
	tmp->info = deepCopyInfo(info);
	tmp->next = NULL;
	return tmp;
}

SLNode* SLInsertStart(SLNode* head, Info* info)
{
	SLNode* tmp = createNode(info);
	tmp->next = head;
	return tmp;
}


void printSList(SLNode* head)
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
		deleteNode(&tmp);
		//tmp = NULL; <- i was told this would break it if it isnt here but it seems to work without
	}
}

#pragma endregion


#pragma region Utilities - DL

DLNode* createDLNode(Info* info)
{
	DLNode* tmp = (DLNode*)malloc(sizeof(DLNode));
	tmp->info = (Info*)malloc(sizeof(Info)); //rev
	tmp->info = deepCopyInfo(info);
	tmp->next = NULL;
	tmp->prev = NULL;
	return tmp;
}

//extra: do it as a void function with DLNode** head
DLNode* DLInsertStart(DLNode* head, Info* inf)
{
	DLNode* tmp = createDLNode(inf);
	tmp->next = head;
	if (head)
	{
		head->prev = tmp;
	}
	return tmp;
}

void printDListForwards(DLNode* head)
{
	while (head)
	{
		printInfo(head->info);
		head = head->next;
	}
}

void printDListBackwards(DLNode* tail) 
{
	while (tail)
	{
		printInfo(tail->info);
		tail = tail->prev;
	}
}


void deleteDLNode(DLNode** node)
{
	free((*node)->info->name);
	free((*node)->info);
	free(*node);
	(*node) = NULL;
}

void deleteDL(DLNode** head)
{
	while (*head)
	{
		DLNode* tmp = (*head);
		(*head) = (*head)->next;
		deleteDLNode(&tmp);
	}
}

#pragma endregion
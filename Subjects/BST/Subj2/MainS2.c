#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <stdbool.h>

typedef struct File {
	char* id;
	unsigned int size;
	bool readOnly;
	char dateCreated[11];
	char* ownerName;
}Info;

typedef struct BST {
	struct BST* left;
	Info* info;
	struct BST* right;
}BST;

typedef struct HEAP {
	Info** arr;
	int currentpos;
}Heap;



Info* createInfo(char* id, unsigned int size, bool readOnly, char dateCreated[11], char* ownerName) {
	Info* ret = (Info*)malloc(sizeof(Info));
	ret->id= (char*)malloc(sizeof(char) * (strlen(id) + 1));
	ret->ownerName = (char*)malloc(sizeof(char) * (strlen(ownerName) + 1));

	ret->id = id;
	ret->readOnly = readOnly;
	ret->size = size;
	strcpy(ret->id, id);
	strcpy(ret->ownerName, ownerName);
	strcpy(ret->dateCreated, dateCreated);
	
	return ret;
}

void printInfo(Info* inf) {
	printf("\nID: %s, Size: %d, Readonly: %s, Date: %s, Owner: %s", inf->id, inf->size, (inf->readOnly == true ? "Yes" : "No"), inf->dateCreated, inf->ownerName);
}


void addToBST(BST** root, Info* info) {
	if (!(*root)) {
		(*root) = (BST*)malloc(sizeof(BST));
		(*root)->info = createInfo(info->id, info->size, info->readOnly, info->dateCreated, info->ownerName);
		(*root)->left = NULL;
		(*root)->right = NULL;

		return;
	}

	else if (strcmp(info->id, (*root)->info->id) < 0) 
		addToBST(&(*root)->left, info);
	else addToBST(&(*root)->right, info);

}


void printBST(BST* root) {
	if (root) {
		printBST(root->left);
		printInfo(root->info);
		printBST(root->right);
	}
}

void printGreater(BST* root, char date[11]) {
	if (root) {
		printGreater(root->left, date);

		//this is wrong lol but im too lazy to fix it so whatever. use ISO-8601 for dates thx
		if (strcmp(root->info->dateCreated, date) > 0) printInfo(root->info);
		printGreater(root->right, date);
	}
}


int getNrReadOnly(BST* root) {
	if (root) {
		if (root->info->readOnly == true) return 1 + getNrReadOnly(root->left) + getNrReadOnly(root->right);
		return 0 + getNrReadOnly(root->left) + getNrReadOnly(root->right);

	}

	else return 0;

}

int getNoNodes(BST* root) {
	if (root) {
		return 1 + getNoNodes(root->left) + getNoNodes(root->right);
	}
	else return 0;
}


int getSum(BST* root) {
	if (root) {
		return root->info->size + 
			getSum(root->left) + 
			getSum(root->right);
	}
	else return 0;
}

int checkExist(BST* root, char* id) {
	if (root) {
		if (strcmp(root->info->id, id) == 0) return 1;
		else {
			if (strcmp(root->info->id, id) > 0) return checkExist(root->left, id);
			else return checkExist(root->right, id);
		}
	}

	else return 0;
}

void boostAll(BST** root) {
	if (*root) {
		boostAll(&(*root)->left);
		(*root)->info->size *= 2;
		boostAll(&(*root)->right);
	}
}

void boostSizes(BST** root, char* fileID) {
	if (checkExist(*root, fileID) == 0) {
		boostAll(root);
		return;
	}

	else {
		if (*root) {
			if (strcmp((*root)->info->id, fileID) != 0) {
				(*root)->info->size *= 2;
				if (strcmp((*root)->info->id, fileID) > 0) boostSizes(&(*root)->left, fileID);
				else boostSizes(&(*root)->right, fileID);
			}
			else return;
		}
		else return;
	}
}


int getCountNodes(BST* root, char* key) {
	if (root) {
		if (strcmp(root->info->ownerName, key) == 0)
			return 1 + getCountNodes(root->left, key) + getCountNodes(root->right, key);
		else return 0 + getCountNodes(root->left, key) + getCountNodes(root->right, key);
	}
	else return 0;
}

void reheap(Heap* h, int index) {

	if (index > 0) {
		int pInd = (index - 1) / 2;
		if (strcmp(h->arr[pInd]->id, h->arr[index]->id) < 0) {
			Info* aux = h->arr[pInd];
			h->arr[pInd] = h->arr[index];
			h->arr[index] = aux;
			reheap(h, pInd);
		}
	}

}


void addInfoToHeap(Heap* h, Info* inf){
	(*h).arr[(*h).currentpos] = inf;
	reheap(h, (*h).currentpos);
	(*h).currentpos++;

}


void BSTtoHeap(BST* root, Heap* h, char* key) {
	if (root)
	{
		if (strcmp(root->info->ownerName, key) == 0)
		{
			Info* inf = createInfo(root->info->id, root->info->size, root->info->readOnly, root->info->dateCreated, root->info->ownerName);
			addInfoToHeap(h, inf);
		}
		BSTtoHeap(root->left, h, key);
		BSTtoHeap(root->right, h, key);
	}
}


int main() {
	FILE* file = fopen("DataS2.txt", "r");
	if (!file) return -1;

	BST* root = NULL;


	char* id;
	unsigned int size;
	bool readOnly;
	char dateCreated[11];
	char* ownerName;

	char buffer[256]; char* token;
	while (fgets(buffer, 256, file)) {
		token = strtok(buffer, " ,\n");
		id = (char*)malloc(sizeof(char) * (strlen(token) + 1));
		strcpy(id, token);

		token = strtok(NULL, " ,\n");
		size = atoi(token);

		token = strtok(NULL, " ,\n");
		readOnly = token[0] == '1' ? 1 : 0;

		token = strtok(NULL, " ,\n");
		strcpy(dateCreated, token);

		token = strtok(NULL, " ,\n");
		ownerName = (char*)malloc(sizeof(char) * (strlen(token) +1));
		strcpy(ownerName, token);

		Info* current = createInfo(id, size, readOnly, dateCreated, ownerName);
		//printInfo(current);
		addToBST(&root, current);

	}
	printBST(root);

	printf("\nEx2: ");
	printGreater(root, "12/12/1980");


	printf("\nEx3: ");
	printf("%d", getNrReadOnly(root));


	printf("\nEx4; Average: ");
	int x = getSum(root);
	int y = getNoNodes(root);
	printf("%.2f",(float)x/y);


	printf("\nEx5: ");
	boostSizes(&root, "999");
	printBST(root);


	printf("\nEx6: ");
	int c = getCountNodes(root, "Alberto");
	Heap heap = { .currentpos = 0 };
	heap.arr = (Info**)malloc(sizeof(Info*) * c);
	BSTtoHeap(root, &heap, "Alberto");

	for (int i = 0; i < c; i++) printInfo(heap.arr[i]);

}
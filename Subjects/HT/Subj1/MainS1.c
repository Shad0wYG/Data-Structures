#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#define HTSIZE 26;

typedef struct Task {
	unsigned int id;
	char* date;
	char* ownerName;
	float percentDone;
}Info;

typedef struct SLList {
	Info* info;
	struct SLList* next;
}Node;

typedef struct HT {
	Node** arr;
	int size;
}HT;

HT initHash(int size) {
	HT ret;
	ret.size = size;
	ret.arr = (Node**)malloc(sizeof(Node*) * size);

	for (int i = 0; i < size; i++) {
		ret.arr[i] = NULL;
	}
	return ret;
}

Info* createInfo(unsigned int id, char* date, char* name, float perc) {
	Info* ret = (Info*)malloc(sizeof(Info));
	ret->date = (char*)malloc(sizeof(char) * (strlen(date) + 1));
	ret->ownerName = (char*)malloc(sizeof(char) * (strlen(name) + 1));
	strcpy(ret->date, date);
	strcpy(ret->ownerName, name);
	ret->id = id;
	ret->percentDone = perc;
	return ret;
}

void printInfo(Info* inf) {
	printf("\nID: %d, Date: %s, Name: %s, Percent done: %.2f", inf->id, inf->date, inf->ownerName, inf->percentDone);
}



Node* createNode(Info* inf) {
	Node* ret = (Node*)malloc(sizeof(Node));
	ret->info = (Info*)malloc(sizeof(Info));
	ret->info = inf;
	ret->next = NULL;
	return ret;
}

int hashFunc(char* key, int size) {
	return (key[0] % size);
}

void addToHash(HT* ht, Node* current) {
	if (current == NULL) return;

	int pos = hashFunc(current->info->ownerName, ht->size);
	if (ht->arr[pos] == NULL) ht->arr[pos] = current;
	else {
		Node* tmp = ht->arr[pos];
		while (tmp->next) {
			tmp = tmp->next;
		}
		tmp->next = current;
	}
}

void printHash(HT ht) {
	for (int i = 0; i < ht.size; i++) {
		if (ht.arr[i]) printf("\nPos: %d. Values: ", i);
		Node* tmp = ht.arr[i];
		while (tmp) {
			printInfo(tmp->info);
			tmp = tmp->next;
		}
	}
}

int getTasks(HT ht, char* key) {
	int count = 0;
	int pos = hashFunc(key, ht.size);
	Node* tmp = ht.arr[pos];
	while (tmp) {
		count++;
		tmp = tmp->next;
	}
	return count;
}

int tasksAboveCompletion(HT ht, float target) {
	int ret = 0;
	for (int i = 0; i < ht.size; i++) {
		if (ht.arr[i]) {
			Node* tmp = ht.arr[i];
			while (tmp) {
				if (tmp->info->percentDone > target) ret++;
				tmp = tmp->next;
			}
		}
	}

	return ret;
}


void changeOwner(HT* ht, unsigned int id, char* newName) {
	Node* temporaryNode = NULL;

	for (int i = 0; i < (*ht).size; i++) {
		if ((*ht).arr[i]) {
			Node* tmp = (*ht).arr[i];

			if (tmp->info->id == id) {

				temporaryNode = createNode(tmp->info);
				free(temporaryNode->info->ownerName);
				temporaryNode->info->ownerName = (char*)malloc(sizeof(char) * (strlen(newName) + 1));
				strcpy(temporaryNode->info->ownerName, newName);

				if (tmp->next) (*ht).arr[i] = tmp->next;
				else ht->arr[i] = NULL;
			}

			while (tmp->next) {
				if (tmp->next->info->id == id) {

					temporaryNode = createNode(tmp->next->info);
					free(temporaryNode->info->ownerName);
					temporaryNode->info->ownerName = (char*)malloc(sizeof(char) * (strlen(newName) + 1));
					strcpy(temporaryNode->info->ownerName, newName);

					break;
				}
				tmp = tmp->next;
			}
		}
	}

	addToHash(ht, temporaryNode);


}

void printlist(Node* head) {
	Node* tmp = head;
	while (tmp) {
		printInfo(tmp->info);
		tmp = tmp->next;
	}
}


void insertAtStart(Node** head, Node* curr) {
	Node* tmp = createNode(curr->info);
	if ((*head) == NULL) {
		(*head) = tmp;
		return;
	}

	Node* other = (*head);
	tmp->next = other;
	(*head) = tmp;
	return;

}

Node* createList(HT ht, char* date) {
	Node* head = NULL;

	for (int i = 0; i < ht.size; i++) {
		if (ht.arr[i]) {
			Node* tmp = ht.arr[i];
			while (tmp) {
				if (strcmp(tmp->info->date, date) == 0) insertAtStart(&head, tmp);
				tmp = tmp->next;
			}
		}
	}

	return head;
}


int main() {
	FILE* f = fopen("DataS1.txt", "r");
	if (!f) return -1;
	HT ht; Node* current = NULL; Node* headList = NULL;
	ht = initHash(26);
	unsigned int id = 0; char* date = NULL; char* ownername = NULL; float perc = 0;

	char buffer[256]; char* token;
	while (fgets(buffer, 256, f)) {
		token = strtok(buffer, ", \n");
		id = atoi(token);

		token = strtok(NULL, ", \n"); 
		date = (char*)malloc(sizeof(char) * (strlen(token) + 1));
		strcpy(date, token);

		token = strtok(NULL, ", \n");
		ownername = (char*)malloc(sizeof(char) * (strlen(token) + 1));
		strcpy(ownername, token);

		token = strtok(NULL, ", \n");
		perc = atof(token);

		Info* inf = createInfo(id, date, ownername, perc);
		current = createNode(inf);
		addToHash(&ht, current);
		//printInfo(inf);
	}

	printHash(ht);

	printf("\nEx3: ");
	int c = getTasks(ht, "Ala");
	printf("%d", c);


	printf("\nEx4: ");
	int c4 = tasksAboveCompletion(ht, 0.5);
	printf("%d", c4);


	printf("\nEx5: ");
	changeOwner(&ht, 1, "Alberto");
	printHash(ht);


	printf("\nEx6: ");
	headList = createList(ht, "01/01/1970");
	printlist(headList);


}
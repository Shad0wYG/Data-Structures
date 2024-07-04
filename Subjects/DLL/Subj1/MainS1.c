#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

typedef struct Fund {
	char* code;
	char group[2];
	int riskLvl;
	double NAV;
	float percentReturn;
}Fund;

typedef struct DLL {
	struct DLL* prev;
	Fund* info;
	struct DLL* next;
}Node;

typedef struct DoubleList {
	Node* head;
	Node* tail;
}DoubleList;


Fund* createInfo(char* code, char group[2], int rl, double nav, float perc) {
	Fund* ret = (Fund*)malloc(sizeof(Fund));
	ret->code = (char*)malloc(sizeof(char) * (strlen(code) + 1));
	strcpy(ret->code, code);
	strcpy(ret->group, group);
	ret->riskLvl = rl;
	ret->NAV = nav;
	ret->percentReturn = perc;
	return ret;
}


void printData(Fund* inf) {
	printf("Code: %s, Group: %s, Risk: %d, NAV: %.2lf, Percentage return: %.2f\n", inf->code, inf->group, inf->riskLvl, inf->NAV, inf->percentReturn);
}

Node* createNode(Fund* info) {
	Node* tmp = (Node*)malloc(sizeof(Node));
	tmp->info = (Fund*)malloc(sizeof(Fund));
	tmp->info->code = (char*)malloc(sizeof(info->code) + 1);
	tmp->info = createInfo(info->code, info->group, info->riskLvl, info->NAV, info->percentReturn);
	tmp->next = NULL;
	tmp->prev = NULL;
	return tmp;
}

Node* addNode(Node* head, Fund* info) {
	Node* tmp = createNode(info);
	if (head == NULL) return tmp;
	tmp->next = head;
	head->prev = tmp;
	return tmp;
}

void printHeadList(Node* head) {
	while (head) {
		printData(head->info);
		head = head->next;
	}
}

void printBackList(Node* tail) {
	while (tail) {
		printData(tail->info);
		tail = tail->prev;
	}
}

int getNrRisky(Node* head, int risk) {
	int c = 0;
	while (head) {
		if (head->info->riskLvl > risk) c++;
		head = head->next;
	}
	return c;
}


int main() {
	DoubleList dl = { NULL, NULL };
	FILE* f = fopen("DataS1.txt", "r");
	if (!f) return -1;


	char* code; char group[2]; int rl; double nav; float perc;
	char* token;
	char buffer[256];
	while (fgets(buffer, 255, f)) {
		token = strtok(buffer, " ,\n");
		code = (char*)malloc(sizeof(char) * strlen(token) + 1);
		strcpy(code, token);

		token = strtok(NULL, " ,\n");
		strncpy(group, token, 2);

		token = strtok(NULL, " ,\n");
		rl = atoi(token);

		token = strtok(NULL, " ,\n");
		nav = atof(token);

		token = strtok(NULL, " ,\n");
		perc = atof(token);

		Fund* inf = createInfo(code, group, rl, nav, perc);

		//printData(inf);
		dl.head = addNode(dl.head, inf);
		if (dl.head->next == NULL) dl.tail = dl.head;
	}

	printHeadList(dl.head);
	//printBackList(dl.tail);

	int c = getNrRisky(dl.head, 4);
	printf("\nRiskier funds: %d", c);

}

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <stdbool.h>


typedef struct Comanda {
	int timp_livrare;
	int cod_client;
	int id_comanda;
	char* numeClient;
	bool livrata;
}Info;


typedef struct BST {
	struct BST* left;
	Info* info;
	struct BST* right;
}BST;



Info* createData(int tl, int cc, int idc, char* nume, bool liv) {
	Info* ret = (Info*)malloc(sizeof(Info));
	ret->numeClient = (char*)malloc(sizeof(char) * (strlen(nume) + 1));

	ret->timp_livrare = tl;
	ret->cod_client = cc;
	ret->id_comanda = idc;
	strcpy(ret->numeClient, nume);
	ret->livrata = liv;

	return ret;
}

void printData(Info* inf) {
	printf("\nTimp Livrare: %d, Cod Client: %d, Id Comanda: %d, Nume: %s, Livrata: %d", inf->timp_livrare, inf->cod_client, inf->id_comanda, inf->numeClient, inf->livrata);
}

BST* makeNode(Info* info) {
	BST* tmp = (BST*)malloc(sizeof(BST));
	tmp->info = createData(info->timp_livrare, info->cod_client, info->id_comanda, info->numeClient, info->livrata);
	tmp->left = NULL;
	tmp->right = NULL;

	return tmp;

}

void addToBST(BST** bst, Info* inf) {

	if (!(*bst)) {
		(*bst) = makeNode(inf);
		return;
	}

	else {
		if ((*bst)->info->id_comanda > inf->id_comanda) addToBST(&(*bst)->left, inf);
		else addToBST(&(*bst)->right, inf);
	}

}

void printInOrdine(BST* bst) {
	if (bst)
	{
		printInOrdine(bst->left);
		printData(bst->info);
		printInOrdine(bst->right);
	}
}


void getNoNodes(BST* bst, int* size) {
	if (bst) {
		getNoNodes(bst->left, size);
		getNoNodes(bst->right, size);
		(*size)++;
	}
}

void populateVector(Info** arr, BST* root, int* i, int minTime) {
	if (root) {
		if (root->info->timp_livrare < minTime) populateVector(arr, root->right, i, minTime);
		else {
			populateVector(arr, root->left, i, minTime);
			arr[(*i)++] = createData(root->info->timp_livrare, root->info->cod_client, root->info->id_comanda, root->info->numeClient, root->info->livrata);
			populateVector(arr, root->right, i, minTime);
		}

	}


}

int main() {
	FILE* file = fopen("DataS1.txt", "r");
	if (!file) return -1;

	BST* bst = NULL;

	int tl, cc, idc; char* nume = NULL; bool liv;
	char buffer[256]; char* token;
	while (fgets(buffer, 256, file)) {
		token = strtok(buffer, " ,\n");
		tl = atoi(token);

		token = strtok(NULL, " ,\n");
		cc = atoi(token);

		token = strtok(NULL, " ,\n");
		idc = atoi(token);

		token = strtok(NULL, ",\n");
		char* nume = (char*)malloc(sizeof(char) * (strlen(token) + 1));
		strcpy(nume, token);

		token = strtok(NULL, " ,\n");
		liv = (token[0] == '0') ? 0 : 1;

		Info* current = createData(tl, cc, idc, nume, liv);
		//printData(current);

		addToBST(&bst, current);


	}

	printf("\nEx1");
	printInOrdine(bst);


	//am alocat pt 7 elemente si folosesc doar 2 but k..
	printf("\nEx2");
	int c = 0;
	getNoNodes(bst, &c);
	Info** vect = (Info**)malloc(sizeof(Info*) * c);
	for (int i = 0; i < c; i++) vect[i] = NULL;
	int i = 0;
	populateVector(vect, bst, &i, 31);
	for (int k = 0; k < i; k++) printData(vect[k]);

	


}

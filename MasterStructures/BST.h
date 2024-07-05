#pragma once
#include "Basics.h"

///BST is a tree where the child to the left has a lesser value than the parent
///and the child to the right has a higher value than the parent

typedef struct BST {
	struct BSTNode* left;
	Info* info;
	struct BSTNode* right;
}BSTNode;

BSTNode* createBSTNode(Info* inf)
{
	BSTNode* tmp = (BSTNode*)malloc(sizeof(BSTNode));
	tmp->info = deepCopyInfo(inf);
	tmp->left = NULL;
	tmp->right = NULL;
	return tmp;
}



void addBSTNode(BSTNode** root, Info* inf)
{
	if (!(*root))
	{
		*root = createBSTNode(inf);
	}

	else
	{
		if (inf->letter < (*root)->info->letter)
			addBSTNode(&(*root)->left, inf);
		else
			addBSTNode(&(*root)->right, inf);
	}
}



//SRD
void printInOrder(BSTNode* root)
{
	if (root)
	{
		printInOrder(root->left);
		printInfo(root->info);
		printInOrder(root->right);
	}
}

//RSD
void printPreOrder(BSTNode* root)
{
	if (root)
	{
		printInfo(root->info);
		printPreOrder(root->left);
		printPreOrder(root->right);
	}
}

//SDR
void printPostOrder(BSTNode* root)
{
	if (root)
	{
		printPostOrder(root->left);
		printPostOrder(root->right);
		printInfo(root->info);
	}
}


Info* seekInBST(BSTNode* root, char letter)
{
	if (!root) return NULL;

	else if(letter == root->info->letter) 
		return deepCopyInfo(root->info);

	else if (letter < root->info->letter)
		return seekInBST(root->left, letter);

	else if (letter > root->info->letter)
		return seekInBST(root->right, letter);
	

}


void deleteBST(BSTNode** root)
{
	if ((*root)->left) deleteBST(&(*root)->left);
	if ((*root)->right) deleteBST(&(*root)->right);
	free((*root)->info->name);
	free((*root)->info);
	free((*root));
	*root = NULL;
}
#pragma once
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>


//just a normal ass .info
typedef struct InformationStruct {
	int nr; //use this to count amount of strings if youre a pxssy
	char** stringslol; //remember to make the last one null so you know to stop cause you didnt work with nr like a pxssy
	double funnydub; //%lf long float

};
typedef struct InformationStruct InformationStruct;

void printStruct(InformationStruct info)
{
	printf("\nInt: %d, Double: %lf,\t Strings: ", info.nr, info.funnydub);
	int i = 0;
	while ((info.stringslol)[i])
	{
		printf("%s, ", info.stringslol[i]);
		i++;
	}
}

InformationStruct* createElem()
{
	InformationStruct* tmp = (InformationStruct*)malloc(sizeof(InformationStruct));
	tmp->stringslol = (char**)malloc(sizeof(char*));
	return tmp;
}

void printElem(InformationStruct* x)
{
	printf("\nInt: %d, Double: %5.2lf, Strings: ", x->nr, x->funnydub);
	int i = 0;
	while (x->stringslol[i])
	{
		printf("%s, ", x->stringslol[i]);
		i++;
	}
}


//file reading
#pragma region OkScrewThese

int getNoStrings(char* token)
{
	int no = 0;
	while (token)
	{
		token = strtok(NULL, " \n");
		no++;
	}
	return no;
}

void putStrings(char** STRINGS, int nr, char* token)
{
	char* token2; //???
	STRINGS = (char**)malloc(sizeof(char*) * (nr + 1)); //want an extra to make it null
	token2 = strtok(token, " \n");

	for (int i = 0; i < nr; i++)
	{
		(STRINGS)[i] = (char*)malloc(sizeof(char) * (strlen(token2) + 1));
		strcpy((STRINGS)[i], token2);
		token2 = strtok(NULL, " \n");

	}
	(STRINGS)[nr] = NULL;
}

void readOne(FILE* f, int* NR, char*** STRINGS, double* DUB) ///ik triple * is scary but i promise its useful :( 

{///but also it could've been done without it if you just created those variables in the function and 
///made the struct in here rather than in createElement

	char buffer[256];
	char* token = NULL;
	fgets(buffer, 256, f);
	token = strtok(buffer, ", ");	//the int
	*NR = atoi(token);

	token = strtok(NULL, ", ");		 //the double
	*DUB = atof(token);		 //maybe learn how to use strtod instead of this idk

	token = strtok(NULL, "");	 //the strings
	int noStr = getNoStrings(token);	 //sent by value to not break it
	putStrings(*STRINGS, noStr, token);


}
#pragma endregion

InformationStruct* readElem(FILE* f)
{
	InformationStruct* tmp = createElem();

	char buffer[256];
	char* token = NULL;
	fgets(buffer, 256, f);
	token = strtok(buffer, ", ");	
	tmp->nr = atoi(token);

	token = strtok(NULL, ", ");		 
	tmp->funnydub = atof(token);	

	char b2[256];
	strcpy(b2, *token);
	char* buffer2 = &b2;
	int nr = getNoStrings(buffer2);
	tmp->stringslol = (char**)realloc(tmp->stringslol, sizeof(char*) * nr);

	int i = 0;
	while (1)
	{
		token = strtok(NULL , " \n");
		if (!token) break;
		tmp->stringslol[i] = (char*)malloc(sizeof(char) * strlen(token));
		strcpy(tmp->stringslol[i], token);
		i++;
		//conditie de oprire
	}
	tmp->stringslol[i] = NULL;

	return tmp;
}


//Simple and Double List

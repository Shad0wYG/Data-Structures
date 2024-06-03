#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include "ABANDONED.h"


int main() 
{
	//quickly testing if printStruct works
	/*InformationStruct info;
	info.stringslol = (char**)malloc(sizeof(char*) * 3);
	for (int i = 0; i < 3; i++) info.stringslol[i] = (char*)malloc(sizeof(char) * 6);
	info.nr = 99, info.funnydub = 0.001, info.stringslol[0] = "ajsdhs", info.stringslol[1] = "string", info.stringslol[2] = NULL;
	printStruct(info);*/

	FILE* f = fopen("Data1.txt", "r");
	if (!f) return -1;
	while (!feof(f))
	{
		InformationStruct* inf = createElem();
		inf = readElem(f);
		printElem(inf);
	}

}


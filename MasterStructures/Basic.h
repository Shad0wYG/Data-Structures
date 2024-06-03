#pragma once
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>


//just a normal ass .info
typedef struct InformationStruct {
	int nr; //use this to count amount of strings if youre a PUSSY
	char** stringslol; //remember to make the last one null so you know to stop cause you didnt work with nr like a pussy
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

InformationStruct createElement(int NR, char** STRINGS, double DUB)
{

}


//file reading

void readOne(FILE* f, int* NR, char*** STRINGS, double* DUB) ///ik triple * is scary but i promise its useful :( 

{///but also it could've been done without it if you just created those variables in the function and 
///made the struct in here rather than in createElement

	char buffer[256];
	fgets(buffer, 256, f);



}



//Simple and Double List

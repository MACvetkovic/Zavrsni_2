#ifndef HEADER_H
#define HEADER_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct {
	char ime[50];
	char prezime[50];
}IGRAC;

typedef struct {
	int id;
	char pitanje[100];
	char odgovorA[50];
	char odgovorB[50];
	char odgovorC[50];
	char Todgovor;
}PITANJA;

void stvaranjedatoteke();
void upis();
int kviz();


#endif 
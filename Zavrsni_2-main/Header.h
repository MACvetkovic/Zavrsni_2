#ifndef HEADER_H
#define HEADER_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct {
	char ime;
	char prezime[50];
	int bodovi;
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
void upis(int brojBodova);
int ucitajPitanja(const char* filename, PITANJA pitanja[]);
void ispisiSveIgrace();
int usporedi(const void* a, const void* b);
void ispisiTop5();

#endif 
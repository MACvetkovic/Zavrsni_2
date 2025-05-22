#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Header.h"

static int igraci = 0;

void stvaranjedatoteke() {
	FILE* fp = NULL;
	const char* datoteka = "igraci.bin";

	fp = fopen(datoteka, "rb");
	if (!fp) {
		fp = fopen(datoteka, "wb");
		if (!fp) {
			return 1;
		}
		fwrite(&igraci, sizeof(int), 1, fp);
		fclose(fp);
	}
	else {
		fclose(fp);
	}
}


void upis() {
	FILE* fp = NULL;
	const char* datoteka = "igraci.bin";

	fp = fopen(datoteka, "rb+");
	if (!fp) {
		return 1;
	}

	IGRAC temp = { 0 };

	getchar();
	printf("Unesite ime!\n");
	scanf("%19[^\n]", temp.ime);

	printf("Unesite prezime!\n");
	getchar();
	scanf("%19[^\n]", temp.prezime);
	igraci++;
	fseek(fp, sizeof(IGRAC) * igraci, SEEK_CUR);
	fwrite(&temp, sizeof(IGRAC), 1, fp);
	rewind(fp);
	fwrite(&igraci, sizeof(int), 1, fp);
	fclose(fp);
}

int kviz() {
	int a, bb = 0;
	char o;
	
	FILE* fp = NULL;
	const char* datoteka = "pitanja.txt";

	fp = fopen(datoteka, "rb+");
	if (!fp) {
		return 1;
	}

	const PITANJA* Pitanje=NULL;

	Pitanje = (PITANJA*)calloc(10, sizeof(PITANJA));
	if (Pitanje == NULL) {
		perror("Zauzimanje memorije za clanove");
		return NULL;
	}

	for (int i = 0; i < 10; i++) {
		

		a= rand() % 120;

		for (int j = 0; j < 120; j++) {

			if (a == (Pitanje + j)->id) {
				printf("ID: %d\n%d. %s\nA): %s\nB): %s\nC): %s\n",
					(Pitanje + j)->id,
					i + 1,
					(Pitanje + j)->pitanje,
					(Pitanje + j)->odgovorA,
					(Pitanje + j)->odgovorB,
					(Pitanje + j)->odgovorC);
			}
			scanf("%c", &o);
			
			if (o == (Pitanje + a)->Todgovor) {
				bb++;
			}
		}
	}
	return bb;
}
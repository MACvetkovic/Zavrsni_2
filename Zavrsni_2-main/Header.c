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


void upis(int brojBodova) {
	FILE* fp = fopen("igraci.bin", "ab");
	if (!fp) {
		perror("Ne mogu otvoriti datoteku igraci.bin");
		return;
	}

	IGRAC igrac;

	getchar(); 
	printf("Unesite ime: ");
	scanf("%19[^\n]", igrac.ime);

	getchar(); 
	printf("Unesite prezime: ");
	scanf("%19[^\n]", igrac.prezime);

	igrac.bodovi = brojBodova;

	fwrite(&igrac, sizeof(IGRAC), 1, fp);

	fclose(fp);
}

int ucitajPitanja(const char* filename, PITANJA pitanja[]) {
	FILE* file = fopen(filename, "r");
	if (!file) {
		perror("Ne mogu otvoriti datoteku");
		return 0;
	}

	char linija[100];
	int count = 0;

	while (fgets(linija, sizeof(linija), file) && count < 10) {
		pitanja[count].id = atoi(linija);

		fgets(pitanja[count].pitanje, sizeof(pitanja[count].pitanje), file);
		fgets(pitanja[count].odgovorA, sizeof(pitanja[count].odgovorA), file);
		fgets(pitanja[count].odgovorB, sizeof(pitanja[count].odgovorB), file);
		fgets(pitanja[count].odgovorC, sizeof(pitanja[count].odgovorC), file);
		fgets(linija, sizeof(linija), file);


		pitanja[count].pitanje[strcspn(pitanja[count].pitanje, "\n")] = 0;
		pitanja[count].odgovorA[strcspn(pitanja[count].odgovorA, "\n")] = 0;
		pitanja[count].odgovorB[strcspn(pitanja[count].odgovorB, "\n")] = 0;
		pitanja[count].odgovorC[strcspn(pitanja[count].odgovorC, "\n")] = 0;
		pitanja[count].Todgovor = linija[0];

		count++;
	}

	fclose(file);
	return count;
}

void ispisiSveIgrace() {
	FILE* fp = fopen("igraci.bin", "rb");
	if (!fp) {
		perror("Ne mogu otvoriti datoteku igraci.bin");
		return;
	}

	IGRAC igrac;
	printf("\nLista igraca:\n");
	while (fread(&igrac, sizeof(IGRAC), 1, fp) == 1) {
		printf("%s %s - Bodovi: %d\n", igrac.ime, igrac.prezime, igrac.bodovi);
	}

	fclose(fp);
}

int usporedi(const void* a, const void* b) {
	IGRAC* ia = (IGRAC*)a;
	IGRAC* ib = (IGRAC*)b;
	return ib->bodovi - ia->bodovi;
}

void ispisiTop5() {
	FILE* fp = fopen("igraci.bin", "rb");
	if (!fp) {
		perror("Ne mogu otvoriti datoteku igraci.bin");
		return;
	}

	
	fseek(fp, 0, SEEK_END);
	long size = ftell(fp);
	int brojIgraca = size / sizeof(IGRAC);
	rewind(fp);

	if (brojIgraca == 0) {
		printf("Nema zapisanih igraca.\n");
		fclose(fp);
		return;
	}

	IGRAC* igraci = malloc(size);
	if (!igraci) {
		printf("Nema dovoljno memorije.\n");
		fclose(fp);
		return;
	}

	fread(igraci, sizeof(IGRAC), brojIgraca, fp);
	fclose(fp);

	
	qsort(igraci, brojIgraca, sizeof(IGRAC), usporedi);

	
	int limit = brojIgraca < 5 ? brojIgraca : 5;
	printf("Top %d igraca po bodovima:\n", limit);
	for (int i = 0; i < limit; i++) {
		printf("%d. %s %s - %d bodova\n", i + 1, igraci[i].ime, igraci[i].prezime, igraci[i].bodovi);
	}

	free(igraci);
}
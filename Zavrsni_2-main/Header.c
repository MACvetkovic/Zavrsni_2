#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Header.h"


void upis(int brojBodova) {
	FILE* fp = fopen("igraci.bin", "ab+");
	if (!fp) {
		perror("Ne mogu otvoriti datoteku igraci.bin");
		return;
	}

	IGRAC *igrac;
	IGRAC *temp;
	int maxId = 0;

	
	while (fread(&temp, sizeof(IGRAC), 1, fp) == 1) {
		if (temp->id > maxId) {
			maxId = temp->id;
		}
	}

	igrac->id = maxId + 1;

	printf("Unesi ime: ");
	scanf("%19s", igrac->ime);

	printf("Unesi prezime: ");
	scanf("%19s", igrac->prezime);

	igrac->bodovi = brojBodova;

	fwrite(&igrac, sizeof(IGRAC), 1, fp);
	
	free(igrac);
	igrac = NULL;
	fclose(fp);
}

int ucitajPitanja(const char* filename, PITANJA* pitanja) {
	FILE* file = fopen(filename, "r");
	if (!file) {
		perror("Ne mogu otvoriti datoteku");
		return 0;
	}

	char linija[100];
	int count = 0;

	while (fgets(linija, sizeof(linija), file) && count < 100) {
		pitanja[count].id = atoi(linija);

		fgets((pitanja + count)->pitanje, sizeof((pitanja + count)->pitanje), file);
		fgets((pitanja + count)->odgovorA, sizeof((pitanja + count)->odgovorA), file);
		fgets((pitanja + count)->odgovorB, sizeof((pitanja + count)->odgovorB), file);
		fgets((pitanja + count)->odgovorC, sizeof((pitanja + count)->odgovorC), file);
		fgets(linija, sizeof(linija), file);


		(pitanja + count)->pitanje[strcspn((pitanja + count)->pitanje, "\n")] = 0;
		(pitanja + count)->odgovorA[strcspn((pitanja + count)->odgovorA, "\n")] = 0;
		(pitanja + count)->odgovorB[strcspn((pitanja + count)->odgovorB, "\n")] = 0;
		(pitanja + count)->odgovorC[strcspn((pitanja + count)->odgovorC, "\n")] = 0;
		(pitanja + count)->Todgovor = linija[0];

		count++;
	}

	srand(time(NULL));

	for (int i = count - 1; i > 0; i--) {
		int j = rand() % (i + 1);
		PITANJA temp = pitanja[i];
		pitanja[i] = pitanja[j];
		pitanja[j] = temp;
	}


	fclose(file);
	return count;
}

void ispisiSveIgraceRekurzivno(FILE* fp) {
	IGRAC igrac;
	if (fread(&igrac, sizeof(IGRAC), 1, fp) != 1) {
		return;
	}

	printf("%d. %s %s - Bodovi: %d\n", igrac.id, igrac.ime, igrac.prezime, igrac.bodovi);

	ispisiSveIgraceRekurzivno(fp);
}

void ispisiSveIgrace() {
	FILE* fp = fopen("igraci.bin", "rb");
	if (!fp) {
		perror("Ne mogu otvoriti datoteku igraci.bin");
		return;
	}

	printf("\nLista igraca:\n");
	ispisiSveIgraceRekurzivno(fp);

	fclose(fp);
}

static int usporedi(const void* a, const void* b) {
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
		printf("Nema zapisanih igraca.\n\n\n");
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
		printf("%d. %s %s - %d bodova\n", i + 1, (igraci+i)->ime, (igraci+i)->prezime, (igraci+i)->bodovi);
	}

	free(igraci);
	igraci = NULL;
}

void obrisiIgracaPoID(int trazeniID) {
	FILE* fp = fopen("igraci.bin", "rb");
	if (!fp) {
		perror("Ne mogu otvoriti datoteku za čitanje");
		return;
	}

	FILE* temp = fopen("temp.bin", "wb");
	if (!temp) {
		perror("Ne mogu otvoriti privremenu datoteku");
		fclose(fp);
		return;
	}

	IGRAC igrac;
	int pronadjen = 0;

	while (fread(&igrac, sizeof(IGRAC), 1, fp) == 1) {
		if (igrac.id != trazeniID) {
			fwrite(&igrac, sizeof(IGRAC), 1, temp);
		}
		else {
			pronadjen = 1;
		}
	}

	fclose(fp);
	fclose(temp);

	if (pronadjen) {
		remove("igraci.bin");
		rename("temp.bin", "igraci.bin");
		printf("Igrac s ID-om %d je obrisan.\n", trazeniID);
	}
	else {
		remove("temp.bin");
		printf("Igrac s ID-om %d nije pronađen.\n", trazeniID);
	}
}
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

void kviz() {

}
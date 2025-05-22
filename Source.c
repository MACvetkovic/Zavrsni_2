#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Header.h"

int main() {
	stvaranjedatoteke();
	int a,z=0;

	do {
		printf("====================");
		printf("Odaberite jednu od ponudenih opcija:");
		printf("====================\n");
		printf("\t\tOpcija 1: Pokreni kviz\n");
		printf("\t\tOpcija 2: Tablica\n");
		printf("\t\tOpcija 3: Pretrazivanje pitanja\n");
		printf("\t\tOpcija 4: Pretrazi korisnika po ID-u i njegovo ispisivanje\n");
		printf("\t\tOpcija 5: Zavrsetak programa\n");
		printf("======================================\======================================\n");

		scanf("%d", &a);


		switch (a) {
		case 1:
			upis();
			kviz();
			break;
		default:
			return 0;
		}
	} while (z == 0);

	return 0;
}
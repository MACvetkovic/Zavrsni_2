#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Header.h"

int main() {
	stvaranjedatoteke();
	int a,z=0,bodovi=0;
	PITANJA pitanja[10];
	do {
		printf("====================");
		printf("Odaberite jednu od ponudenih opcija:");
		printf("====================\n");
		printf("\t\tOpcija 1: Pokreni kviz\n");
		printf("\t\tOpcija 2: Tablica\n");
		printf("\t\tOpcija 3: Ispis svih igraca\n");
		printf("\t\tOpcija 4: Pretrazi korisnika po ID-u i njegovo ispisivanje\n");
		printf("\t\tOpcija 5: Zavrsetak programa\n");
		printf("======================================\======================================\n");

		scanf("%d", &a);


		switch (a) {
		case 1:
			ucitajPitanja("pitanja.txt", pitanja);
			for (int i = 0; i < 10; i++) {
				printf("\nPitanje %d: %s\n", pitanja[i].id, pitanja[i].pitanje);
				printf("A) %s\n", pitanja[i].odgovorA);
				printf("B) %s\n", pitanja[i].odgovorB);
				printf("C) %s\n", pitanja[i].odgovorC);

				char odgovor;
				printf("Vas odgovor (A, B, C): ");
				scanf(" %c", &odgovor);

				odgovor = toupper(odgovor);

				if (odgovor == pitanja[i].Todgovor) {
					printf("Tocno!\n");
					bodovi++;
				}
				else {
					printf("Netocno! Tocan odgovor je: %c\n", pitanja[i].Todgovor);
				}
			}
			upis(bodovi);
			break;
		case 2:
			ispisiTop5();
			break;
		case 3:
			ispisiSveIgrace();
			break;
		default:
			return 0;
		}
	} while (z == 0);

	return 0;
}
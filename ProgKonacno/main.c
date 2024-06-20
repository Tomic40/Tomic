#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "header.h"

int main() {
	printf("\n-----Dobrodosli u sustav za pracenje voznog parka logisticke tvrtke!-----\n-----U nastavku imate izbornik pomocu kojeg mozete upravljati sustavom.-----\n-----Ozake za kilometre, litre i sate ne morate pisati!-----\n");
    int izbor;

    do {
        printf("\nGlavni izbornik:\n");
        printf("1. Prijava kao administrator\n");
        printf("2. Prijava kao korisnik\n");
        printf("3. Izlaz\n");
        printf("Odaberite opciju: ");
        scanf("%d", &izbor);
        getchar(); // ?isti newline iz buffer-a

        switch (izbor) {
        case 1:
            prijavaAdministratora();
            break;
        case 2:
            prijavaKorisnika();
            break;
        case 3:
            printf("Izlaz iz programa.\n");
            return 0;
            break;
        default:
            printf("Nepostojeca opcija. Pokusajte ponovno.\n");
        }
    } while (izbor != 3);

	return 0;
}
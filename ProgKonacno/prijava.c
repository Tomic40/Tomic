#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "header.h"

void prijavaAdministratora() {
    char korisnickoIme[20];
    char lozinka[20];

    printf("Unesite korisnicko ime (admin): ");
    fgets(korisnickoIme, sizeof(korisnickoIme), stdin);
    strtok(korisnickoIme, "\n");

    printf("Unesite lozinku(admin123): ");
    fgets(lozinka, sizeof(lozinka), stdin);
    strtok(lozinka, "\n");

    // provjera korisnickog imena i lozinke
    if (strcmp(korisnickoIme, "admin") == 0 && strcmp(lozinka, "admin123") == 0) {
        printf("\nDobrodosli, administrator!\n");
        int izbor;
        do {
            printf("\nAdministratorske opcije:\n");
            printf("1. Dodaj kamion\n");
            printf("2. Dodaj vozaca\n");
            printf("3. Planiraj rutu\n");
            printf("4. Generiraj izvjestaj\n");
            printf("5. Izbrisi kamion\n");
            printf("6. Izbrisi vozaca\n");
            printf("7. Izbrisi rutu\n");
            printf("8. Sortiraj kamione\n");
            printf("9. Pretrazi kamione\n");
            printf("10. Brisanje cijele datoteke kamiona\n");
            printf("11. Izlaz\n");
            printf("Odaberite opciju: ");
            scanf("%d", &izbor);
            getchar(); 


            switch (izbor) {
            case 1:
                dodajKamione();
                break;
            case 2:
                dodajVozaca();
                break;
            case 3:
                dodajRutu();
                break;
            case 4:
                generirajIzvjestaj();
                break;
            case 5:
                obrisiKamion();
                break;
            case 6:
                brisiVozaca();
                break;
            case 7:
                brisiRutu();
                break;
            case 8:
                sortirajKamionePoModelu();
                break;
            case 9:
                pretraziKamionePoRegistraciji();
                break;
            case 10:
                brisanjeDatotekeKamiona(); 
                break;
            case 11:
                printf("Izlaz iz administratorskog izbornika.\n");
                break;
            default:
                printf("Nepostojeca opcija. Pokusajte ponovno.\n");
            }
        } while (izbor != 11);
        return 0;

    }

    else {
        printf("Pogresno korisnicko ime ili lozinka. Pokusajte ponovno.\n");
    }

}

void prijavaKorisnika() {

    printf("\nDobrodosli, korisnik!\n");
    int izbor;
    do {
        printf("\nKorisnicke opcije:\n");
        printf("1. Dodaj kamion\n");
        printf("2. Dodaj vozaca\n");
        printf("3. Planiraj rutu\n");
        printf("4. Generiraj izvjestaj\n");
        printf("5. Sortiraj kamione\n");
        printf("6. Pretrazi kamione\n");
        printf("7. azuriraj kilometrazu kamiona\n");
        printf("8. Izlaz\n");
        printf("Odaberite opciju: ");
        scanf("%d", &izbor);
        getchar(); // ocisti newline iz buffer-a
        

        switch (izbor) {
        case 1:
            dodajKamione();
            break;
        case 2:
            dodajVozaca();
            break;
        case 3:
             dodajRutu();
            break;
       case 4:
            generirajIzvjestaj();
            break;
        case 5:
            sortirajKamionePoModelu();
            break;
        case 6:
            pretraziKamionePoRegistraciji();
            break;
        case 7:
            azurirajKilometaraKamiona();
            break;
        case 8:
            printf("Izlaz iz korisnickog izbornika.\n");
            break;
        default:
            printf("Nepostojeca opcija. Pokusajte ponovno.\n");
        }
    } while (izbor != 8);
    return 0;
}




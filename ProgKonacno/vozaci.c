#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"


/*void sigurnoOslobodi(void** ptr) {
	if (*ptr != NULL) {
		free(*ptr);
		*ptr = NULL;
	}
}*/
void dodajVozaca() {
    FILE* file = fopen("vozaci.txt", "r+");
    if (file == NULL) {
        // Datoteka ne postoji ili nije moguće otvoriti u read/write modu, probajmo otvoriti u append modu
        file = fopen("vozaci.txt", "a+");
        if (file == NULL) {
            perror("Ne moze se otvoriti datoteka za vozace");
            exit(1);
        }
    }

    Vozac* noviVozac = (Vozac*)malloc(sizeof(Vozac));
    if (noviVozac == NULL) {
        perror("Ne moze se alocirati memorija za novog vozaca");
        fclose(file);
        exit(1);
    }

    printf("Unesite ID: ");
    if (scanf("%d", &noviVozac->id) != 1) {
        printf("Neispravan unos ID-a.\n");
        fclose(file);
        free(noviVozac);
        return;
    }

    // Provjera da li ID već postoji
   // Provjera da li ID već postoji
    fseek(file, 0, SEEK_SET); // Premjesti pokazivač na početak datoteke
    char line[256]; // Pretpostavka: linija neće biti dulja od 255 znakova
    int idPostoji = 0;

    while (fgets(line, sizeof(line), file) != NULL) {
        int id;
        if (sscanf(line, "ID vozaca: %d", &id) == 1) {
            if (id == noviVozac->id) {
                idPostoji = 1;
                break;
            }
        }
    }


    if (idPostoji) {
        printf("Vozac sa ID %d vec postoji.\n", noviVozac->id);
        fclose(file);
        free(noviVozac);
        return;
    }

    printf("Unesite ime: ");
    if (scanf("%s", noviVozac->ime) != 1) {
        fclose(file);
        free(noviVozac);
        return;
    }

    printf("Unesite prezime: ");
    if (scanf("%s", noviVozac->prezime) != 1) {
        fclose(file);
        free(noviVozac);
        return;
    }

    printf("Unesite broj vozacke dozvole: ");
    if (scanf("%s", noviVozac->vozackaDozvola) != 1) {
        printf("Neispravan unos broja vozacke dozvole.\n\n");
        fclose(file);
        free(noviVozac);
        return;
    }

    printf("Unesite godine iskustva: ");
    if (scanf("%s", noviVozac->godineIskustva) != 1) {
        printf("Neispravan unos godina iskustva.\n\n");
        fclose(file);
        free(noviVozac);
        return;
    }

    // Premjesti pokazivač na kraj datoteke za dodavanje novog vozača
    fseek(file, 0, SEEK_END);
    fprintf(file, "ID vozaca: %d\nIme vozaca: %s\nPrezime vozaca: %s\nBroj vozacke dozvole: %s\nGodine iskustva: %s\n\n", noviVozac->id, noviVozac->ime, noviVozac->prezime, noviVozac->vozackaDozvola, noviVozac->godineIskustva);

    fclose(file);
    free(noviVozac);
    printf("Vozac uspjesno dodan.\n\n");
}

void brisiVozaca() {
    int id;
    printf("Unesite ID vozaca za brisanje: ");
    if (scanf("%d", &id) != 1) {
        printf("Neispravan unos ID-a.\n");
        return;
    }

    FILE* file = fopen("vozaci.txt", "r");
    if (file == NULL) {
        perror("Ne moze se otvoriti datoteka za citanje vozaca");
        return;
    }

    Vozac* vozaci = NULL;
    int brojVozaca = 0;
    Vozac tempVozac;

    // Učitavanje svih vozača iz datoteke
    while (fscanf(file, "%d %49s %49s %19s %9s", &tempVozac.id, tempVozac.ime, tempVozac.prezime, tempVozac.vozackaDozvola, tempVozac.godineIskustva) == 5) {
        Vozac* noviVozaci = realloc(vozaci, sizeof(Vozac) * (brojVozaca + 1));
        if (noviVozaci == NULL) {
            perror("Ne moze se alocirati memorija za vozace");
            fclose(file);
            free(vozaci);
            return;
        }
        vozaci = noviVozaci;
        vozaci[brojVozaca++] = tempVozac;
    }
    fclose(file);

    // Pronalazak i brisanje vozača sa zadanim ID-om
    int found = 0;
    for (int i = 0; i < brojVozaca; i++) {
        if (vozaci[i].id == id) {
            for (int j = i; j < brojVozaca - 1; j++) {
                vozaci[j] = vozaci[j + 1];
            }
            brojVozaca--;
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Vozac sa ID %d nije pronaden.\n", id);
        free(vozaci);
        return;
    }

    file = fopen("vozaci.txt", "w");
    if (file == NULL) {
        perror("Ne moze se otvoriti datoteka za pisanje vozaca");
        free(vozaci);
        return;
    }

    for (int i = 0; i < brojVozaca; i++) {
        fprintf(file, "%d %s %s %s %s\n", vozaci[i].id, vozaci[i].ime, vozaci[i].prezime, vozaci[i].vozackaDozvola, vozaci[i].godineIskustva);
    }
    fclose(file);

    free(vozaci);
    printf("Vozac sa ID %d je uspjesno obrisan.\n", id);
}





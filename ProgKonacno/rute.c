#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

void dodajRutu() {
    FILE* file = fopen("rute.txt", "a+");
    if (file == NULL) {
        perror("Ne moze se otvoriti datoteka za rute");
        exit(1);
    }

    Ruta* novaRuta = (Ruta*)malloc(sizeof(Ruta));
    if (novaRuta == NULL) {
        perror("Ne moze se alocirati memorija za novou rutu");
        fclose(file);
        exit(1);
    }
    printf("Unesite ID: ");
    if (scanf("%d", &novaRuta->id) != 1) {
        printf("Neispravan unos ID-a.\n");
        fclose(file);
        free(novaRuta);
        return 1;
    }

    // Provjera da li ID već postoji
    fseek(file, 0, SEEK_SET); // Premjesti pokazivač na početak datoteke
    char line[256]; // Pretpostavka: linija neće biti dulja od 255 znakova
    int idPostojeci = 0;

    while (fgets(line, sizeof(line), file) != NULL) {
        int id;
        if (sscanf(line, "ID vozaca: %d", &id) == 1) {
            if (id == novaRuta->id) {
                idPostojeci = 1;
                break;
            }
        }
    }

    if (idPostojeci) {
        printf("Ruta sa ID %d vec postoji.\n", novaRuta->id);
        fclose(file);
        free(novaRuta);
        return 1;
    }

    printf("Unesite ID kamiona: ");
    if (scanf("%d", &novaRuta->idKamiona) != 1) {
        fclose(file);
        free(novaRuta);
        return 1;
    }

    printf("Unesite ID vozaca: ");
    if (scanf("%d", &novaRuta->idVozaca) != 1) {
        fclose(file);
        free(novaRuta);
        return 1;
    }


    printf("Unesite pocetnu lokaciju: ");
    if (scanf("%s", novaRuta->pocetnaLokacija) != 1) {
        fclose(file);
        free(novaRuta);
        return 1;
    }


    printf("Unesite krajnju lokaciju: ");
    if (scanf("%s", novaRuta->krajnjaLokacija) != 1) {
        fclose(file);
        free(novaRuta);
        return 1;
    }


    printf("Unesite udaljenost u km: ");
    if (scanf("%f", &novaRuta->udaljenost) != 1) {
        fclose(file);
        free(novaRuta);
        return 1;
    }

    printf("Unesite trajanje rute u h: ");
    if (scanf("%f", &novaRuta->trajanje) != 1) {
        fclose(file);
        free(novaRuta);
        return 1;
    }

    fprintf(file, "ID rute: %d\nID kamiona: %d\nID vozaca: %d\nPocetna lokacija: %s\nKrajnja lokacija: %s\nUdaljenost: %.2f km\nTrajanje rute: %.2f h\n\n", novaRuta->id, novaRuta->idKamiona, novaRuta->idVozaca, novaRuta->pocetnaLokacija, novaRuta->krajnjaLokacija, novaRuta->udaljenost, novaRuta->trajanje);

    fclose(file);
    free(novaRuta);

    printf("Ruta uspjesno dodana.\n\n");

    return 0;
}
void brisiRutu() {
    int id;
    printf("Unesite ID rute za brisanje: ");
    if (scanf("%d", &id) != 1) {
        printf("Neispravan unos ID-a.\n");
        return;
    }

    FILE* file = fopen("rute.txt", "r");
    if (file == NULL) {
        perror("Ne moze se otvoriti datoteka za citanje ruta");
        return;
    }

    Ruta* rute = NULL;
    int brojRuta = 0;
    Ruta tempRuta;

    // Učitavanje svih vozača iz datoteke
    while (fscanf(file, "%d %d %d %s %s %f %f", &tempRuta.id, &tempRuta.idKamiona, &tempRuta.idVozaca, tempRuta.pocetnaLokacija, tempRuta.krajnjaLokacija, &tempRuta.udaljenost, &tempRuta.trajanje) == 7) {
        Ruta* novaRuta = realloc(rute, sizeof(Ruta) * (brojRuta + 1));
        if (novaRuta == NULL) {
            perror("Ne moze se alocirati memorija za rute");
            fclose(file);
            return;
        }
        rute = novaRuta;
        rute[brojRuta++] = tempRuta;
    }
    fclose(file);

    // Pronalazak i brisanje vozača sa zadanim ID-om
    int found = 0;
    for (int i = 0; i < brojRuta; i++) {
        if (rute[i].id == id) {
            for (int j = i; j < brojRuta - 1; j++) {
                rute[j] = rute[j + 1];
            }
            brojRuta--;
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Ruta sa ID %d nije pronaden.\n", id);
        return;
    }

    file = fopen("rute.txt", "w");
    if (file == NULL) {
        perror("Ne moze se otvoriti datoteka za pisanje ruta");
        return;
    }

    for (int i = 0; i < brojRuta; i++) {
        fprintf(file, "%d %d %d %s %s %.2f %.2f\n", rute[i].id, rute[i].idKamiona, rute[i].idVozaca, rute[i].pocetnaLokacija, rute[i].krajnjaLokacija, rute[i].udaljenost, rute[i].trajanje);
    }
    fclose(file);

    printf("Ruta sa ID %d je uspjesno obrisan.\n", id);
}

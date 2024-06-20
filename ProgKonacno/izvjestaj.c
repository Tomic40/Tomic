#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"
Kamion* ucitajKamione(int* brojKamiona) {
    FILE* file = fopen("kamioni.txt", "r");
    if (file == NULL) {
        perror("Ne moze se otvoriti datoteka kamioni.txt");
        return NULL;
    }

    Kamion* kamioni = NULL;
    Kamion tempKamion;
    *brojKamiona = 0;

    printf("Ucitavanje kamiona...\n");
    while (fscanf(file, "%d %49s %49s %d %d %d", &tempKamion.id, tempKamion.registracija, tempKamion.model, &tempKamion.godinaProizvodnje, &tempKamion.kilometraza, &tempKamion.stanjeGoriva) == 6) {
        Kamion* noviKamioni = realloc(kamioni, sizeof(Kamion) * (*brojKamiona + 1));
        if (noviKamioni == NULL) {
            perror("Ne moze se alocirati memorija za kamione");
            free(kamioni);
            fclose(file);
            return NULL;
        }
        kamioni = noviKamioni;
        kamioni[*brojKamiona] = tempKamion;
        (*brojKamiona)++;
    }
    printf("Ucitano kamiona: %d\n", *brojKamiona);

    fclose(file);
    return kamioni;
}

Vozac* ucitajVozace(int* brojVozaca) {
    FILE* file = fopen("vozaci.txt", "r");
    if (file == NULL) {
        perror("Ne moze se otvoriti datoteka vozaci.txt");
        return NULL;
    }

    Vozac* vozaci = NULL;
    Vozac tempVozac;
    *brojVozaca = 0;

    printf("Ucitavanje vozaca...\n");
    while (fscanf(file, "%d %49s %49s %19s %9s", &tempVozac.id, tempVozac.ime, tempVozac.prezime, tempVozac.vozackaDozvola, tempVozac.godineIskustva) == 5) {
        Vozac* noviVozaci = realloc(vozaci, sizeof(Vozac) * (*brojVozaca + 1));
        if (noviVozaci == NULL) {
            perror("Ne moze se alocirati memorija za vozace");
            free(vozaci);
            fclose(file);
            return NULL;
        }
        vozaci = noviVozaci;
        vozaci[*brojVozaca] = tempVozac;
        (*brojVozaca)++;
    }
    printf("Ucitano vozaca: %d\n", *brojVozaca);

    fclose(file);
    return vozaci;
}

Ruta* ucitajRute(int* brojRuta) {
    FILE* file = fopen("rute.txt", "r");
    if (file == NULL) {
        perror("Ne moze se otvoriti datoteka rute.txt");
        return NULL;
    }

    Ruta* rute = NULL;
    Ruta tempRuta;
    *brojRuta = 0;

    printf("Ucitavanje ruta...\n");
    while (fscanf(file, "%d %d %d %49s %49s %f %f", &tempRuta.id, &tempRuta.idKamiona, &tempRuta.idVozaca, tempRuta.pocetnaLokacija, tempRuta.krajnjaLokacija, &tempRuta.udaljenost, &tempRuta.trajanje) == 7) {
        Ruta* noveRute = realloc(rute, sizeof(Ruta) * (*brojRuta + 1));
        if (noveRute == NULL) {
            perror("Ne moze se alocirati memorija za rute");
            free(rute);
            fclose(file);
            return NULL;
        }
        rute = noveRute;
        rute[*brojRuta] = tempRuta;
        (*brojRuta)++;
    }
    printf("Ucitano ruta: %d\n", *brojRuta);

    fclose(file);
    return rute;
}

void generirajIzvjestaj() {
    int brojKamiona = 0;
    int brojVozaca = 0;
    int brojRuta = 0;

    Kamion* kamioni = ucitajKamione(&brojKamiona);
    Vozac* vozaci = ucitajVozace(&brojVozaca);
    Ruta* rute = ucitajRute(&brojRuta);

    if (kamioni == NULL || vozaci == NULL || rute == NULL) {
        printf("Greska pri ucitavanju podataka.\n");
        free(kamioni);
        free(vozaci);
        free(rute);
        return;
    }

    FILE* file = fopen("izvjestaj.txt", "w");
    if (file == NULL) {
        perror("Ne može se otvoriti datoteka za izvještaj");
        free(kamioni);
        free(vozaci);
        free(rute);
        return;
    }

    fprintf(file, "===== Izvjestaj o Kamionima =====\n");
    for (int i = 0; i < brojKamiona; i++) {
        fprintf(file, "ID: %d\nRegistracija: %s\nModel: %s\nGodina proizvodnje: %d\nKilometraza: %d\nStanje goriva: %d\n\n",
            kamioni[i].id, kamioni[i].registracija, kamioni[i].model, kamioni[i].godinaProizvodnje,
            kamioni[i].kilometraza, kamioni[i].stanjeGoriva);
    }

    fprintf(file, "\n===== Izvjestaj o Vozacima =====\n");
    for (int i = 0; i < brojVozaca; i++) {
        fprintf(file, "ID: %d\nIme: %s\nPrezime: %s\nBroj vozacke dozvole: %s\nGodine iskustva: %s\n\n",
            vozaci[i].id, vozaci[i].ime, vozaci[i].prezime, vozaci[i].vozackaDozvola, vozaci[i].godineIskustva);
    }

    fprintf(file, "\n===== Izvjestaj o Rutama =====\n");
    for (int i = 0; i < brojRuta; i++) {
        fprintf(file, "ID: %d\nKamion ID: %d\nVozac ID: %d\nPocetna lokacija: %s\nKrajnja lokacija: %s\nUdaljenost: %.2f km\nTrajanje: %.2f\n\n",
            rute[i].id, rute[i].idKamiona, rute[i].idVozaca, rute[i].pocetnaLokacija, rute[i].krajnjaLokacija, rute[i].udaljenost, rute[i].trajanje);
    }

    fclose(file);
    free(kamioni);
    free(vozaci);
    free(rute);

    printf("Izvjestaj je uspjesno generisan u fajlu 'izvjestaj.txt'.\n");
}
#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>


#define REG 20      //s ovim smo izbjegli VLA
#define MODEL 20
#define REGA 20

// definicija struktura koristeci typedef
typedef struct {
    int id;
    char registracija[REG];
    char trazenaRegistracija[REGA];
    char model[MODEL];
    int godinaProizvodnje;
    int kilometraza;
    int stanjeGoriva;
} Kamion;


#define IME 20
#define PREZIME 20
#define VOZACKA 20
#define ISKUSTVO 2

typedef struct {
    int id;
    char ime[IME];
    char prezime[PREZIME];
    char vozackaDozvola[VOZACKA];
   char godineIskustva[ISKUSTVO];
} Vozac;

#define P_LOKACIJA 50
#define K_LOKACIJA 50

typedef struct {
    int id;
    int idKamiona;
    int idVozaca;
    char pocetnaLokacija[P_LOKACIJA];
    char krajnjaLokacija[K_LOKACIJA];
    float udaljenost;
    float trajanje;
} Ruta;

//prijava
extern void prijavaAdministratora();
extern void prijavaKorisnika();

//Kamioni
extern void dodajKamione();
extern void obrisiKamion();
extern void pretraziKamionePoRegistraciji();
extern void sortirajKamionePoModelu();
extern void brisanjeDatotekeKamiona();
extern void azurirajKilometaraKamiona();

//vozaci
extern void dodajVozaca();
extern void brisiVozaca();

//rute
extern void dodajRutu();
extern void brisiRutu();

//generiranje izvjestaja
extern void generirajIzvjestaj();





#endif // HEADER_H


/*
Obavezni koncepti
1. Odabir konkretnih primitivnih tipova podataka za rad s cjelobrojnim i realnim konstantama.   DA
2. Odabir konkretnih složenih tipova podataka za rad sa specifi?nim objektima.                  DA
3. Primjena typedef sa strukturama i unijama, po potrebi s enum tipovima podataka tamo gdje     DA
treba.
4. Imenovanje identifikatora (varijabli, konstanti, polja, funkcija, pokaziva?a…) – upotreba
camelCase, PascalCase i snake_case konzistento kroz cijeli projekt.                                         DA
5. Primjena klju?ne rije?i static za globalne i lokalne varijable.                                      DA?
6. Organizacija izvornog kôda.                                                                  DA
7. Primjena extern klju?ne rije?i za globalne varijable.                                                    DA
8. Ako su funkcije jednostavne koristiti makro funkcije ili inline funkcije.                                ?--------------
9. Izbornik/podizbornici.                                                                       DA
10. Generalno upotreba pokaziva?a tamo gdje su potrebni.                                                DA
11. Generalno upotreba struktura i funkcija.                                                    DA
12. Zaštita parametara kod svih funkcija.                                                                   DA
13. Koristiti stati?ki zauzeta polja gdje su potrebna, nikako ne koristiti VLA polja.                   DA
14. Koristiti dinami?ko zauzimanje memorije za bilo koji tip podatka, osobito za složene tipove             DA
podataka.
15. Koristiti funkcije malloc(), calloc(), realloc(), free() – neku od njih, ako ne i sve.                  DA
16. Sigurno brisanje memorije koja je dinami?ki zauzeta, anuliranje memorijskog prostora, provjera          DA
pokaziva?a kako se ne bi dogodila pogreška double free() i anuliranje svih pokaziva?a koji su bili
usmjereni na memorijski prostor koji se dinami?ki zauzeo.
17. Datoteke, koristiti tekstualnu ili binarnu, provjera pokaziva?a i zatvaranje datoteke.              DA
18. Koristiti funkcije fseek(), ftell(), rewind(), ovisno o potrebi – neku od njih ako ne sve.              DA
19. Koristiti funkcije remove(), rename(), po potrebi implementirati funkciju za kopiranje datoteka.        
20. Upravljati s pogreškama, errno, perror(), strerror(), feof(), ferror() – neku od njih ako ne sve.   DA
21. Sortiranje – preporuka koristiti ugra?enu qsort() funkciju.                                             DA
22. Pretraživanje – preporuka koristiti ugra?enu bsearch() funkciju.                                        DA
23. Rekurzije je najlakše koristiti primjenom rekurzivnih algoritama sortiranja kao što su quick sort,      NE-----------------
merge sort, insert sort ili pretraživanja kao što je binary search.
24. Pokaziva?e na funkcije je najlakše koristiti upotrebom funkcije qsort() ili bsearch() iz standardne     DA
biblioteke.
*/

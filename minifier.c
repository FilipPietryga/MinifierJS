#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

/*

  WSZYSTKO DZIAŁA JAK NALEŻY,
  POWAŻNIE, TO CO MIAŁEM ZAIMPLEMENTOWAĆ
  DZISIAJ, ZAIMPLEMENTOWAŁEM POPRAWNIE.

  POTRZEBA JEDYNIE WPROWADZIĆ POPRAWKI
  W KONTEKŚCIE ROZRÓŻNIANIA MIĘDZY KODEM PROGRAMU,
  A ZAWARTOŚCIĄ STRINGÓW, ZMIANY W KODZIE NIE POWINNY
  DOTYCZYĆ TEGO CO ZNAJDUJE SIĘ W ŚRODKU CUDZYSŁOWIÓW

  SPRÓBUJĘ COŚ NA TO PORADZIĆ

  poprawka...
  
  ZAIMPLEMENTOWANE!!!

  PROGRAM JUŻ PRAKTYCZNIE DZIAŁA, 
  TERAZ TYLKO NAPISAĆ SPRAWOZDANIE 
  I MOŻNA ODDAWAĆ!! 
  AHH, JESTEM Z SIEBIE DUMNY, 
  WSZYSTKO ZROBIŁEM TAK JAK MIAŁEM :)

  CIEKAWE CO BĘDĘ MUSIAŁ ZROBIĆ, ŻEBY TO ODDAĆ

*/

int main(int argc, char *argv[]) {
   if(argc <= 1) {
     printf("Podano zbyt mala ilosc argumentow");
     } else {
      printf("Podano odpowiednia ilosc argumentow");
     } 
  char nazwa_pliku[] = argv[1];
  char tresc_pliku[2000] = "";
  if(nazwa_pliku == NULL) {
    printf("Nazwa pliku nie zostala okreslona");
  }
  strcat(nazwa_pliku, ".js");
  printf(nazwa_pliku);
  FILE *plik = fopen(nazwa_pliku, "r");
  if(plik == NULL) {
    perror("\nBlad przy otwieraniu pliku");
    return (-1);
  }
  char linia[60] = "";
  char *nowa_linia;
  printf("\nRozpoczeto czytanie z pliku!\n\n");
  while(fgets(linia, 60, plik) != 0) {
    nowa_linia = calloc(60, sizeof(char));
    char dlugosc_linii = strlen(linia);
    char ostatni_znak = linia[strlen(linia) - 1];
    puts(linia);
    if(ostatni_znak == '\n') {
      strncpy(nowa_linia, linia, strlen(linia)-1);
    } else {
      strcpy(nowa_linia, linia);
    }
    strcat(nowa_linia, "\0");
    usunZnakZNapisu(nowa_linia, ' ');
    printf("\n\nObliczona nowa linia=%s\n\n", nowa_linia);
    // ostatni_znak = nowa_linia[strlen(nowa_linia) - 1];
    // if(ostatni_znak != ';') {
    //   strcat(nowa_linia, ";");
    // }
    strcat(tresc_pliku, nowa_linia);
  }
  char* skrocona_tresc = skrocNazwy(tresc_pliku);
  fclose(plik);
  printf("\n\nZakonczono czytanie z pliku!");
  printf("\nSkondensowana tresc pliku - %s", skrocona_tresc);
  plik = fopen("minified.js", "w");
  fprintf(plik, skrocona_tresc);
  fclose(plik);
}
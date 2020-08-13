#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

/** @brief Program sluzacy do skracania kodu programow napisanych w jedyku JS
 *  @author Filip Pietryga
 *  @date sierpień 2020
 */


int main(int argc, char *argv[]) {
  /** @brief główna funkja programu 
 *  @param ilość argumentów
 *  @param argumenty 
 *  @return wartosc pomocnicza, pomagajaca okreslic, czy program wykonal sie dobrze
*/
   if(argc <= 1) {
     printf("Podano zbyt mala ilosc argumentow");
     return 1;
     } else {
      printf("Podano odpowiednia ilosc argumentow\n");
     } 
  char *nazwa_pliku;
  int len = strlen(argv[1]);
  printf("%s", argv[1]);
  printf("\n%s, nazwa_pliku");
  nazwa_pliku = malloc(len);
  printf("\n%d\n", len);
  memset(nazwa_pliku, ' ', len);
  strcpy(nazwa_pliku, argv[1]);
  printf("\n%s", nazwa_pliku);
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
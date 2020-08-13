#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

char* skrocNazwy(char tresc[]) {

  printf("\n\nRozpoczeto funkcje skracania nazw\n\n");

  const int dlugosc = strlen(tresc); 
  char *bufor = calloc(dlugosc+1, sizeof(char));
  int indeks_znaleziska; 
  char nowy_kod[6000]; 

  strcpy(bufor, tresc);

  printf("DLugosc tresci nowego pliku = %d\n", dlugosc);
  printf("\nWypisujemy tresc pliku\n");
  for(int i = 0; i < dlugosc; i++) {
    printf("%c", tresc[i]);
  }

  printf("\n\nRozpoczeto pisanie tresci bufora=");
  for(int i = 0; i < dlugosc; i++) {
    printf("%c", bufor[i]);
  }
    printf("\n");
  int ilosc_slow_kluczowych = 3; 
  int indeks; 
  char obecny_znak = 'a';
  int indeksy[300] = {0}; 
  int obecny_indeks;
  char *slowa_kluczowe[3] = {"var", "const", "function"};
    for(int j = 0; j < ilosc_slow_kluczowych; j++) {
    obecny_indeks = 0;
    char buf[6000] = "";
    for (int i = 0; i < strlen(bufor); i++) {
      strcpy(buf,"");
      memcpy(buf, &bufor[i], strlen(slowa_kluczowe[j]));
      //printf("\nWartosc badanago substringa=%\n", buf);
      //printf("indeks=%d ", i);
      //printf("\nBufor=%s\n", bufor);
        if (strcmp(buf, slowa_kluczowe[j]) == 0) {
          //wykonaj kod dla wykrytego vara, znasz polozenie varu od poczatku
          //printf("Znaleziono szukanego substringa!\n");
          //printf("Nazwa zmiennej=");
          char nazwa[6000] = "";
          i++;
          for(int k = i + strlen(slowa_kluczowe[j]); bufor[k]!=';' && bufor[k]!='=' && bufor[k]!='(' ; k++){
            strncat(nazwa, &bufor[k], 1);
          }
          i--;
          //printf(nazwa);
          //printf("\n");
          //printf("Dlugosc nazwy=%d", strlen(nazwa));
          //printf("\n\nROZPOCZETO PROCES ZAMIANY OBECNIE ZNALEZIONEJ NAZWY (%s) NA KROTSZA, AKA KOLEJNA LITERE ALFABETU", nazwa);
          char test[6000]="";
          int owarty_cudzyslow = 0;
          int odstep = 0;
          for(int z = 0; z < strlen(bufor); z++) {
              memcpy(test, &bufor[z], strlen(nazwa));
              printf("wartosc testowa=%s\n", test);
              for(int o = 0; o < strlen(nazwa); o++) {
                if(odstep == 0) {
                  if(test[o] == '"') {
                    if(owarty_cudzyslow == 0) {
                      owarty_cudzyslow = 1;
                    } else {
                      owarty_cudzyslow = 0;
                    }
                    odstep = strlen(nazwa);
                  }
                }
              }
              if(odstep > 0) {
                odstep--;
              }
              printf("\nWartosc zmiennej odstepu = %d ", odstep);
              printf("\nWartosc zmiennej otwartego cudzyslowia = %d ", owarty_cudzyslow);
              if(strcmp(test, nazwa)==0 && owarty_cudzyslow == 0) {
                  printf("\nZnaleziono nazwe na slocie\n");
                  indeksy[obecny_indeks] = z;
                  obecny_indeks++;
              }
          }
          printf("\n\nIndeksy na ktorych wystepuje obecnie szukane slowo kluczowe to: ");
          for(int a = 0; a < obecny_indeks; a++) {
              printf("%d ", indeksy[a]);
          }
          
          printf("\n\n bufor przed zmianami %s\n\n", bufor);
          for(int a = 0; a < obecny_indeks; a++) {
            for(int b = indeksy[a] + 1; bufor[b] != ';' && bufor[b] != '(' && bufor[b] != ' ' && bufor[b] != '=' && bufor[b] != '"'; b++) {
              bufor[b] = ' ';
            }
            bufor[indeksy[a]] = obecny_znak;
            int koncowy_indeks;
            
            printf("Stan bufora po pierwszej petli %s", bufor);
            for(int b = indeksy[a] + 1;b <= strlen(bufor)-strlen(nazwa)+1; b++) {
              bufor[b] = bufor[b+strlen(nazwa)-1];
              koncowy_indeks = b;
            }
            printf("Stan bufora po drugiej petli %s", bufor);
            // for(int b = strlen(bufor)-strlen(nazwa)+2; b<strlen(bufor); b++) {
            //   bufor[b] = ' ';
            // }
            
            // printf("Stan bufora po trzeciej petli %s", bufor);
            bufor[koncowy_indeks] = '\0';
         }
         for(int l = 0; l < 300; l++) {
            indeksy[l] = 0;
          }
          obecny_znak++;
          obecny_indeks = 0;
          printf("\n\nObecny bufor %s\n\n", bufor);
          printf("\n\nZAKONCZONO PROCES ZAMIANY OBECNIE ZNALEZIONEJ NAZWY (%s) NA KROTSZA, AKA KOLEJNA LITERE ALFABETU", nazwa);
        }
     }

     printf("\n");
  }
  printf("\n\nWartosc bufora po wykonaniu skrocenia: %s\n\n", bufor);
  printf("\n\nZakonczono funkcje skracania nazw\n\n");
  return bufor;
}

void usunZnakZNapisu(char *napis, char znak) {
  /** @brief Funkcja służąca do usuwania wybranych znaków z kodu programu, stworzona ze szczeólnym zamiarem usuwania spacji 
 *  @param napis - ciag znakow, fragment kodu programu ktory ma ulec analizie pod kątem słów kluczowych
 *  @param znak - znak ktory ma zostac usuniety z napisu
 *  @return funkcja nie zwraca zadnych wartosci
*/
  char *zrodlowy_napis, *nowy_napis;
  char ostatnieZnaki[11] = {' ', ' ',' ',' ',' ',' ',' ',' ',' ',' ',' '};
  int obecny_znak = 10;
  int doszedl_do_10 = 0;
  int cudzyslow_otwarty = 0;
  for(zrodlowy_napis = nowy_napis = napis; *zrodlowy_napis != '\0'; zrodlowy_napis++) {
    *nowy_napis = *zrodlowy_napis;
    // printf("\n%c", *nowy_napis);
    if(*zrodlowy_napis == '"') {
      if(cudzyslow_otwarty == 0) {
        cudzyslow_otwarty = 1;
      } else {
        cudzyslow_otwarty = 0;
      }
    }
    if(cudzyslow_otwarty == 1) {
      nowy_napis++;
    }
      else if(ostatnieZnaki[5] == ' ' && ostatnieZnaki[6] == 'c' && ostatnieZnaki[7] == 'o' && ostatnieZnaki[8] == 'n' && ostatnieZnaki[9] == 's' && ostatnieZnaki[10] == 't') {
        nowy_napis++;
      }
      else if (ostatnieZnaki[2] == ' ' && ostatnieZnaki[3] == 'f' && ostatnieZnaki[4] == 'u' && ostatnieZnaki[5] == 'n' && ostatnieZnaki[6] == 'c' && ostatnieZnaki[7] == 't' && ostatnieZnaki[8] == 'i' && ostatnieZnaki[9] == 'o' && ostatnieZnaki[10] == 'n') {
        nowy_napis++;
      }
      else if (ostatnieZnaki[7] == ' ' && ostatnieZnaki[8] == 'v' && ostatnieZnaki[9] == 'a' && ostatnieZnaki[10] == 'r') {
        nowy_napis++;
      }
      else if (ostatnieZnaki[4] == ' ' && ostatnieZnaki[5] == 'd' && ostatnieZnaki[6] == 'e' && ostatnieZnaki[7] == 'l' && ostatnieZnaki[8] == 'e' && ostatnieZnaki[9] == 't' && ostatnieZnaki[10] == 'e') {
        nowy_napis++;
      }
      else if (ostatnieZnaki[6] == ' ' && ostatnieZnaki[7] == 'c' && ostatnieZnaki[8] == 'a' && ostatnieZnaki[9] == 's' && ostatnieZnaki[10] == 'e') {
        nowy_napis++;
      }
      else if (ostatnieZnaki[8] == ' ' && ostatnieZnaki[9] == 'i' && ostatnieZnaki[10] == 'n') {
        nowy_napis++;
      }
      else if (ostatnieZnaki[7] == ' ' && ostatnieZnaki[8] == 'n' && ostatnieZnaki[9] == 'e' && ostatnieZnaki[10] == 'w') {
        nowy_napis++;
      }
      else if (ostatnieZnaki[5] == ' ' && ostatnieZnaki[6] == 'c' && ostatnieZnaki[7] == 'a' && ostatnieZnaki[8] == 't' && ostatnieZnaki[9] == 'c' && ostatnieZnaki[10] == 'h') {
        nowy_napis++;
      }
      else if (ostatnieZnaki[5] == ' ' && ostatnieZnaki[6] == 't' && ostatnieZnaki[7] == 'h' && ostatnieZnaki[8] == 'r' && ostatnieZnaki[9] == 'o' && ostatnieZnaki[10] == 'w') {
        nowy_napis++;
      }
      else if (ostatnieZnaki[4] == ' ' && ostatnieZnaki[5] == 't' && ostatnieZnaki[6] == 'y' && ostatnieZnaki[7] == 'p' && ostatnieZnaki[8] == 'e' && ostatnieZnaki[9] == 'o' && ostatnieZnaki[10] == 'f') {
        nowy_napis++;
      }
      else if (ostatnieZnaki[6] == ' ' && ostatnieZnaki[7] == 't' && ostatnieZnaki[8] == 'h' && ostatnieZnaki[9] == 'i' && ostatnieZnaki[10] == 's') {
        nowy_napis++;
      }
      else if(*nowy_napis != znak) {
        nowy_napis++;
      }
      if (ostatnieZnaki[0] == ' ' && ostatnieZnaki[1] == 'i' && ostatnieZnaki[2] == 'n' && ostatnieZnaki[3] == 's' && ostatnieZnaki[4] == 't' && ostatnieZnaki[5] == 'a' && ostatnieZnaki[6] == 'n' && ostatnieZnaki[7] == 'c' && ostatnieZnaki[8] == 'e' && ostatnieZnaki[9] == 'o' && ostatnieZnaki[10] == 'f') {
        nowy_napis++;
      }
      else if(*(zrodlowy_napis) == ' ' && *(zrodlowy_napis+1) == 'i' && *(zrodlowy_napis+2) == 'n' && *(zrodlowy_napis+3) == 's' && *(zrodlowy_napis+4) == 't' && *(zrodlowy_napis+5) == 'a' && *(zrodlowy_napis+6) == 'n' && *(zrodlowy_napis+7) == 'c'  && *(zrodlowy_napis+8) == 'e' && *(zrodlowy_napis+9) == 'o' && *(zrodlowy_napis+10) == 'f') {
        nowy_napis++;
        printf("Nastepnym wyrazem bedzie instanceof\n");
      }

      for(int i = 0;i < 10;i++) {
          ostatnieZnaki[i] = ostatnieZnaki[i+1];
          //printf("%c", ostatnieZnaki[i+1]);
          obecny_znak = 10;
        }
        printf("\n");
      ostatnieZnaki[obecny_znak] = *zrodlowy_napis;
  }
  *nowy_napis = '\0';
}
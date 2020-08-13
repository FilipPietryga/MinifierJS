/**@file*/

/** Plik naglowkowy pliku minifier.c przechowujacy glowne funkcje potrzebne do dzialania programu
 *  @author Filip Pietryga
 *  @date sierpień 2020
 */

#ifndef MINIFIER_H
#define MINIFIER_H
#include "functions.c"

/** Funkcja sluzaca do usuwania znakow z kodu programu, stworzona ze szczegolnym zamiarem usuwania spacji 
 *  @param napis - ciag znakow, fragment kodu programu ktory ma ulec analizie pod katem slow kluczowych
 *  @param znak - znak ktory ma zostac usuniety z napisu
 *  @return funcja nie zwraca zadnych wartosci
*/
void usunZnakZNapisu(char *napis, char znak);

/** Funkcja sluzaca do zmiany nazw zmiennych na krotsze
  *  @param tresc - lancuch znakow, zawartosc kodu programu ktory ma ulec "skroceniu" poprzez zmiane nazwy jego zmiennych na krotsze
  *  @return lancuch znakow, skrocony kod programu
*/
char* skrocNazwy(char tresc[]);



#endif
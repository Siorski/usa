/* Program mnożący macierze.
   kompilacja z opcja -lrt
   Uruchamianie: ./nazwaprogramu nazwa_pliku_z_macierza_A nazwa_pliku_z_macierza_B 
   Plik z macierza w postaci:
   x y
   a b c
   d e f
   g h i
   gdzie x to ilość wierszy, y to ilość kolumn macierzy, natomiast a,b,c... to kolejne elementy macierzy. 
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MLD 1000000000.0 //10^9

int main(int argc, char *argv[]){
  if(argc!=3){
    printf("******** BŁĄD! ******** \n");
    printf("Uruchamianie: ./nazwaprogramu nazwa_pliku_z_macierza_A nazwa_pliku_z_macierza_B\n");
    exit(0);
  }
  FILE *plik; 
  int i,j,k,ilosc_wierszy_A,ilosc_kolumn_A,ilosc_wierszy_B,ilosc_kolumn_B; 
  struct timespec tp0, tp1;
  double sp;

  clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp0); //pobieramy czas z procesora przed wczytywaniem danych
  /*WCZYTYWANIE MACIERZY A */
  plik=fopen(argv[1],"r"); 
  if(plik==NULL){ 
    printf("Błąd podczas otwierania pliku!\n"); 
    exit(0);
  } 
  fscanf(plik,"%d %d\n",&ilosc_wierszy_A,&ilosc_kolumn_A); 
  int macierzA[ilosc_wierszy_A][ilosc_kolumn_A];
  for(i=0; i<ilosc_wierszy_A; i++){
    for(j=0; j<ilosc_kolumn_A; j++){
      fscanf(plik,"%d ",&macierzA[i][j]);
    } 
  }

  /*WCZYTYWANIE MACIERZY B */
  plik=fopen(argv[2],"r"); 
  if(plik==NULL) { 
    printf("Błąd podczas otwierania pliku!\n"); 
    exit(0);
  } 
  fscanf(plik,"%d %d\n",&ilosc_wierszy_B,&ilosc_kolumn_B); 
  int macierzB[ilosc_wierszy_B][ilosc_kolumn_B];
  for(i=0; i<ilosc_wierszy_B; i++){
    for(j=0; j<ilosc_kolumn_B; j++){
      fscanf(plik,"%d ",&macierzB[i][j]);
    } 
  }  
  fclose(plik);  

  clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp1); //pobieramy czas z procesora po wczytywaniu danych
  sp = (tp1.tv_sec+tp1.tv_nsec/MLD)-(tp0.tv_sec+tp0.tv_nsec/MLD);
  printf("Czas wczytywania danych: %3.10lf\n",sp);          

  /*SPRAWDZANIE CZY MNOŻENIE JEST WYKONALNE */
  if(ilosc_kolumn_A != ilosc_wierszy_B){
    printf("Mnożenie niemożliwe!\n");
    exit(0);
  }

  /*DRUKOWANIE MACIERZY A */
  printf("******** MACIERZ A ********\n");
  for(i=0; i<ilosc_wierszy_A; i++){ 
    for(j=0; j<ilosc_kolumn_A; j++){ 
      printf("%d ",macierzA[i][j]); 
    } 
  printf("\n"); 
  } 

  /*DRUKOWANIE MACIERZY B */
  printf("******** MACIERZ B ********\n");
  for(i=0; i<ilosc_wierszy_B; i++){ 
    for(j=0; j<ilosc_kolumn_B; j++){ 
      printf("%d ",macierzB[i][j]); 
    } 
    printf("\n"); 
  } 

  /*ZEROWANIE MACIERZY WYNIKOWEJ */
  int macierzC[ilosc_wierszy_A][ilosc_kolumn_B];
   for(i=0; i<ilosc_wierszy_A; i++){ 
    for(j=0; j<ilosc_kolumn_B; j++){ 
      macierzC[i][j] = 0; 
    } 
  } 

  clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp0); //pobieramy czas z procesora przed głównymi obliczenami
  /*MNOŻENIE MACIERZY */
  for(i=0; i<ilosc_wierszy_A; i++){
    for(j=0; j<ilosc_kolumn_B; j++){
      for(k=0; k<ilosc_wierszy_B; k++){
        macierzC[i][j] += macierzA[i][k] * macierzB[k][j];
      }
    }
  }
  clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp1); //pobieramy czas z procesora po głównych obliczeniach
  sp = (tp1.tv_sec+tp1.tv_nsec/MLD)-(tp0.tv_sec+tp0.tv_nsec/MLD);
  printf("Czas obliczeń: %3.10lf\n",sp);

  clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp0); //pobieramy czas z procesora przed wypisywaniem wyniku
  /*WYPISYWANIE MACIERZY WYNIKOWEJ*/
  printf("******** MACIERZ WYNIKOWA ********\n");
  for(i=0; i<ilosc_wierszy_A; i++){ 
    for(j=0; j<ilosc_kolumn_B; j++){ 
      printf("%d ",macierzC[i][j]); 
    } 
    printf("\n"); 
  } 
  clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp1); //pobieramy czas z procesora po głównych obliczeniach
  sp = (tp1.tv_sec+tp1.tv_nsec/MLD)-(tp0.tv_sec+tp0.tv_nsec/MLD);
  printf("Czas zapisu danych: %3.10lf\n",sp);
  return 0;
};

//TODO
// malloc dla tablic
// macierz wynikowa dla pliku
// repo 
/* Program mnożący macierze.
   kompilacja z opcja -lrt
   Uruchamianie: ./nazwaprogramu nazwa_pliku_z_macierza_A nazwa_pliku_z_macierza_B nazwa_pliku_wynikowego 
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
  if(argc!=4){
    printf("******** BŁĄD! ******** \n");
    printf("Uruchamianie: ./nazwaprogramu nazwa_pliku_z_macierza_A nazwa_pliku_z_macierza_B nazwa_pliku_wynikowego \n");
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

  /*DYNAMICZNE TWORZENIE MACIERZY A */
  int **macierzA = (int **)malloc(ilosc_wierszy_A * sizeof(int*));
  for (i = 0; i < ilosc_wierszy_A; i++) {
    macierzA[i] = (int *)malloc(ilosc_kolumn_A * sizeof(int));
  }
  
  for(i=0; i<ilosc_wierszy_A; i++){
    for(j=0; j<ilosc_kolumn_A; j++){
      fscanf(plik,"%d ",&macierzA[i][j]);
    } 
  }
  fclose(plik);  

  /*WCZYTYWANIE MACIERZY B */
  plik=fopen(argv[2],"r"); 
  if(plik==NULL) { 
    printf("Błąd podczas otwierania pliku!\n"); 
    exit(0);
  } 
  fscanf(plik,"%d %d\n",&ilosc_wierszy_B,&ilosc_kolumn_B); 

  /*DYNAMICZNE TWORZENIE MACIERZY B */
  int **macierzB = (int **)malloc(ilosc_wierszy_B * sizeof(int*));
  for (i = 0; i < ilosc_wierszy_B; i++) {
    macierzB[i] = (int *)malloc(ilosc_kolumn_B * sizeof(int));
  }

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

  /*DYNAMICZNE TWORZENIE MACIERZY WYNIKOWEJ */
  int **macierzC = (int **)malloc(ilosc_wierszy_A * sizeof(int*));
  for (i = 0; i < ilosc_wierszy_A; i++) {
    macierzC[i] = (int *)malloc(ilosc_kolumn_B * sizeof(int));
  }

  /*ZEROWANIE MACIERZY WYNIKOWEJ */
  for(i=0; i<ilosc_wierszy_A; i++){ 
    for(j=0; j<ilosc_kolumn_B; j++){ 
      macierzC[i][j] = 0; 
    } 
  } 

  clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp0); //pobieramy czas z procesora przed głównymi obliczenami
  /*MNOŻENIE MACIERZY */
  printf("Mnożę macierzę z plików %s oraz %s \n", argv[1], argv[2]);
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
  plik=fopen(argv[3],"w");
  // printf("******** MACIERZ WYNIKOWA ********\n");
  for(i=0; i<ilosc_wierszy_A; i++){ 
    for(j=0; j<ilosc_kolumn_B; j++){ 
      fprintf(plik, "%d ",macierzC[i][j]); 
    } 
    fprintf(plik,"\n"); 
  } 
  fclose(plik);  

  clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp1); //pobieramy czas z procesora po głównych obliczeniach
  sp = (tp1.tv_sec+tp1.tv_nsec/MLD)-(tp0.tv_sec+tp0.tv_nsec/MLD);
  printf("Czas zapisu danych: %3.10lf\n",sp);
  return 0;
};
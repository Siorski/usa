/* Program mnożący macierze przy użyciu OpenMP.
   kompilacja z opcja -fopenmp
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
#include <omp.h>

#define MLD 1000000000.0 //10^9

int main(int argc, char *argv[]){
  double czas_wczyt_start, czas_wczyt_stop, czas_mnoz_start, 
  czas_mnoz_stop, czas_zapis_start, czas_zapis_stop, 
  czas_ogol_start, czas_ogol_stop, czas1, czas2, czas3, czas4;
  
  czas_ogol_start = omp_get_wtime();
  if(argc!=4){
    printf("******** BŁĄD! ******** \n");
    printf("Uruchamianie: ./nazwaprogramu nazwa_pliku_z_macierza_A nazwa_pliku_z_macierza_B nazwa_pliku_wynikowego \n");
    exit(0);
  }
  FILE *plik; 
  int i,j,k,ilosc_wierszy_A,ilosc_kolumn_A,ilosc_wierszy_B,ilosc_kolumn_B; 

  /*WCZYTYWANIE MACIERZY A */
  czas_wczyt_start = omp_get_wtime();
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

  czas_wczyt_stop = omp_get_wtime();
  czas1 = czas_wczyt_stop - czas_wczyt_start;
  printf("Mnożę macierzę z plików %s oraz %s \n", argv[1], argv[2]);
  printf("Czas wczytywania danych: %lf\n",czas1);          


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

  /*MNOŻENIE MACIERZY */
  czas_mnoz_start = omp_get_wtime();
  #pragma omp parallel shared(macierzA, macierzB, macierzC) private(i,j,k)
  {
    #pragma omp for schedule (static)
    for(i=0; i<ilosc_wierszy_A; i++){
      for(j=0; j<ilosc_kolumn_B; j++){
        for(k=0; k<ilosc_wierszy_B; k++){
          macierzC[i][j] += macierzA[i][k] * macierzB[k][j];
        }
      }
    }
  }
  czas_mnoz_stop = omp_get_wtime();
  czas2 = czas_mnoz_stop - czas_mnoz_start;
  printf("Czas obliczeń: %lf\n", czas2);

  /*WYPISYWANIE MACIERZY WYNIKOWEJ*/
  czas_zapis_start = omp_get_wtime();
  plik=fopen(argv[3],"a");
  for(i=0; i<ilosc_wierszy_A; i++){ 
    for(j=0; j<ilosc_kolumn_B; j++){ 
      fprintf(plik, "%d ",macierzC[i][j]); 
    } 
    fprintf(plik,"\n"); 
  } 
  fclose(plik);  

  czas_zapis_stop = omp_get_wtime();
  czas3 = czas_zapis_stop - czas_zapis_start;
  printf("Czas zapisu danych: %lf\n", czas3);

  czas_ogol_stop = omp_get_wtime();
  czas4 = czas_ogol_stop - czas_ogol_start;
  printf("Czas wykonania całego programu: %lf\n", czas4);
  printf("***************************************************\n");
  
  plik=fopen(argv[3],"a");
  fprintf(plik, "\n CZASY DLA OpenMP NA SIGMIE: \n");
  fprintf(plik, "Czas wczytywania danych: %lf\n", czas1);
  fprintf(plik, "Czas obliczeń: %lf\n", czas2);
  fprintf(plik, "Czas zapisu danych: %lf\n", czas3);
  fprintf(plik, "Czas wykonania całego programu: %lf\n", czas4);
  fprintf(plik, "************************************************\n");
  fclose(plik);
  return 0;
};
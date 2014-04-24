/* Program do generowania macierzy.
	 Uruchamianie: ./nazwaprogramu ilosc_wierszy ilosc_kolumn nazwa_pliku_wynikowego
*/
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	if(argc!=4){
		printf("******** BŁĄD! ******** \n");
		printf("Uruchamianie: ./nazwaprogramu ilosc_wierszy ilosc_kolumn nazwa_pliku_wynikowego\n");
		exit(0);
	}
	FILE *plik;
	srand(time(NULL));
	int i,j;
	int ilosc_wierszy = atoi(argv[1]);
	int ilosc_kolumn = atoi(argv[2]);
	int **macierz = (int **)malloc(ilosc_wierszy * sizeof(int*));
  for (i = 0; i < ilosc_wierszy; i++) {
    macierz[i] = (int *)malloc(ilosc_kolumn * sizeof(int));
  }
	plik = fopen(argv[3],"w");
	fprintf(plik, "%d %d\n",ilosc_wierszy,ilosc_kolumn);
	for(i=0; i<ilosc_wierszy; i++){
		for(j=0; j<ilosc_kolumn; j++){
			macierz[i][j] = rand()%100;
		}
	}  
	for(i=0; i<ilosc_wierszy; i++){
		for(j=0; j<ilosc_kolumn; j++){
			fprintf(plik, "%d ", macierz[i][j]);
		}  
		fprintf(plik,"\n");
	}
	fclose(plik);
	return 0;
};

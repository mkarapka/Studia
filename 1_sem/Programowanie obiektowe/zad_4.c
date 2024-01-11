//Mikołaj Karapka
#include<stdio.h>
#include<stdlib.h>

//Zadeklarowanie funkcji 
void tabliczka(float x1, float x2, float y1, float y2, float skok){
    float *liczby = (float*)malloc(sizeof(float)*((int)((x2/skok)+1)));
    int i = 0;

    //stworzenie pętli, która oblicza wyrazy do przemnożenia dla każdej kolumny
    while (x1 <= x2)
    {
        liczby[i] = x1;
        x1 = x1 + skok;
        i++;
    }


    //Użycie funkcji realloc do zmienienia wielkości tablicy
    liczby = (float*)realloc(liczby,i*sizeof(float));
    printf("      ");
    for (int j = 0; j < i; j++)
    {
        printf("%0.2f ", liczby[j]);
    }
    printf("\n");

    //stworzenie pętli, która będzię obliczała mnożniki dla każdego wiersza
    while (y1 <= y2)
    {
        printf("%0.2f: ", y1);
        
        //pętla do obliczania wyrazów po przemnożeniu p-tego wiersza i kolumny
        for (int p = 0; p < i; p++)
        {
            printf("%0.2f " ,liczby[p] * y1);
        }
        printf("\n");
        y1 = y1 + skok;
    }

    //Zwolnienie listy liczby z pamięci
    free(liczby);
}


int main(){

    //Uruchomienie funkcji tabliczka
    tabliczka(0.2,1.3,0.2,3.14,0.3);

    return 0;
}
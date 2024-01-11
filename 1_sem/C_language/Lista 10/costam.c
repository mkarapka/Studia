#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void Horner(int d ,int array[d], int x , char tab_wynik[5]){
   long long wynik = 0;
   int zmienna;
   for (int i = 0; i <= d; i++)
   {
       wynik = wynik*x + array[i];
       if (wynik > 99999)
       {
           wynik = wynik % 100000;
       }
   }
   zmienna = abs((int)wynik);
//    printf("wynik %d\n" , zmienna);
   
    int zmienna = abs((int)wynik);
    for (int i = 4; i >= 0; i--)
    {
        tab_wynik[i] = zmienna % 10 + '0';
        zmienna /= 10;
    }
//    putchar('\n');
}
int main(){
    int n,m = 0;
    char result[100][5];
    if (scanf("%d" , &n) == 1)
    {    
        //pętla po n wierszach
        int d_stopien,x,wspolczynniki[d_stopien+1];
        for (int i = 0; i < n; i++)
        {
            //pobieranie stopnia i zmiennej x wielomianu
            if(scanf("%d %d" , &d_stopien , &x) != 2) return 0;
            for (int j = 0; j < d_stopien+1; j++)
            {
               //pobieranie do tablicy po każdym wielomianie
               if(scanf("%d" , &wspolczynniki[j])!= 1) return 0;
            }
            Horner(d_stopien, wspolczynniki, x, result[m]);
            m++;
        }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            printf("%c" , result[i][j]);
        }
        putchar('\n');
    }
    
    }
    return 0;
}

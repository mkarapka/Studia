#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//schemat hornera
void Horner(int d ,int array[d], int x, char tab[5]){
    long long wynik = 0;
    x = abs(x);
    for (int i = 0; i <= d; i++)
    {
        wynik = wynik*x + array[i];
        if (wynik > 99999)
        {
            wynik = wynik % 100000;
        }
    }
    for (int i = 4; i >= 0; i--)
    {
        if (wynik == 0)
        {
            tab[i] = '0';
        }
        else{
            tab[i] = wynik % 10 + '0';
        }
        wynik /= 10;
    }
}
int main(){
    //pobieranie n
    int n,m = 0;
    char tab_wynik[5], result[100][5] ;
    if (scanf("%d" , &n) == 1)
    {
        //pętla po n wierszach
        int d_stopien,x,wspolczynniki[65536];
        for (int i = 0; i < n; i++)
        {
            //pobieranie stopnia i zmiennej x wielomianu 
            if(scanf("%d %d" , &d_stopien , &x) != 2) return 0;
            for (int j = 0; j < d_stopien+1; j++)
            {
                //pobieranie do tablicy po każdym wielomianie
                if(scanf("%d" , &wspolczynniki[j])!= 1) return 0;
            }
            Horner(d_stopien, wspolczynniki, x, tab_wynik);
            for (int i = 0; i < 5; i++)
            {
                result[m][i] = tab_wynik[i];
            }
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
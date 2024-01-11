#include<stdio.h>
#include<stdbool.h>
void mapa_skarbow(char tab[]){
    char fragment;
    int j=0;
    while ((fragment = getchar()) != '\n')
    {
        tab[j] = fragment;
        j++;
    }
}
void lista_krokow(char tab[] , int zmienna){
    char fragment;
    int j=0;
    while (j<zmienna)
    {
        if ((fragment=getchar()) != '\n')
        {
            tab[j] = fragment;
            j++;
        }
    }
}
int obrot(int kierunek,char znak){
    if(znak == 'L'){
        if (kierunek == 0)
        {
            kierunek = 3;
        }
        else{
            kierunek = kierunek - 1;
        }
    }
    else if (znak == 'R')
    {
        kierunek = (kierunek+1)%4;
    }
    return kierunek;
}
int main(){
    int lenght,wide;
    int liczba;
    if(scanf("%d %d", &wide , &lenght )!=0){
        char mapa[lenght][wide];
        getchar();
        for (int i = 0; i < lenght; i++)
        {
            mapa_skarbow(mapa[i]);
        }
        if(scanf("%d" , &liczba)!=0){
            char instrukcja[liczba],znak;
            getchar();
            lista_krokow(instrukcja , liczba);
            int wspolrzedne[4][2] = {{-1,0},{0,1},{1,0},{0,-1}};
            int wspol_wynik[lenght][wide];
            int pion,poziom;
            for (int y = 0; y < lenght; y++)
            {
                for (int x = 0; x < wide; x++)
                {
                    wspol_wynik[y][x] = mapa[y][x];
                    if (mapa[y][x] == '.')
                    {
                        for (int zmienna = 0; zmienna < 4; zmienna++)
                        {
                            int ruch_x = x, ruch_y = y;
                            int kierunek = zmienna;
                            bool blad = false;
                            for (int i = 0; i < liczba; i++)
                            {
                                znak = instrukcja[i];
                                if (znak == 'L' || znak == 'R')
                                {
                                    kierunek = obrot(kierunek, znak);
                                }
                                else if (znak == 'F')
                                {
                                    pion = wspolrzedne[kierunek][0];
                                    poziom = wspolrzedne[kierunek][1];
                                    while (mapa[ruch_y][ruch_x] == '.')
                                    {
                                        ruch_x = ruch_x - poziom;
                                        ruch_y = ruch_y - pion;
                                        if (ruch_y >= lenght || ruch_y < 0)
                                        {
                                            break;
                                        }
                                        if (ruch_x >= wide || ruch_x < 0)
                                        {
                                            break;
                                        }
                                    }
                                    ruch_x = ruch_x + poziom;
                                    ruch_y = ruch_y + pion;
                                }
                                else if (znak == 'S')
                                {
                                    pion = wspolrzedne[kierunek][0];
                                    poziom = wspolrzedne[kierunek][1];
                                    ruch_x = ruch_x - poziom;
                                    ruch_y = ruch_y - pion;
                                    if (ruch_x < wide && ruch_x >= 0 && ruch_y < lenght && ruch_y >= 0)
                                    {
                                        if (mapa[ruch_y][ruch_x] != '.')
                                        {
                                            blad = true;
                                            break;
                                        }
                                    }
                                    else{
                                        blad = true;
                                        break;
                                    }
                                }
                            }
                            if (blad == false)
                            {
                                wspol_wynik[ruch_y][ruch_x] = 'X';
                            }
                        }  
                    }
                }    
            }
            for (int y = 0; y < lenght; y++)
            {
                for (int x = 0; x < wide; x++)
                {
                    printf("%c" , wspol_wynik[y][x]);
                }
                printf("\n");
            }
        }
    }
    return 0;
}
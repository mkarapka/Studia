#include<stdio.h>
#include<stdbool.h>
void mapa_skarbow(char tab[]){
    char fragment;
    int j=0;
    while ((fragment = getchar()) != '\n')
    {
        // printf("%d%c " ,j , fragment);
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
            // printf("%d%c " ,j , fragment);
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
    //pobieranie obrazu mapy
    int lenght,wide;
    int liczba;
    scanf("%d %d", &wide , &lenght );
    char mapa[lenght][wide];
    getchar();
    for (int i = 0; i < lenght; i++)
    {
        mapa_skarbow(mapa[i]);
    }
    //Pobieranie instrukcji
    scanf("%d" , &liczba);
    char instrukcja[liczba],znak;
    getchar();
    lista_krokow(instrukcja , liczba);
    //wykonywanie kroków
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
                    // printf("p:%d ", kierunek);
                    // printf("%d] " , kierunek);
                    // printf("(%d,%d) " , ruch_x , ruch_y);
                    for (int i = 0; i < liczba; i++)
                    {
                        znak = instrukcja[i];
                        // printf("%c" , znak);
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
                                // printf("kier(%d)%d,%d " ,kierunek, ruch_x , ruch_y);
                                ruch_x = ruch_x + poziom;
                                ruch_y = ruch_y + pion;
                                if (ruch_y >= lenght || ruch_y < 0)
                                {
                                    break;
                                }
                                if (ruch_x >= wide || ruch_x < 0)
                                {
                                    break;
                                }
                            }
                            ruch_x = ruch_x - poziom;
                            ruch_y = ruch_y - pion;
                            // printf("[%d%d]\n" , ruch_x ,ruch_y);
                        }
                        else if (znak == 'S')
                        {
                            pion = wspolrzedne[kierunek][0];
                            poziom = wspolrzedne[kierunek][1];
                            ruch_x = ruch_x + poziom;
                            ruch_y = ruch_y + pion;
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
                        // printf("%d " , kierunek);
                        // printf("[%d](%d,%d) ",kierunek , ruch_x , ruch_y);
                    }
                    // putchar('\n');
                    if (blad == false)
                    {
                        wspol_wynik[ruch_y][ruch_x] = 'X';
                    }
                }  
            }
        }    
    }
    // printf("\n");
    for (int y = 0; y < lenght; y++)
    {
        for (int x = 0; x < wide; x++)
        {
            printf("%c" , wspol_wynik[y][x]);
        }
        printf("\n");
    }
    

    // printf("wynik\n");
    // for (int j = 0; j < lenght; j++)
    // {
    //     for (int i = 0; i < wide; i++)
    //     {
    //         printf("%c" , mapa[j][i]);
    //     }
    //     printf("\n");
    // }
    // for (int i = 0; i < liczba; i++)
    // {
    //     printf("%c" , instrukcja[i]);
    // }
    return 0;
}
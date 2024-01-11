//Mikołaj Karapka - atraktor
#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>
float mult_a(float zespolona[]){
    float real;
    real = (zespolona[0] * zespolona[0]) - (zespolona[1]*zespolona[1]);
    return real;
}
float mult_b(float zespolona[]){
    float imaginary;
    imaginary = 2 * (zespolona[0] * zespolona[1]);
    return imaginary;
}
int main(int argc, char* argv[])
{
    bool mniejsze = true;
    float zespolona[2];
    int length,wide;
    if(argc < 3){
        wide = 40;
        length = 25;
    }
    if (argc >= 3)
    {
        wide = atoi(argv[1]);
        length = atoi(argv[2]);
    }
    if (argc == 5)
    {
        zespolona[0] = atof(argv[3]);
        zespolona[1] = atof(argv[4]);
    }
    else{
        zespolona[0] = 0.2;
        zespolona[1] = 0.75;
    }
    float punkt_y = 1,podzial_y ;
    podzial_y = 2/((float)length);
    for (int i = 0; i < length+1; i++)
    {
        float punkt_x = 1,podzial_x;
        podzial_x = 2/((float)wide);
        for (int j = 0; j < wide+1; j++)
        {
            float zmienna[2];
            zmienna[0] = punkt_x;
            zmienna[1] = punkt_y;
            for (int z = 0; z < 200; z++)
            {
                float wynik[2];
                wynik[0] = zmienna[0];
                wynik[1] = zmienna[1];
                zmienna[0] = mult_a(zmienna);
                zmienna[1] = mult_b(wynik);
                zmienna[0] = zmienna[0] - zespolona[0];
                zmienna[1] = zmienna[1] - zespolona[1];
                if ((zmienna[0]* zmienna[0]) + (zmienna[1]*zmienna[1]) >= 4)
                {
                    mniejsze = false;
                    break;
                }
            }
        
            if (mniejsze == true)
                {
                    printf("O");
                }
            else{
                printf(" ");
            }
            mniejsze = true;
            punkt_x = punkt_x - podzial_x;
        }
        putchar('\n');
        punkt_y = punkt_y - podzial_y;
    }
    return 0;
}
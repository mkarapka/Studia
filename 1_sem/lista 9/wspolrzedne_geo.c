// Mikołaj Karapka - wspołrzędne geograficzne 
#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include<math.h>
#define M_PI 3.14159265358979323846
double wspol_geo(char array[]){
    int i = 0 ;
    float zmienna = 10;
    double liczba = 0, cos = 0;
    while (array[i] != '"')
    {
        i++;
    }
    i++;
    while (array[i] != '.')
    {
        liczba = liczba * 10 + (float)(array[i] - '0');
        i++;
    }
    i++;
    while (array[i] != '"')
    {
        cos = ((double)(int)(array[i] - '0'))/zmienna;
        liczba = liczba + cos;
        i++;
        zmienna = zmienna * 10;
    }
    return liczba;
}
int main(int argc , char* argv[]){
    if(argc == 2){
    char linia[100];
    FILE *fp;
    fp = fopen(argv[1],"r");
    if(fp == NULL){
        printf("bład");
        return 1;
    }
    char slowo[] = "<trkpt";
    int suma = 0;
    double lat_2=0,lat_1=0,dlat=0,lon_2=0,lon_1=0,dlon=0 , a , b , R = 6371 , wynik = 0;

    while (fgets(linia,100,fp)!= NULL)
    {
        if (strstr(linia , slowo))
        {
            char* wide = strstr(linia,"lat=");
            lat_2 = wspol_geo(wide);
            char* lenght = strstr(linia,"lon=");
            lon_2 = wspol_geo(lenght);
            lat_2 = lat_2 * (M_PI / 180);
            lon_2 = lon_2 * (M_PI / 180);
            suma++;
            if (suma >= 2)
            {
                dlat = lat_2 - lat_1;
                dlon = lon_2 - lon_1;
                a = pow(sin(dlat/2),2) + cos(lat_1) * cos(lat_2) * pow(sin(dlon/2),2);
                b = 2 * asin(sqrt(a));
                wynik = wynik + b * R;
            }
                lat_1 = lat_2;
                lon_1 = lon_2;
        }
    }
    printf("%.3lfkm " , wynik);
    fclose(fp);
    }
    return 0;
}  
// Mikołaj Karapka - rozbudowany kalkulator biegacza
#include<stdio.h>
#include <stdbool.h>
void rek(int wynik, int dziel){
    int zm;
    while (dziel >= 1)
    {
        zm = wynik / dziel;
        if(dziel != 1){
            if(zm != 0){
                printf("%d:" , zm);
            }
        }
        else{
            printf("%d" , zm);
        }
        wynik = wynik % dziel;
        dziel = dziel/60;
    }
}
int liczba(int cyfra){
    int liczba = cyfra , time, wynik = 0;
    while (time != ' ' && time != '\n' && time != ',' && time != ']')
    {
        time = getchar();
        if (time == ':')
        {
            wynik = (wynik+liczba) * 60;
            liczba = 0;
        }
        else if (time >= '0' && time <= '9')
        {
            liczba = liczba *10 + (time - '0');
        }
    }
    wynik = wynik + liczba;
    return wynik;
}
int operacja(char znak, int liczba_1 , int liczba_2){
    int wynik;
    if(znak == '+'){
        wynik = liczba_1 + liczba_2;
    }
    if(znak == '-'){
        wynik = liczba_1 - liczba_2;
    }
    if(znak == '*'){
        wynik = liczba_1 * liczba_2;
    }
    if(znak == '/'){
        wynik = liczba_1 / liczba_2;
    }
    return wynik;
}
int main(){
    int time , liczba_1, wynik=0 , cos, wejscie = 0;
    int przedzial[2] , przedzial_wynik[2];
    przedzial_wynik[0] = 0;
    przedzial_wynik[1] = 0;
    bool wyst_znak = false, wyst_przedzial = false , blad = false;
    char znak;
    while (cos != EOF)
    {
        cos = getchar();
        if(wejscie == 0){
            time = ' ';
        }
        blad = false;
        while (time != '\n')
        {
            if(wejscie == 0){
                time = cos;
            }
            else{
                time = getchar();
            }
            if(time == '['){
                time = getchar();
                int cyfra = time - '0';
                przedzial[0] = liczba(cyfra);
                time = getchar();
                cyfra = time - '0';
                przedzial[1] = liczba(cyfra);
                wyst_przedzial = true;
                if(wyst_znak == true && wyst_przedzial == true){
                    przedzial_wynik[0] = operacja(znak,przedzial[0],przedzial_wynik[0]);
                    przedzial_wynik[1] = operacja(znak,przedzial[1],przedzial_wynik[1]);
                    wyst_znak = false;
                }
                else{
                    przedzial_wynik[0] = przedzial[0];
                    przedzial_wynik[1] = przedzial[1];
                }
                if(przedzial_wynik[0] > przedzial_wynik[1]){
                    wyst_przedzial = false;
                    printf("błąd: zły przedział\n");
                    blad = true;
                    break;
                }
            }
            if(time >= '*' && time <= '/'){
                znak = time;
                wyst_znak = true;  
            }
            if(time >= '0' && time <= '9'){
                int zmienna = time - '0';
                liczba_1 = liczba(zmienna);
                // printf("%d" , liczba_1);
                if(wyst_znak == true){
                    // printf("%d\n" , liczba_1);
                    if(wyst_przedzial == true){
                        // printf("peW%d" , przedzial_wynik[0]);
                        przedzial_wynik[0] = operacja(znak,liczba_1,przedzial_wynik[0]);
                        przedzial_wynik[1] = operacja(znak,liczba_1,przedzial_wynik[1]);
                        
                    }
                    else{
                        wynik = operacja(znak,wynik,liczba_1);
                    }
                    wyst_znak = false;
                }
                else{
                    wynik = liczba_1;
                }
            }
            wejscie = 1;
        }
        if(wyst_przedzial == true){
            printf("[");
            rek(przedzial_wynik[0], 3600);
            printf(",");
            rek(przedzial_wynik[1],3600);
            printf("]");
        }
        else if(blad == false){
            rek(wynik,3600);
            putchar('\n');
        }
            przedzial_wynik[0] = 0;
            przedzial_wynik[1] = 0;
            wynik = 0;
            wejscie = 0;
        }
          
    return 0;
}
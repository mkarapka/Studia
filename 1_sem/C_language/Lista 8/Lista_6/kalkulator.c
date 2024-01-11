// Mikołaj Karapka - kalkulator biegacza
#include<stdio.h>
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
            printf("%d\n" , zm);
        }
        wynik = wynik % dziel;
        dziel = dziel/60;
    }
    
}
int liczba(int cyfra){
    int liczba = cyfra , time, wynik = 0;
    while (time != ' ' && time != '\n')
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
int main(){
    int time , liczba_1, liczba_2;
    int wynik;
    char znak;
    while (time != EOF)
    {
        time = getchar();
        liczba_1 = liczba(time-'0');
        znak = getchar();
        time = getchar();
        time = getchar();
        liczba_2 = liczba(time - '0');
        if(liczba_1 == 0 || liczba_2 == 0){
            break;
        }
        if(znak == '+')
        {
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
        rek(wynik,3600);
    }  
    return 0;
}
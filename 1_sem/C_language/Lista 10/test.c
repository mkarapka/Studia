#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int Horner(int array[4] , int d , int x){
    int wynik = 0;
    for (int i = 0; i <= d; i++)
    {
        wynik = wynik*x  + array[i];
    }
    return wynik;
}
int main(){
    char napis[10];
    scanf("%s" , &napis);
    for (int i = 0; i < 10; i++)
    {
        printf("%c" , napis[i]);
    }
    return 0;
}
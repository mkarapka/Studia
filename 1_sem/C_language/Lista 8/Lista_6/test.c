#include<stdio.h>

int main(){
    int time;
    time = getchar();
    if(time == '2'){
        int liczba;
        liczba = time-'0';
        printf("%d" , liczba);
    }
    return 0;
}
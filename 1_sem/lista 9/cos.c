#include<stdio.h>
int main(){
    int liczba;
    scanf("%d" , &liczba);
    char tab[liczba] , cos[4095];
    getchar();
    int zmienna = liczba /4095,p = 0;
    while (p < zmienna)
    {
        fgets(cos,4095,stdin);
        for (int i = 0; i < 4095; i++)
        {
            if (cos[i] != '\n')
            {
                tab[p+i]
            }
            
        }
        
        p++;
    }
    for (int z = 0; z < liczba; z++)
    {
        printf("%c" , tab[z]);
    }
    return 0;
}
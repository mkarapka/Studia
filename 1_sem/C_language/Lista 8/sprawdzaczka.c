#include<stdio.h>
#include<stdbool.h>
int main(){
    int n,k;
    scanf("%d" , &n);
    scanf("%d" , &k);
    char tab[n][k],napis;
    getchar();
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < k; j++)
        {
            napis = getchar();
            tab[i][j] = napis;
        }
        getchar();
    }
    int maxi,suma,index_maxi=0;
    char zmienna;
    for (int i = 0; i < n; i++)
    {
        suma = 0;
        for (int j = 0; j < k; j++)
        {
            bool unique = true;
            zmienna = tab[i][j];
            for(int z = 0; z < n; z++){
                if(z != i){
                    if(zmienna == tab[z][j]){
                        unique = false;
                    }
                }
           }
           if(unique == true){
                suma++;
           } 
        }
        if(suma > maxi){
            maxi = suma;
            index_maxi = i;
        } 
    }
    // printf("to jest wynik: ");
    for (int j = 0; j < k; j++)
    {
        printf("%c" , tab[index_maxi][j]);
    }
    printf("\n%d" , maxi);
    // for (int i = 0; i < n; i++)
    // {
    //     for (int j = 0; j < k; j++)
    //     {  
    //         printf("%c " , tab[i][j]);
    //     }
    //     putchar('\n');
    // }
    return 0;
}
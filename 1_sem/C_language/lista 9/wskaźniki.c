#include<stdio.h>
void costam(char array[]){
    int fragment,i=0;
    while((fragment = getchar())!='\n'){
        array[i] = fragment;
        i++;
    }
}
int main(){
    // int cos = 4;
    // int *px = &cos;
    // printf("Adres cos (&cos)%p\n" , &cos);
    // printf("Adres przy użyciu wskaźnika (px)%p\n" , px);
    // printf("Wartość wskaźnika (*px)%d\n" , *px);
    char tab[3];
    costam(tab);
    for (int i = 0; i < 3; i++)
    {
        printf("%c" , tab[i]);
    }
    
    
    return 0;
}
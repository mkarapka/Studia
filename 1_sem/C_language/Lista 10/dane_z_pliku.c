#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct Ptlist{
    int x;
    float lat,lon;
    char nazwa[47];
    struct Ptlist* end;
    };
typedef struct Ptlist Ptlist_t;
struct dane{
    int x;
    float lat,lon;
    char nazwa[47];
};
typedef struct dane dane_t;
void *create_new_node(dane_t wiersz){
    Ptlist_t *result = malloc(sizeof(Ptlist_t));
    result->x = wiersz.x;
    result->lat = wiersz.lat;
    result->lon = wiersz.lon;
    for (int i = 0; i < 47; i++)
    {
        result->nazwa[i] = wiersz.nazwa[i];
    }
    
    result->end = NULL;
    return result;
}
// void remove_malloc(Ptlist_t *head){
//     Ptlist_t *tmp;
//     while (head != NULL)
//     {
//         tmp = head;
//         head->end = head;
//     }
// }
void printlist(Ptlist_t *head){
    Ptlist_t *tmp = head;
    while (tmp != NULL)
    {
        printf("%d %f %f %s\n" , tmp->x , tmp->lat , tmp->lon , tmp->nazwa);
        tmp = tmp->end;
    }
}
void info_wiersz(char wiersz[100]){
    int x = 0,suma , j = 0;
    float lat,lon;
    char zmienna[5];
    char nazwa[47];
    while (wiersz[j] != ' ')
    {
        x = x * 10 + (int)wiersz[j]-'0';
        j++;
    }
    j++;
    int z;
    for (int i = 0; i < 2; i++)
    {
        z = 0;
        while (wiersz[j] != ' ')
        {
            zmienna[z] = wiersz[j];
            // printf("%c" ,zmienna[z]);
            j++;
            z++; 
        }
        if (suma == 0)
        {
            printf("%s" , zmienna);
            lat = atof(zmienna);
            
        }
        else{
            lon = atof(zmienna);
        }
        suma++;
        j++;
        
    }
    // printf("%d %.2f %.2f" , x , lat  , lon);
    
}
int main(){
    // if (argc >= 2)
    // {
        char linia[100];
        FILE *fp;
        fp = fopen("Dane_geograficzne" , "r");
        if (fp == NULL)
        {
            printf("bład");
            return 1;
        }
        // if (argc == 3)
        // {
                // char place = argv[2];
        // }
        int suma = 0;
        while (fgets(linia,100,fp) != NULL)
        {
            info_wiersz(linia);
            putchar('\n');
            if(suma == 5) break;
            suma++;
        }
        // printf("%c" , linia[1]);
        fclose(fp);
    // }
    
    return 0;
}
//Mikołaj Karapka
#include<stdio.h>
#include<stdlib.h>

//Zdefiniowanie struktury Tablica
typedef struct Tablica {
    int index;
    float val;
    struct Tablica* left;
    struct Tablica* right;
} Tablica;

//Zadeklarowanie funkcji do tworzenia struktury typu tablica 
Tablica* nowa_tablica() {
    Tablica* t = malloc(sizeof(Tablica));
    t->index = 0;
    t->val = 0;
    t->left = NULL;
    t->right = NULL;
    return t;
}

//Zadeklarowanie funkcji do tworzenia nowej gałęźi 
Tablica* create_new_note(float value, int index, Tablica* left, Tablica* right){
    Tablica* result = malloc(sizeof(Tablica));
    result->val = value;
    result->index = index;
    result->left = left;
    result->right = right;
    return result;
}

//Zadeklarowanie funkcji do dodawania wartości na konkretny indeks 
void dodaj(Tablica* t, int id, float liczba) {
    int skok, ind = 0;

    //sprawdzenie czy indeks jest ujemny
    if (id < 0) {
        skok = -1;
    }
    else {
        skok = 1;
    }
    Tablica* tmp = t, *tmp_skok;

    //Pętla do przechodzenia po indeksach
    while (ind != id) {
        ind = ind + skok;

        //skakanie w prawo lub w lewo, zależnie czy indeks jest ujemny lub nie 
        if (id < 0) {
            tmp_skok = tmp->left;


            //sprawdzenie czy kolejny element jest NULL
            if (tmp_skok == NULL) {
                
                //stworzenie nowej gałęzi
                tmp_skok = create_new_note(0, ind, NULL, tmp);
                tmp->left = tmp_skok;
            }
            tmp = tmp->left;
        }
        else {
            tmp_skok = tmp->right;


            //sprawdzenie czy kolejny element jest NULL
            if (tmp_skok == NULL) {


                //stworzenie nowej gałęzi
                tmp_skok = create_new_note(0, ind, tmp, NULL);
                tmp->right = tmp_skok;
            }
            tmp = tmp->right;
        }
    }

    //przypisanie wartości do szukanego indeksu
    tmp->val = liczba;
}

//zadeklarowanie funkcji do wypisywania elementów listy
void show(Tablica* t) {
    Tablica* tmp = t;

    //przejście do najbardziej wysuniętego indeksu na lewo
    while (tmp->left != NULL) {
        tmp = tmp->left;
    }

    //wypisanie wszystkich indeksów od najmniejszego do najwięszego
    while (tmp != NULL) {
        printf("%0.2f ", tmp->val);
        tmp = tmp->right;
    }
}


//zedeklarowanie funkcji do zwalniania pamięci z utworzonej listy
void tab_free(Tablica *t){
    Tablica* tmp = t , *tmp_2;
    while (tmp->left != NULL) {
        tmp = tmp->left;
    }
    while (tmp != NULL) {
        tmp_2 = tmp;
        tmp = tmp->right;
        free(tmp_2);
    }
}


int main() {
    Tablica* t;

    //wywołanie wyżej zadeklarowanych funkcji 
    t = nowa_tablica();

    dodaj(t, -1, 6.0);
    dodaj(t, 4, 5.0);
    dodaj(t,2,1.0);

    show(t);

    tab_free(t);
    return 0;
}
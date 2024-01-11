#include<stdio.h>
#include<stdlib.h>
typedef struct Tablica {
    int index;
    float val;
    struct Tablica* left;
    struct Tablica* right;
} Tablica;


Tablica* nowa_tablica() {
    Tablica* t = malloc(sizeof(Tablica));
    t->index = 0;
    t->val = 0;
    t->left = NULL;
    t->right = NULL;
    return t;
}


Tablica* create_new_note(float value, int index, Tablica* left, Tablica* right) {
    Tablica* result = malloc(sizeof(Tablica));
    result->val = value;
    result->index = index;
    result->left = left;
    result->right = right;
    return result;
}


void dodaj(Tablica* t, int id, float liczba) {
    int skok;
    if (id < 0) {
        skok = -1;
    }
    else {
        skok = 1;
    }
    Tablica* tmp = t, * tmp_skok;
    if (skok < 0) {
        while (id != tmp->index) {
            tmp = tmp->left;
        }
        if (tmp->left == NULL) {
            tmp_skok = create_new_note(0, id, NULL, tmp);
            tmp->left = tmp_skok;
        }
        else {
            tmp_skok = tmp->left;
        }
    }
    else if (skok > 0) {
        while (id != tmp->index) {
            tmp = tmp->right;
        }
        if (tmp->right == NULL) {
            tmp_skok = create_new_note(0, id, tmp, NULL);
            tmp->right = tmp_skok;
        }
        else {
            tmp_skok = tmp->right;
        }
        tmp = tmp_skok->left;
    }
    tmp->val = liczba;
}


void show(Tablica* t) {
    Tablica* tmp = t;
    while (tmp->left != NULL) {
        tmp = tmp->left;
    }
    while (tmp != NULL) {
        printf("%f ", tmp->val);
        tmp = tmp->right;
    }
}


int main() {
    Tablica* t;
    t = nowa_tablica();
    dodaj(t, -1, 6.0);
    dodaj(t, 2, 5.0);
    show(t);
    return 0;
}



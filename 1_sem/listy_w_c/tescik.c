#include<stdio.h>
#include<stdlib.h>
struct elem
{
    int val;
    struct elem *next;
};
typedef struct elem elem_t;
elem_t *costam(elem_t *head , int data){
    elem_t *new_el = malloc(sizeof(elem_t));
    new_el->val = data;
    new_el->next = head;
    return new_el;
}
void printlist(elem_t *head){
    elem_t *tmp = head;
    while (tmp != NULL)
    {
        printf("%d " , tmp->val);
        tmp = tmp->next;
    }
}
int main(){
    elem_t *head = NULL;
    for (int i = 0; i < 4; i++)
    {
        head = costam(head , i);
    }
    printlist(head);
    return 0;
}
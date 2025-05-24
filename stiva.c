#include <stdio.h>
#include <stdlib.h>
#include "stiva.h"

void afis_stiva(FILE* out, stiva* top){
    int generatie = 1;

    while(top != NULL){
        fprintf(out, "%d ", generatie);
        afis_lista(out, top->head);
        top = top->urm;
        generatie++;
    }    
}

void impinge(stiva** top, lista* head){
    stiva* nou = (stiva*)malloc(sizeof(stiva));

    nou->head = head;
    nou->urm = *top;
    *top = nou;    
}

void eliberare_stiva(stiva** top){
    stiva* temp = NULL;

    while((*top) != NULL){
        temp = *top;
        *top = (*top)->urm;
        eliberare_lista(&(temp->head));
        free(temp);
    }
}

lista* elem_scos(stiva** top){
    if(*top == NULL) return NULL;

    stiva* temp = *top;
    lista* head = temp->head;

    *top = (*top)->urm;
    free(temp);

    return head;    
}
#include <stdio.h>
#include <stdlib.h>
#include "arbore_binar.h"

BN* creare_arbore(int nivel){
    if(nivel == -1) return NULL;

    BN* nou = (BN*)malloc(sizeof(BN));

    nou->head = NULL;
    nou->st = creare_arbore(nivel-1);
    nou->dr = creare_arbore(nivel-1);

    return nou;    
}

void afis_preordine(FILE* out, BN* root, celula** grila, int lin, int col, int flag_radacina){
    celula** grila_st = NULL, **grila_dr = NULL;

    if((root == NULL) && (grila != NULL)){
        eliberare_grila(grila, lin); 
        return;
    }

    if(flag_radacina){
        grila = convertto_grila(root->head, lin, col);
        afis_grila(out, grila, lin, col);
    } else {
        lista* head = root->head;

        while(head != NULL){
            grila[(head->y) + 1][(head->x) + 1].vie = !grila[(head->y) + 1][(head->x) + 1].vie;
            head = head->urm;
        }

        afis_grila(out, grila, lin, col);
    }

    grila_st = copie(grila, lin, col);
    grila_dr = copie(grila, lin, col);

    eliberare_grila(grila, lin); 

    afis_preordine(out, root->st, grila_st, lin, col, 0);
    afis_preordine(out, root->dr, grila_dr, lin, col, 0);    
}

void umplere_arbore(BN* root, celula** grila, int lin, int col, int flag_st, int flag_radacina){
    struct celula** grila_st = NULL, **grila_dr = NULL;

    if(root == NULL){
        eliberare_grila(grila, lin); 
        return;
    }

    if(flag_radacina) root->head = convertto_lista(grila, lin, col);
    else {
        num_vecini(grila, lin, col);

        if(flag_st){
            root->head = schimbariB(grila, lin, col);
            modifB(grila, lin, col);
        } else {
            root->head = schimbariBD(grila, lin, col);
            modifBD(grila, lin, col);
        }

        reset_vecini(grila, lin, col);
    }

    grila_st = copie(grila, lin, col);
    grila_dr = copie(grila, lin, col);

    eliberare_grila(grila, lin);

    umplere_arbore(root->st, grila_st, lin, col, 1, 0);
    umplere_arbore(root->dr, grila_dr, lin, col, 0, 0);
}

void eliberare_arbore(BN** root){
    if((*root) == NULL) return;

    BN* st = (*root)->st, *dr = (*root)->dr;

    eliberare_lista(&((*root)->head));
    free(*root);
    eliberare_arbore(&st);
    eliberare_arbore(&dr);    
}
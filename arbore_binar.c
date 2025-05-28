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

void hamilton_preordine(FILE* out, BN* root, celula** grila, int lin, int col, int flag_radacina){
    int nr_cel, len, len_max = 0;
    celula** grila_st = NULL, **grila_dr = NULL, **vizitat = NULL, **cc = NULL;
    lista* lant = NULL, *lant_max = NULL;

    if((root == NULL) && (grila != NULL)){
        eliberare_grila(grila, lin); 
        return;
    }

    if(flag_radacina) grila = convertto_grila(root->head, lin, col);
    else {
        lista* head = root->head;

        while(head != NULL){
            grila[(head->y) + 1][(head->x) + 1].vie = !grila[(head->y) + 1][(head->x) + 1].vie;
            head = head->urm;
        }
    }

    vizitat = (celula**)malloc(lin*sizeof(celula*));
    for(int i = 0; i < lin; i++) vizitat[i] = (celula*)calloc(col, sizeof(celula));

    cc = copie(vizitat, lin, col);

    for(int i = 1; i < lin-1; i++)
        for(int j = 1; j < col-1; j++)
            if(grila[i][j].vie && !vizitat[i][j].vie){
                for(int k = 0; k < lin; k++)
                    for(int l = 0; l < col; l++) cc[k][l].vie = 0;

                comp_conexa(grila, cc, j-1, i-1);
                nr_cel = nr_celule(cc, lin, col);
                lant = (lista*)calloc(nr_cel, sizeof(lista));
                len = hamilton(lant, grila, j-1, i-1, nr_cel, 0);

                if(len){
                    for(int k = 0; k < len; k++) vizitat[lant[k].y + 1][lant[k].x + 1].vie = 1;
                    if(len > len_max){
                        len_max = len;
                        if(lant_max != NULL) free(lant_max);
                        lant_max = lant;
                    } else if(len == len_max){
                        if(cmp(lant, lant_max, len)){
                            free(lant_max);
                            lant_max = lant;
                        } else free(lant);
                    } else free(lant);
                } else free(lant);
            }

    fprintf(out, "%d\n", len_max-1);
    for(int i = 0; i < len_max; i++){
        if(i != len_max-1) fprintf(out, "(%d,%d) ", lant_max[i].y, lant_max[i].x);
        else fprintf(out, "(%d,%d)", lant_max[i].y, lant_max[i].x);
    }
    if(len_max) fprintf(out, "\n");

    if(lant_max != NULL) free(lant_max);
    eliberare_grila(vizitat, lin);
    eliberare_grila(cc, lin);

    grila_st = copie(grila, lin, col);
    grila_dr = copie(grila, lin, col);

    eliberare_grila(grila, lin);

    hamilton_preordine(out, root->st, grila_st, lin, col, 0);
    hamilton_preordine(out, root->dr, grila_dr, lin, col, 0);    
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
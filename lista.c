#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

void afis_lista(FILE* out, lista* head){
    while(head != NULL){
        if(head->urm != NULL) fprintf(out, "%d %d ", head->y, head->x);
        else fprintf(out, "%d %d", head->y, head->x);
        head = head->urm;
    }

    fprintf(out, "\n");
}

void adauga(lista** head, int x, int y){
    if(*head == NULL){
        (*head) = (lista*)malloc(sizeof(lista));
        (*head)->x = x;
        (*head)->y = y;
        (*head)->urm = NULL;
    } else {
        lista* nou = (lista*)malloc(sizeof(lista));
        nou->x = x;
        nou->y = y;
        nou->urm = NULL;
        (*head)->urm = nou;
        *head = nou;
    }    
}

void eliberare_lista(lista** head){
    lista* temp = NULL;

    while(*head != NULL){
        temp = (*head)->urm;
        free(*head);
        *head = temp;
    }

    *head = NULL;    
}

lista* convertto_lista(celula** grila, int lin, int col){
    lista* actual = NULL, *head = NULL;
    int flag = 0;

    for(int i = 1; i < lin-1; i++)
        for(int j = 1; j < col-1; j++)
            if(grila[i][j].vie){
                adauga(&actual, j-1, i-1);
                if(flag == 0){
                    head = actual;
                    flag = 1;
                }
            }

    return head;
}

lista* schimbariBD(celula** grila, int lin, int col){
    lista* actual = NULL, *head = NULL;
    int flag = 0;

    for(int i = 1; i < lin-1; i++)
        for(int j = 1; j < col-1; j++)
            if(grila[i][j].vie){
                if((grila[i][j].nr_vec < 2) || (grila[i][j].nr_vec > 3)){
                    adauga(&actual, j-1, i-1);
                    if(flag == 0){
                        head = actual;
                        flag = 1;
                    }
                }
            } else {
                if(grila[i][j].nr_vec == 3){
                    adauga(&actual, j-1, i-1);
                    if(flag == 0){
                        head = actual;
                        flag = 1;
                    }
                }
            }    
    return head;
}

lista* schimbariB(celula** grila, int lin, int col){
    lista* actual = NULL, *head = NULL;
    int flag = 0;

    for(int i = 1; i < lin-1; i++)
        for(int j = 1; j < col-1; j++)
            if(!grila[i][j].vie)
                if(grila[i][j].nr_vec == 2){
                    adauga(&actual, j-1, i-1);
                    if(flag == 0){
                        head = actual;
                        flag = 1;
                    }
                }   

    return head;
}

celula** convertto_grila(lista* head, int lin, int col){
    celula** grila = (celula**)malloc(lin*sizeof(celula*));
    for(int i = 0; i < lin; i++) grila[i] = (celula*)malloc(col*sizeof(celula));

    for(int i = 0; i < lin; i++)
        for(int j = 0; j < col; j++){
            grila[i][j].vie = 0;
            grila[i][j].nr_vec = 0;
        }

    while(head != NULL){
        grila[(head->y) + 1][(head->x) + 1].vie = 1;
        head = head->urm;
    }

    return grila;
}
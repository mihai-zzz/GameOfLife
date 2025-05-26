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

int cmp(const lista* lant1, const lista* lant2, int len){
    for(int i = 0; i < len; i++)
        if(lant1[i].y < lant2[i].y) return 1;
        else if(lant1[i].y == lant2[i].y){
            if(lant1[i].x < lant2[i].x) return 1;
            else if(lant1[i].x == lant2[i].x) continue;
            else return 0;
        } else return 0;
    
    return 0;
}

int hamilton(lista* lant, celula** grila, int lin, int col, int x, int y, int nr_cel, int nivel){
    const int dir_l[8] = {-1, -1, -1, 0, 0, 1, 1, 1}, dir_c[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

    lista punct;
    punct.x = x;
    punct.y = y;
    punct.urm = NULL;

    grila[y+1][x+1].vie = 0;
    lant[nivel] = punct;

    if(nivel == (nr_cel - 1)){
        grila[y+1][x+1].vie = 1;
        return 1;
    }

    for(int i = 0; i < 8; i++)
        if(grila[y+dir_l[i]+1][x+dir_c[i]+1].vie){
            int len = hamilton(lant, grila, lin, col, x+dir_c[i], y+dir_l[i], nr_cel, nivel+1);
            if(len){
                grila[y+1][x+1].vie = 1;
                return (len+1);
            }
        }
    
    grila[y+1][x+1].vie = 1;
    return 0;
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
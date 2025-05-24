#include <stdio.h>
#include <stdlib.h>
#include "celula.h"

void afis_grila(FILE* out, celula** grila, int lin, int col){
    for(int i = 1; i < lin-1; i++){
        for(int j = 1; j < col-1; j++)
            if(grila[i][j].vie) fprintf(out, "X");
            else fprintf(out, "+");

        fprintf(out, "\n");
    }

    fprintf(out, "\n");    
}

void num_vecini(celula** grila, int lin, int col){
    for(int i = 1; i < lin-1; i++)
        for(int j = 1; j < col-1; j++)
            for(int k = i-1; k <= i+1; k++)
                for(int l = j-1; l <= j+1; l++){
                    if((k == i) && (l == j)) continue;
                    grila[i][j].nr_vec += grila[k][l].vie;
                }
}

void reset_vecini(celula** grila, int lin, int col){
    for(int i = 0; i < lin; i++)
        for(int j = 0; j < col; j++) grila[i][j].nr_vec = 0;
}

void modifBD(celula** grila, int lin, int col){
    for(int i = 1; i < lin-1; i++)
        for(int j = 1; j < col-1; j++)
            if(grila[i][j].vie){
                if((grila[i][j].nr_vec < 2) || (grila[i][j].nr_vec > 3)) grila[i][j].vie = 0;
            } else {
                if(grila[i][j].nr_vec == 3) grila[i][j].vie = 1;
            }  
}

void modifB(celula** grila, int lin, int col){
    for(int i = 1; i < lin-1; i++)
        for(int j = 1; j < col-1; j++)
            if(!grila[i][j].vie)
                if(grila[i][j].nr_vec == 2) grila[i][j].vie = 1;
}

void eliberare_grila(celula** grila, int lin){
    for(int i = 0; i < lin; i++) free(grila[i]);
    free(grila);
}

celula** citire(FILE* in, int lin, int col){
    char c;

    celula** grila = (celula**)malloc(lin*sizeof(celula*));
    for(int i = 0; i < lin; i++) grila[i] = (celula*)malloc(col*sizeof(celula));

    for(int i = 0; i < lin; i++)
        for(int j = 0; j < col; j++)
            if(i*j * (lin-i-1)*(col-j-1) == 0) grila[i][j].vie = 0;
            else {
                fscanf(in, "%c ", &c);
                if(c == '+') grila[i][j].vie = 0;
                if(c == 'X') grila[i][j].vie = 1;
            }

    return grila;    
}

celula** copie(celula** grila, int lin, int col){
    celula** grila_noua = (celula**)malloc(lin*sizeof(celula*));
    for(int i = 0; i < lin; i++) grila_noua[i] = (celula*)malloc(col*sizeof(celula));

    for(int i = 0; i < lin; i++)
        for(int j = 0; j < col; j++){
            grila_noua[i][j].vie = grila[i][j].vie;
            grila_noua[i][j].nr_vec = grila[i][j].nr_vec;
        }
        
    return grila_noua;    
}
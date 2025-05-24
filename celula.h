#ifndef CELULA_H
#define CELULA_H

typedef struct celula {
    int vie;
    int nr_vec;
} celula;

void afis_grila(FILE* out, celula** grila, int lin, int col);
void num_vecini(celula** grila, int lin, int col);
void reset_vecini(celula** grila, int lin, int col);

void modifBD(celula** grila, int lin, int col);
void modifB(celula** grila, int lin, int col);

void eliberare_grila(celula** grila, int lin);

celula** citire(FILE* in, int lin, int col);
celula** copie(celula** grila, int lin, int col);

#endif
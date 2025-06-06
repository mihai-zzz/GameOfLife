#ifndef LISTA_H
#define LISTA_H
#include "celula.h"

typedef struct lista lista;

struct lista {
    int x;
    int y;
    lista* urm;
};

void afis_lista(FILE* out, lista* head);
void adauga(lista** head, int x, int y);
void eliberare_lista(lista** head);

int cmp(const lista* lant1, const lista* lant2, int len);
int hamilton(lista* lant, celula** grila, int x, int y, int nr_cel, int nivel);

lista* convertto_lista(celula** grila, int lin, int col);
lista* schimbariBD(celula** grila, int lin, int col);
lista* schimbariB(celula** grila, int lin, int col);

celula** convertto_grila(lista* head, int lin, int col);

#endif
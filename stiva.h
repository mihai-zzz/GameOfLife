#ifndef STIVA_H
#define STIVA_H
#include "lista.h"

typedef struct stiva stiva;

struct stiva {
    lista* head;
    stiva* urm;
};

void afis_stiva(FILE* out, stiva* top);
void impinge(stiva** top, lista* head);
void eliberare_stiva(stiva** top);

lista* elem_scos(stiva** top);

#endif
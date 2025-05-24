#ifndef ARB_BIN
#define ARB_BIN
#include "lista.h"

typedef struct nod_arb_bin BN;

struct nod_arb_bin {
    lista* head;
    BN* st;
    BN* dr;
};

BN* creare_arbore(int nivel);

void afis_preordine(FILE* out, BN* root, celula** grila, int lin, int col, int flag_radacina);
void umplere_arbore(BN* root, celula** grila, int lin, int col, int flag_st, int flag_radacina);
void eliberare_arbore(BN** root);

#endif
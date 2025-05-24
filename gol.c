#include <stdio.h>
#include <stdlib.h>
#include "stiva.h"
#include "arbore_binar.h"

int main(int argc, const char* argv[]){
    FILE *in = fopen(argv[1], "r"), *out = fopen(argv[2], "w");

    celula** grila = NULL;
    stiva* temp = NULL, *st = NULL;
    BN* root = NULL;

    int T, N, M, K;

    fscanf(in, "%d %d %d %d ", &T, &N, &M, &K);
    grila = citire(in, N+2, M+2);

    switch(T){
        case 1:
            reset_vecini(grila, N+2, M+2);
            afis_grila(out, grila, N+2, M+2);
        
            for(int i = 0; i < K; i++){
                num_vecini(grila, N+2, M+2);
                modifBD(grila, N+2, M+2);
                afis_grila(out, grila, N+2, M+2);
                reset_vecini(grila, N+2, M+2);
            }

            break;

        case 2:
            reset_vecini(grila, N+2, M+2);
        
            for(int i = 0; i < K; i++){
                num_vecini(grila, N+2, M+2);
                impinge(&temp, schimbariBD(grila, N+2, M+2));
                modifBD(grila, N+2, M+2);
                reset_vecini(grila, N+2, M+2);
            }

            while(temp != NULL) impinge(&st, elem_scos(&temp));
            afis_stiva(out, st);
            eliberare_stiva(&st);

            break;

        case 3:
            root = creare_arbore(K);
            reset_vecini(grila, N+2, M+2);

            umplere_arbore(root, grila, N+2, M+2, 0, 1);
            afis_preordine(out, root, NULL, N+2, M+2, 1);

            eliberare_arbore(&root);

            break;

        case 4: break;
        default: break;
    }

    eliberare_grila(grila, N+2);

    fclose(in);
    fclose(out);
    return 0;
}
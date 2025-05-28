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
    reset_vecini(grila, N+2, M+2);

    switch(T){
        case 1:
            afis_grila(out, grila, N+2, M+2);
        
            for(int i = 0; i < K; i++){
                num_vecini(grila, N+2, M+2);
                modifBD(grila, N+2, M+2);
                afis_grila(out, grila, N+2, M+2);
                reset_vecini(grila, N+2, M+2);
            }

            break;

        case 2:
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
            umplere_arbore(root, grila, N+2, M+2, 0, 1);
            
            afis_preordine(out, root, NULL, N+2, M+2, 1); 
            
            break;

        case 4: 
            root = creare_arbore(K);
            umplere_arbore(root, grila, N+2, M+2, 0, 1);

            hamilton_preordine(out, root, NULL, N+2, M+2, 1);

            break;
        
        case 5:
            char c = '\n';
            int x, y, nr_gen = 0;
            lista* head;

            while(nr_gen < K){
                head = NULL;
                do {
                    if(c == '\n'){
                        fscanf(in, "%d%*c%d%*c%d%c", &nr_gen, &y, &x, &c);
                    }
                    else fscanf(in, "%d%*c%d%c", &y, &x, &c);
                    adauga(&head, x, y);
                } while(c != '\n');
                impinge(&st, head);
            }

            while(st != NULL){
                head = elem_scos(&st);
                while(head != NULL){
                    grila[(head->y) + 1][(head->x) + 1].vie = !grila[(head->y) + 1][(head->x) + 1].vie;
                    head = head->urm;
                }
            }

            afis_grila(out, grila, N+2, M+2);
            eliberare_stiva(&st);
            
            break;

        default: break;
    }

    eliberare_grila(grila, N+2);
    eliberare_arbore(&root);

    fclose(in);
    fclose(out);

    return 0;
}
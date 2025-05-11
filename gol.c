#include <stdio.h>
#include <stdlib.h>

struct celula {
    int alive;
    int vecini;
};

struct lista {
    int l;
    int c;
    struct lista* urm;
};

struct stiva {
    struct lista* li;
    struct stiva* urm;
};

struct binarynode {
    struct lista* li;
    struct binarynode* left;
    struct binarynode* right;
};

void reset_vecini(struct celula** grila, int rows, int cols){
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            grila[i][j].vecini = 0;
        }
    }
}

void num_vecini(struct celula** grila, int rows, int cols){
    for(int i = 1; i < rows-1; i++){
        for(int j = 1; j < cols-1; j++){
            for(int k = i-1; k <= i+1; k++){
                for(int l = j-1; l <= j+1; l++){
                    if((k == i) && (l == j)) continue;
                    grila[i][j].vecini += grila[k][l].alive;
                }
            }
        }
    }
}

void modif(struct celula** grila, int rows, int cols){
    for(int i = 1; i < rows-1; i++){
        for(int j = 1; j < cols-1; j++){
            if(grila[i][j].alive){
                if((grila[i][j].vecini < 2) || (grila[i][j].vecini > 3)) grila[i][j].alive = 0;
            } else {
                if(grila[i][j].vecini == 3) grila[i][j].alive = 1;
            }
        }
    }
}

void modif_reguliNoi(struct celula** grila, int rows, int cols){
    for(int i = 1; i < rows-1; i++){
        for(int j = 1; j < cols-1; j++){
            if(!grila[i][j].alive){
                if(grila[i][j].vecini == 2) grila[i][j].alive = 1;
            }
        }
    }
}

void print_generatie(FILE* f, struct celula** grila, int rows, int cols){
    for(int i = 1; i < rows-1; i++){
        for(int j = 1; j < cols-1; j++){
            if(grila[i][j].alive){
                fprintf(f, "X");
            } else {
                fprintf(f, "+");
            }
        }
        fprintf(f, "\n");
    }
    fprintf(f, "\n");
}

struct celula** copie_grila(struct celula** grila, int rows, int cols){
    struct celula** grila_noua = (struct celula**)malloc(rows*sizeof(struct celula*));
    for(int i = 0; i < rows; i++) grila_noua[i] = (struct celula*)malloc(cols*sizeof(struct celula));
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            grila_noua[i][j].alive = grila[i][j].alive;
            grila_noua[i][j].vecini = grila[i][j].vecini;
        }
    }
    return grila_noua;
}

void adauga_elem(struct lista** head, int l, int c){
    if(*head == NULL){
        (*head) = (struct lista*)malloc(sizeof(struct lista));
        (*head)->l = l;
        (*head)->c = c;
        (*head)->urm = NULL;
    } else {
        struct lista* elem_nou = (struct lista*)malloc(sizeof(struct lista));
        elem_nou->l = l;
        elem_nou->c = c;
        elem_nou->urm = NULL;
        (*head)->urm = elem_nou;
        *head = elem_nou;
    }
}

void sterge_lista(struct lista** head){
    struct lista* copie;
    while(*head != NULL){
        copie = (*head)->urm;
        free(*head);
        *head = copie;
    }
    *head = NULL;
}

void afis_lista(FILE* f, const struct lista* head){
    while(head != NULL){
        if(head->urm != NULL) fprintf(f, "%d %d ", head->l, head->c);
        else fprintf(f, "%d %d", head->l, head->c);
        head = head->urm;
    }
    fprintf(f, "\n");
}

void afis_stiva(FILE* f, const struct stiva* top){
    int nr_gen = 1;
    while(top != NULL){
        fprintf(f, "%d ", nr_gen);
        afis_lista(f, top->li);
        top = top->urm;
        nr_gen++;
    }
}

struct lista* lista_gen_reguliNoi(struct celula** grila, int rows, int cols){
    struct lista* current = NULL, *inceput = NULL;
    int k = 0;
    for(int i = 1; i < rows-1; i++){
        for(int j = 1; j < cols-1; j++){
            if(!grila[i][j].alive){
                if(grila[i][j].vecini == 2){
                    adauga_elem(&current, i-1, j-1);
                    if(k == 0) inceput = current;
                    k = 1;
                }
            }
        }
    }    
    return inceput;
}

struct lista* lista_gen(struct celula** grila, int rows, int cols){
    struct lista* current = NULL, *inceput = NULL;
    int k = 0;
    for(int i = 1; i < rows-1; i++){
        for(int j = 1; j < cols-1; j++){
            if(grila[i][j].alive){
                if((grila[i][j].vecini < 2) || (grila[i][j].vecini > 3)) {
                    adauga_elem(&current, i-1, j-1);
                    if(k == 0) inceput = current;
                    k = 1;
                }
            } else {
                if(grila[i][j].vecini == 3) {
                    adauga_elem(&current, i-1, j-1);
                    if(k == 0) inceput = current;
                    k = 1;
                }
            }
        }
    }    
    return inceput;
}

struct lista* lista_initiala(struct celula** grila, int rows, int cols){
    struct lista* current = NULL, *inceput = NULL;
    int k = 0;
    for(int i = 1; i < rows-1; i++){
        for(int j = 1; j < cols-1; j++){
            if(grila[i][j].alive){
                adauga_elem(&current, i-1, j-1);
                if(k == 0) inceput = current;
                k = 1;
            }
        }
    }    
    return inceput;
}

struct celula** grila_din_lista(struct lista* li, int rows, int cols){
    struct celula** grila = (struct celula**)malloc(rows*sizeof(struct celula*));
    for(int i = 0; i < rows; i++) grila[i] = (struct celula*)malloc(cols*sizeof(struct celula));

    for(int i = 0; i < rows; i++){
        for(int j = 0; j < rows; j++){
            grila[i][j].alive = 0;
            grila[i][j].vecini = 0;
        }
    }

    while(li != NULL){
        (grila[li->l + 1][li->c + 1].alive)++;
        li = li->urm;
    }

    return grila;
}

void push(struct stiva** top, struct lista* li){
    struct stiva* elem_nou = (struct stiva*)malloc(sizeof(struct stiva));
    elem_nou->li = li;
    elem_nou->urm = *top;
    *top = elem_nou;
}

struct lista* pop(struct stiva** top){
    if(*top == NULL) return NULL;
    struct stiva* temp = *top;
    struct lista* aux = temp->li;
    *top = (*top)->urm;
    free(temp);
    return aux;
}

void sterge_stiva(struct stiva** top){
    struct stiva* temp = NULL;
    while((*top) != NULL){
        temp = *top;
        *top = (*top)->urm;
        sterge_lista(&(temp->li));
        free(temp);
    }
}

void preordine(FILE* f, struct binarynode* root, int isRoot, struct celula** grila, int rows, int cols){
    struct celula** grila_noua_st = NULL, **grila_noua_dr = NULL;
    if((root == NULL) && (grila != NULL)){
        for(int i = 0; i < rows; i++) free(grila[i]);
        free(grila); 
        return;
    }
    if(isRoot){
        grila = grila_din_lista(root->li, rows, cols);
        print_generatie(f, grila, rows, cols);
    } else {
        struct lista* ls = root->li;
        while(ls != NULL){
            int stare = grila[ls->l + 1][ls->c + 1].alive;
            grila[ls->l + 1][ls->c + 1].alive = !stare;
            ls = ls->urm;
        }
        print_generatie(f, grila, rows, cols);
    }
    grila_noua_st = copie_grila(grila, rows, cols);
    grila_noua_dr = copie_grila(grila, rows, cols);

    for(int i = 0; i < rows; i++) free(grila[i]);
    free(grila); 

    preordine(f, root->left, 0, grila_noua_st, rows, cols);
    preordine(f, root->right, 0, grila_noua_dr, rows, cols);
}

struct binarynode* arbore(int k){
    if(k == -1) return NULL;
    struct binarynode* new = (struct binarynode*)malloc(sizeof(struct binarynode));
    new->li = NULL;
    new->left = arbore(k-1);
    new->right = arbore(k-1);
    return new;
}

void umpleArbore(struct binarynode* root, struct celula** grila, int rows, int cols, int isRoot, int B){
    struct celula** grila_noua_st = NULL, **grila_noua_dr = NULL;

    if(root == NULL){
        for(int i = 0; i < rows; i++) free(grila[i]);
        free(grila); 
        return;
    }

    if(isRoot){
        root->li = lista_initiala(grila, rows, cols);
    } else {
        num_vecini(grila, rows, cols);
        if(B){
            root->li = lista_gen_reguliNoi(grila, rows, cols);
            modif_reguliNoi(grila, rows, cols);
        } else {
            root->li = lista_gen(grila, rows, cols);
            modif(grila, rows, cols);
        }
        reset_vecini(grila, rows, cols);
    }

    grila_noua_st = copie_grila(grila, rows, cols);
    grila_noua_dr = copie_grila(grila, rows, cols);

    for(int i = 0; i < rows; i++) free(grila[i]);
    free(grila);

    umpleArbore(root->left, grila_noua_st, rows, cols, 0, 1);
    umpleArbore(root->right, grila_noua_dr, rows, cols, 0, 0);
}

void eliberare_arbore(struct binarynode** root){
    if((*root) == NULL) return;

    struct binarynode* st = (*root)->left, *dr = (*root)->right;
    sterge_lista(&((*root)->li));
    free(*root);

    eliberare_arbore(&st);
    eliberare_arbore(&dr);
}

int main(int argc, const char* argv[]){
    FILE *in = fopen(argv[1], "r+"), *out = fopen(argv[2], "w+");
    int T, N, M, K;
    char c;
    struct celula** grila;
    struct stiva* temp = NULL, *st = NULL;
    struct binarynode* root = NULL;

    fscanf(in, "%d %d %d %d ", &T, &N, &M, &K);
    
    grila = (struct celula**)malloc((N+2)*sizeof(struct celula*));
    for(int i = 0; i < N+2; i++) grila[i] = (struct celula*)malloc((M+2)*sizeof(struct celula));

    switch(T){
        case 1:
            for(int i = 0; i < N+2; i++){
                for(int j = 0; j < M+2; j++){
                    if(i*j * (N-i+1)*(M-j+1) == 0) {
                        grila[i][j].alive = 0;
                    } else {
                        fscanf(in, "%c ", &c);
                        if(c == '+') grila[i][j].alive = 0;
                        if(c == 'X') grila[i][j].alive = 1;
                    }
                }
            }
            reset_vecini(grila, N+2, M+2);
            print_generatie(out, grila, N+2, M+2);
        
            for(int i = 0; i < K; i++){
                num_vecini(grila, N+2, M+2);
                modif(grila, N+2, M+2);
                print_generatie(out, grila, N+2, M+2);
                reset_vecini(grila, N+2, M+2);
            }

            break;

        case 2:
            for(int i = 0; i < N+2; i++){
                for(int j = 0; j < M+2; j++){
                    if(i*j * (N-i+1)*(M-j+1) == 0) {
                        grila[i][j].alive = 0;
                    } else {
                        fscanf(in, "%c ", &c);
                        if(c == '+') grila[i][j].alive = 0;
                        if(c == 'X') grila[i][j].alive = 1;
                    }
                }
            }
            reset_vecini(grila, N+2, M+2);
        
            for(int i = 0; i < K; i++){
                num_vecini(grila, N+2, M+2);
                push(&temp, lista_gen(grila, N+2, M+2));
                modif(grila, N+2, M+2);
                reset_vecini(grila, N+2, M+2);
            }

            while(temp != NULL) push(&st, pop(&temp));
            afis_stiva(out, st);
            sterge_stiva(&st);

            break;

        case 3:
            root = arbore(K);
            for(int i = 0; i < N+2; i++){
                for(int j = 0; j < M+2; j++){
                    if(i*j * (N-i+1)*(M-j+1) == 0) {
                        grila[i][j].alive = 0;
                    } else {
                        fscanf(in, "%c ", &c);
                        if(c == '+') grila[i][j].alive = 0;
                        if(c == 'X') grila[i][j].alive = 1;
                    }
                }
            }
            reset_vecini(grila, N+2, M+2);

            umpleArbore(root, grila, N+2, M+2, 1, 0);
            preordine(out, root, 1, NULL, N+2, M+2);

            eliberare_arbore(&root);
            break;

        case 4: break;
        case 5: break;
        default: break;
    }

    for(int i = 0; i < N+2; i++) free(grila[i]);
    free(grila);

    return 0;
}
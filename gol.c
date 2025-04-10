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

int main(int argc, const char* argv[]){
    FILE *in = fopen(argv[1], "r+"), *out = fopen(argv[2], "w+");
    int T, N, M, K;
    char c;
    struct celula** grila;
    struct stiva* temp = NULL, *st = NULL;

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
        case 3: break;
        case 4: break;
        case 5: break;
        default: break;
    }

    for(int i = 0; i < N+2; i++) free(grila[i]);
    free(grila);
    return 0;
}
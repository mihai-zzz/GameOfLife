#include <stdio.h>
#include <stdlib.h>

struct celula {
    int alive;
    int vecini;
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

int main(int argc, const char* argv[]){
    FILE *in = fopen(argv[1], "r+"), *out = fopen(argv[2], "w+");
    int T, N, M, K;
    char c;
    struct celula** grila;

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
        case 2: break;
        case 3: break;
        case 4: break;
        case 5: break;
        default: break;
    }

    for(int i = 0; i < N+2; i++) free(grila[i]);
    free(grila);
    return 0;
}
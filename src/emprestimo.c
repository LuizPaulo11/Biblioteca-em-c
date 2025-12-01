#include <stdio.h>;
#include <string.h>;
#include "emprestimo.h";


void inicializarEmprestimo(Emprestimo emprestimo[], int tamanho) {
    for(int i = 0; i < tamanho; i++) {
        memset(&emprestimo[i], 0, sizeof(Emprestimo));
    }
}
#ifndef EMPRESTIMO_H
#define EMPRESTIMO_H

#include "usuario.h"
#include "livro.h"

#define ATIVO 1
#define DEVOLVIDO 0

typedef struct Emprestimo {
    int codigoemprestimo;
    int matricula_usuario;
    int codigo_livro;
    Data data_emprestimo;
    Data data_devolucao_prevista;
    int status;
} Emprestimo;

void inicializarEmprestimo(Emprestimo emprestimo[], int tamanho);
void realizarEmprestimo(Emprestimo emprestimos[], int *qtdEmprestimos, int maxEmprestimos, Usuario usuarios[], int qtdUsuarios, Livro livros[], int qtdLivros);
void devolverEmprestimo(Emprestimo emprestimos[], int qtdEmprestimos, Livro livros[], int qtdLivros);
void listarEmprestimosAtivos(const Emprestimo emprestimos[], int qtdEmprestimos, const Usuario usuarios[], int qtdUsuarios,   const Livro livros[], int qtdLivros);


#endif
#ifndef LIVRO_H
#define LIVRO_H

#define DISPONIVEL 1
#define EMPRESTADO 0

typedef struct Livro {
    int codigo;
    char titulo[101];
    char autor[81];
    char editora[61];
    int anopublicacao;
    int exemplaresdisponivel;
    int status;
} Livro;

void inicializarLivros(Livro livros[], int tamanho);
void cadastrarLivro(Livro livros[], int *qtdLivros);
int buscarLivroPorCodigo(Livro livros[], int qtdLivros, int codigo);

#endif

#include <stdio.h>
#include <string.h>
#include "livro.h"

// Inicializa o array de livros
void inicializarLivros(Livro livros[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        memset(&livros[i], 0, sizeof(Livro));
        livros[i].status = DISPONIVEL;
    }
}


// Cadastra um novo livro no array
void cadastrarLivro(Livro livros[], int *qtdLivros) {

    int pos = *qtdLivros;   // posição livre no array

    printf("=== Cadastro de Livro ===\n");

    printf("Código do livro: ");
    scanf("%d", &livros[pos].codigo);

    printf("Título: ");
    getchar(); // limpa buffer do teclado
    fgets(livros[pos].titulo, sizeof(livros[pos].titulo), stdin);
    livros[pos].titulo[strcspn(livros[pos].titulo, "\n")] = '\0';

    printf("Autor: ");
    fgets(livros[pos].autor, sizeof(livros[pos].autor), stdin);
    livros[pos].autor[strcspn(livros[pos].autor, "\n")] = '\0';

    printf("Editora: ");
    fgets(livros[pos].editora, sizeof(livros[pos].editora), stdin);
    livros[pos].editora[strcspn(livros[pos].editora, "\n")] = '\0';

    printf("Ano de publicação: ");
    scanf("%d", &livros[pos].anopublicacao);

    printf("Número de exemplares: ");
    scanf("%d", &livros[pos].exemplaresdisponivel);

    livros[pos].status = DISPONIVEL;

    (*qtdLivros)++;  // aumenta a quantidade real de livros

    printf("Livro cadastrado com sucesso!\n");
}


// Busca um livro pelo código
// Retorna: índice encontrado OU -1 se não achar

int buscarLivroPorCodigo(Livro livros[], int qtdLivros, int codigo) {
    for (int i = 0; i < qtdLivros; i++) {
        if (livros[i].codigo == codigo) {
            return i;  // encontrou
        }
    }
    return -1; // não encontrou
}




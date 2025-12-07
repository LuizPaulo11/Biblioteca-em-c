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
    int contadorEmprestimos;
} Livro;

void inicializarLivros(Livro livros[], int tamanho);

void cadastrarLivro(Livro livros[], int *qtdLivros);
int buscarLivroPorCodigo(const Livro livros[], int qtdLivros, int codigo);
void pesquisarLivroPorTitulo(const Livro livros[], int qtdLivros, const char *titulo);
void pesquisarLivroPorAutor(const Livro livros[], int qtdLivros, const char *autor);
void relatorioLivrosMaisEmprestados(const Livro livros[], int qtdLivros);

void pesquisarLivroMenu(const Livro livros[], int qtdLivros);

#endif



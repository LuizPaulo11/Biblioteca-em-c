#ifndef LIVRO_H
#define LIVRO_H

#define DISPONIVEL 1 // definido 1 como disponivel
#define EMPRESTADO 0 // e definido 0 como emprestado 
//struct do livro
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
//declaracao inicializar livro
void inicializarLivros(Livro livros[], int tamanho);
// declaracao de funcoes para lisvros
void cadastrarLivro(Livro livros[], int *qtdLivros);
int buscarLivroPorCodigo(const Livro livros[], int qtdLivros, int codigo);
void pesquisarLivroPorTitulo(const Livro livros[], int qtdLivros, const char *titulo);
void pesquisarLivroPorAutor(const Livro livros[], int qtdLivros, const char *autor);
void relatorioLivrosMaisEmprestados(const Livro livros[], int qtdLivros);
// declaracao funcao para trabalhar com menu
void pesquisarLivroMenu(const Livro livros[], int qtdLivros);

#endif



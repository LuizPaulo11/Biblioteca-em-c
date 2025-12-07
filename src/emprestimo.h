#ifndef EMPRESTIMO_H
#define EMPRESTIMO_H

#include <time.h>      // Necessário para time_t
#include "usuario.h"
#include "livro.h" 

#define ATIVO 1 // status do emprestimo definido como 1 para ativo
#define DEVOLVIDO 0 // status do emprestimo devolvido definido  como 0
#define MAX_RENOVACOES 2

// struct do Emprestimo
typedef struct Emprestimo {
    int codigoemprestimo;
    int matricula_usuario;
    int codigo_livro;
    Data data_emprestimo;
    Data data_devolucao_prevista;
    int status;
    int renovacoes;
} Emprestimo;


void inicializarEmprestimo(Emprestimo emprestimo[], int tamanho); // funcao para iniciarlizar emprestimo


/* funcoes de manipulacao de emprestimo */
void realizarEmprestimo(Emprestimo emprestimos[], int *qtdEmprestimos, int maxEmprestimos,
                        Usuario usuarios[], int qtdUsuarios, Livro livros[], int qtdLivros);
void devolverEmprestimo(Emprestimo emprestimos[], int qtdEmprestimos,
                        Livro livros[], int qtdLivros);

void renovarEmprestimo(Emprestimo emprestimos[], int qtdEmprestimos,
                       Livro livros[], int qtdLivros);

/* Listagens e relatórios */
void listarEmprestimosAtivos(Emprestimo emprestimos[], int qtdEmprestimos,
                             Usuario usuarios[], int qtdUsuarios, Livro livros[], int qtdLivros);

void relatorioUsuariosAtrasados(Emprestimo emprestimos[], int qtdEmprestimos,
                                Usuario usuarios[], int qtdUsuarios);

/* Utilitários de data e buscas */
time_t dataParaTimeT(Data d);
Data adicionarDias(Data d, int dias);
// definicao de logica para menu
void pesquisarLivroMenu(const Livro livros[], int qtdLivros);
void pesquisarUsuarioMenu(const Usuario usuarios[], size_t qtdUsuarios);
// definicao funcionalidade para relatorio
void relatorioLivrosMaisEmprestados(const Livro livros[], int qtdLivros);

#endif



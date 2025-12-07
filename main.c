#include <stdio.h>
#include <stdlib.h>
#include "src/usuario.h"
#include "src/livro.h"
#include "src/emprestimo.h"

#define MAX_USUARIOS 100
#define MAX_LIVROS 100
#define MAX_EMPRESTIMOS 200

static void limpar_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

int main(void) {
    Usuario usuarios[MAX_USUARIOS];
    Livro livros[MAX_LIVROS];
    Emprestimo emprestimos[MAX_EMPRESTIMOS];

    size_t qtdUsuarios = 0;
    int qtdLivros = 0;
    int qtdEmprestimos = 0;

    inicializarUsuarios(usuarios, MAX_USUARIOS);
    inicializarLivros(livros, MAX_LIVROS);
    inicializarEmprestimo(emprestimos, MAX_EMPRESTIMOS);

    int opcao = -1;

    while (opcao != 0) {
        printf("\n===== SISTEMA DA BIBLIOTECA =====\n");
        printf("1  - Cadastrar livro\n");
        printf("2  - Cadastrar usuário\n");
        printf("3  - Realizar empréstimo\n");
        printf("4  - Devolver empréstimo\n");
        printf("5  - Renovar empréstimo\n");
        printf("6  - Pesquisar livro (código/título/autor)\n");
        printf("7  - Pesquisar usuário (matrícula/nome)\n");
        printf("8  - Listar empréstimos ativos\n");
        printf("9  - Relatório: livros mais emprestados\n");
        printf("10 - Relatório: usuários com empréstimos atrasados\n");
        printf("0  - Sair\n");
        printf("Escolha uma opção: ");

        if (scanf("%d", &opcao) != 1) {
            printf("Entrada inválida. Tente novamente.\n");
            limpar_buffer();
            continue;
        }
        limpar_buffer();

        switch (opcao) {
            case 1:
                cadastrarLivro(livros, &qtdLivros);
                break;
            case 2:
                cadastrarUsuario(usuarios, &qtdUsuarios, MAX_USUARIOS);
                break;
            case 3:
                realizarEmprestimo(emprestimos, &qtdEmprestimos, MAX_EMPRESTIMOS,
                                   usuarios, (int)qtdUsuarios, livros, qtdLivros);
                break;
            case 4:
                devolverEmprestimo(emprestimos, qtdEmprestimos, livros, qtdLivros);
                break;
            case 5:
                renovarEmprestimo(emprestimos, qtdEmprestimos, livros, qtdLivros);
                break;
            case 6:
                pesquisarLivroMenu(livros, qtdLivros);
                break;
            case 7:
                pesquisarUsuarioMenu(usuarios, qtdUsuarios);
                break;
            case 8:
                listarEmprestimosAtivos(emprestimos, qtdEmprestimos, usuarios, (int)qtdUsuarios, livros, qtdLivros);
                break;
            case 9:
                relatorioLivrosMaisEmprestados(livros, qtdLivros);
                break;
            case 10:
                relatorioUsuariosAtrasados(emprestimos, qtdEmprestimos, usuarios, (int)qtdUsuarios);
                break;
            case 0:
                printf("Saindo. Até mais!\n");
                break;
            default:
                printf("Opção inválida, escolha novamente.\n");
        }
    }

    return 0;
}



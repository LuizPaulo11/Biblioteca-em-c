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


void cadastrarLivro(Livro livros[], int *qtdLivros) {
    int pos = *qtdLivros;
    printf("\n=== Cadastro de Livro ===\n");
    printf("Código: ");
    if (scanf("%d", &livros[pos].codigo) != 1) {
        printf("Entrada inválida.\n");
        int c; while ((c = getchar()) != '\n' && c != EOF) {}
        return;
    }
    getchar();
    printf("Título: ");
    fgets(livros[pos].titulo, sizeof(livros[pos].titulo), stdin);
    livros[pos].titulo[strcspn(livros[pos].titulo, "\n")] = '\0';

    printf("Autor: ");
    fgets(livros[pos].autor, sizeof(livros[pos].autor), stdin);
    livros[pos].autor[strcspn(livros[pos].autor, "\n")] = '\0';

    printf("Editora: ");
    fgets(livros[pos].editora, sizeof(livros[pos].editora), stdin);
    livros[pos].editora[strcspn(livros[pos].editora, "\n")] = '\0';

    printf("Ano de publicação: ");
    if (scanf("%d", &livros[pos].anopublicacao) != 1) livros[pos].anopublicacao = 0;

    printf("Número de exemplares: ");
    if (scanf("%d", &livros[pos].exemplaresdisponivel) != 1) livros[pos].exemplaresdisponivel = 0;

    livros[pos].status = (livros[pos].exemplaresdisponivel > 0) ? DISPONIVEL : EMPRESTADO;
    livros[pos].contadorEmprestimos = 0;

    (*qtdLivros)++;
    int c; while ((c = getchar()) != '\n' && c != EOF) {}
    printf("Livro cadastrado com sucesso!\n");
}

int buscarLivroPorCodigo(const Livro livros[], int qtdLivros, int codigo) {
    for (int i = 0; i < qtdLivros; i++) {
        if (livros[i].codigo == codigo) return i;
    }
    return -1;
}

void pesquisarLivroPorTitulo(const Livro livros[], int qtdLivros, const char *titulo) {
    int achou = 0;
    for (int i = 0; i < qtdLivros; i++) {
        if (strstr(livros[i].titulo, titulo) != NULL) {
            if (!achou) { printf("\nResultados por título:\n"); achou = 1; }
            printf("- Cod: %d  Título: %s  Autor: %s  Disp.: %d\n",
                   livros[i].codigo, livros[i].titulo, livros[i].autor, livros[i].exemplaresdisponivel);
        }
    }
    if (!achou) printf("Nenhum livro encontrado com título contendo '%s'.\n", titulo);
}

void pesquisarLivroPorAutor(const Livro livros[], int qtdLivros, const char *autor) {
    int achou = 0;
    for (int i = 0; i < qtdLivros; i++) {
        if (strstr(livros[i].autor, autor) != NULL) {
            if (!achou) { printf("\nResultados por autor:\n"); achou = 1; }
            printf("- Cod: %d  Título: %s  Autor: %s  Disp.: %d\n",
                   livros[i].codigo, livros[i].titulo, livros[i].autor, livros[i].exemplaresdisponivel);
        }
    }
    if (!achou) printf("Nenhum livro encontrado com autor contendo '%s'.\n", autor);
}

void relatorioLivrosMaisEmprestados(const Livro livros[], int qtdLivros) {
    if (qtdLivros == 0) { printf("Nenhum livro cadastrado.\n"); return; }

    int indices[qtdLivros];
    for (int i = 0; i < qtdLivros; i++) indices[i] = i;

    for (int i = 0; i < qtdLivros - 1; i++) {
        int maior = i;
        for (int j = i + 1; j < qtdLivros; j++) {
            if (livros[indices[j]].contadorEmprestimos > livros[indices[maior]].contadorEmprestimos)
                maior = j;
        }
        int tmp = indices[i]; indices[i] = indices[maior]; indices[maior] = tmp;
    }

    printf("\n=== Relatório: Livros mais emprestados ===\n");
    int mostrou = 0;
    for (int i = 0; i < qtdLivros; i++) {
        int idx = indices[i];
        if (livros[idx].contadorEmprestimos == 0) break;
        mostrou = 1;
        printf("%d) Cod: %d - %s (Autor: %s) - empréstimos: %d\n",
               i + 1, livros[idx].codigo, livros[idx].titulo, livros[idx].autor, livros[idx].contadorEmprestimos);
    }
    if (!mostrou) printf("Nenhum empréstimo registrado ainda.\n");
}

void pesquisarLivroMenu(const Livro livros[], int qtdLivros) {
    int op;
    printf("\nPesquisar livro por:\n1 - Código\n2 - Título\n3 - Autor\nEscolha: ");
    if (scanf("%d", &op) != 1) { int c; while ((c = getchar()) != '\n' && c != EOF) {} printf("Entrada inválida.\n"); return; }
    int c; while ((c = getchar()) != '\n' && c != EOF) {}

    if (op == 1) {
        int cod; printf("Digite o código: "); if (scanf("%d", &cod) != 1) { printf("Entrada inválida.\n"); while ((c = getchar()) != '\n' && c != EOF) {} return; }
        int idx = buscarLivroPorCodigo(livros, qtdLivros, cod);
        if (idx == -1) printf("Livro não encontrado.\n");
        else printf("Encontrado: Cod %d - %s (Autor: %s) Disp: %d\n", livros[idx].codigo, livros[idx].titulo, livros[idx].autor, livros[idx].exemplaresdisponivel);
        while ((c = getchar()) != '\n' && c != EOF) {}
    } else if (op == 2) {
        char termo[101];
        printf("Digite parte do título: ");
        fgets(termo, sizeof(termo), stdin); termo[strcspn(termo, "\n")] = '\0';
        pesquisarLivroPorTitulo(livros, qtdLivros, termo);
    } else if (op == 3) {
        char termo[81];
        printf("Digite parte do nome do autor: ");
        fgets(termo, sizeof(termo), stdin); termo[strcspn(termo, "\n")] = '\0';
        pesquisarLivroPorAutor(livros, qtdLivros, termo);
    } else {
        printf("Opção inválida.\n");
    }
}
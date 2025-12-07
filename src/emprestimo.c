#include <stdio.h>
#include <string.h>
#include <time.h>
#include "emprestimo.h"

/* ---------------- conversão de datas ---------------- */

time_t dataParaTimeT(Data d) {
    struct tm t = {0};
    t.tm_mday = d.dia;
    t.tm_mon  = d.mes - 1;
    t.tm_year = d.ano - 1900;
    t.tm_hour = 12; // meio-dia para evitar problemas de DST
    return mktime(&t);
}

Data adicionarDias(Data d, int dias) {
    struct tm t = {0};
    t.tm_mday = d.dia + dias;
    t.tm_mon  = d.mes - 1;
    t.tm_year = d.ano - 1900;
    mktime(&t);
    Data r;
    r.dia = t.tm_mday;
    r.mes = t.tm_mon + 1;
    r.ano = t.tm_year + 1900;
    return r;
}

/* ---------------- funções auxiliares ---------------- */

static int findUsuarioIndex(Usuario usuarios[], int qtdUsuarios, int matricula) {
    for (int i = 0; i < qtdUsuarios; i++)
        if (usuarios[i].matricula == matricula)
            return i;
    return -1;
}

static int findLivroIndex(Livro livros[], int qtdLivros, int codigo) {
    for (int i = 0; i < qtdLivros; i++)
        if (livros[i].codigo == codigo)
            return i;
    return -1;
}

static int findEmprestimoIndexByCodigo(Emprestimo emprestimos[], int qtdEmprestimos, int codigo) {
    for (int i = 0; i < qtdEmprestimos; i++)
        if (emprestimos[i].codigoemprestimo == codigo)
            return i;
    return -1;
}

/* ---------------- implementação ---------------- */
// inicializar com valores padrao
void inicializarEmprestimo(Emprestimo emprestimos[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        emprestimos[i].codigoemprestimo = 0;
        emprestimos[i].matricula_usuario = 0;
        emprestimos[i].codigo_livro = 0;
        emprestimos[i].data_emprestimo.dia = 0;
        emprestimos[i].data_emprestimo.mes = 0;
        emprestimos[i].data_emprestimo.ano = 0;
        emprestimos[i].data_devolucao_prevista.dia = 0;
        emprestimos[i].data_devolucao_prevista.mes = 0;
        emprestimos[i].data_devolucao_prevista.ano = 0;
        emprestimos[i].status = DEVOLVIDO;
        emprestimos[i].renovacoes = 0;
    }
}
//funcao para realizar emprestimo
void realizarEmprestimo(Emprestimo emprestimos[], int *qtdEmprestimos, int maxEmprestimos,
                        Usuario usuarios[], int qtdUsuarios, Livro livros[], int qtdLivros) {

    if (*qtdEmprestimos >= maxEmprestimos) {
        printf("Capacidade máxima de empréstimos atingida.\n");
        return;
    }

    int matricula, codigoLivro;
    printf("\n=== Realizar Empréstimo ===\n");
    printf("Matrícula do usuário: ");
    if (scanf("%d", &matricula) != 1) { printf("Entrada inválida.\n"); int c; while ((c = getchar()) != '\n' && c != EOF) {} return; }

    int idxU = findUsuarioIndex(usuarios, qtdUsuarios, matricula);
    if (idxU == -1) { printf("Usuário não encontrado.\n"); return; }

    printf("Código do livro: ");
    if (scanf("%d", &codigoLivro) != 1) { printf("Entrada inválida.\n"); int c; while ((c = getchar()) != '\n' && c != EOF) {} return; }

    int idxL = findLivroIndex(livros, qtdLivros, codigoLivro);
    if (idxL == -1) { printf("Livro não encontrado.\n"); return; }

    if (livros[idxL].exemplaresdisponivel <= 0) { printf("Nenhum exemplar disponível.\n"); return; }

    int pos = *qtdEmprestimos;
    emprestimos[pos].codigoemprestimo = pos + 1;
    emprestimos[pos].matricula_usuario = matricula;
    emprestimos[pos].codigo_livro = codigoLivro;

    printf("Data do empréstimo (dia mes ano): ");
    if (scanf("%d %d %d", &emprestimos[pos].data_emprestimo.dia,
                       &emprestimos[pos].data_emprestimo.mes,
                       &emprestimos[pos].data_emprestimo.ano) != 3) {
        printf("Data inválida.\n"); int c; while ((c = getchar()) != '\n' && c != EOF) {} return;
    }

    emprestimos[pos].data_devolucao_prevista = adicionarDias(emprestimos[pos].data_emprestimo, 7);
    emprestimos[pos].status = ATIVO;
    emprestimos[pos].renovacoes = 0;

    livros[idxL].exemplaresdisponivel--;
    if (livros[idxL].exemplaresdisponivel == 0) livros[idxL].status = EMPRESTADO;
    livros[idxL].contadorEmprestimos++;

    (*qtdEmprestimos)++;
    int c; while ((c = getchar()) != '\n' && c != EOF) {}
    printf("Empréstimo registrado com sucesso! Código: %d\n", emprestimos[pos].codigoemprestimo);
}
// funcao responsavel pela logica de devolucao de emprestimo
void devolverEmprestimo(Emprestimo emprestimos[], int qtdEmprestimos, Livro livros[], int qtdLivros) {
    int codigo;
    printf("\nDigite o código do empréstimo a devolver: ");
    if (scanf("%d", &codigo) != 1) { printf("Entrada inválida.\n"); int c; while ((c = getchar()) != '\n' && c != EOF) {} return; }

    int idx = findEmprestimoIndexByCodigo(emprestimos, qtdEmprestimos, codigo);
    if (idx == -1) { printf("Empréstimo não encontrado.\n"); return; }
    if (emprestimos[idx].status != ATIVO) { printf("Empréstimo já devolvido ou inativo.\n"); return; }

    emprestimos[idx].status = DEVOLVIDO;

    int idxL = findLivroIndex(livros, qtdLivros, emprestimos[idx].codigo_livro);
    if (idxL != -1) {
        livros[idxL].exemplaresdisponivel++;
        if (livros[idxL].exemplaresdisponivel > 0) livros[idxL].status = DISPONIVEL;
    }

    int c; while ((c = getchar()) != '\n' && c != EOF) {}
    printf("Empréstimo %d devolvido com sucesso.\n", codigo);
}
// funcao responsavel pela logica de renovação do emprestimo
void renovarEmprestimo(Emprestimo emprestimos[], int qtdEmprestimos, Livro livros[], int qtdLivros) {
    int codigo;
    printf("\nDigite o código do empréstimo para renovar: ");
    if (scanf("%d", &codigo) != 1) { printf("Entrada inválida.\n"); int c; while ((c = getchar()) != '\n' && c != EOF) {} return; }

    int idx = findEmprestimoIndexByCodigo(emprestimos, qtdEmprestimos, codigo);
    if (idx == -1) { printf("Empréstimo não encontrado.\n"); return; }
    if (emprestimos[idx].status != ATIVO) { printf("Somente empréstimos ativos podem ser renovados.\n"); return; }

    time_t prevista = dataParaTimeT(emprestimos[idx].data_devolucao_prevista);
    time_t agora = time(NULL);
    if (agora > prevista) { printf("Não é possível renovar: empréstimo não está em atraso.\n"); return; }

    if (emprestimos[idx].renovacoes >= MAX_RENOVACOES) {
        printf("Número máximo de renovações atingido.\n");
        return;
    }

    emprestimos[idx].data_devolucao_prevista = adicionarDias(emprestimos[idx].data_devolucao_prevista, 7);
    emprestimos[idx].renovacoes++;
    int c; while ((c = getchar()) != '\n' && c != EOF) {}
    printf("Renovação realizada. Nova data de devolução: %02d/%02d/%04d (renovações: %d)\n",
           emprestimos[idx].data_devolucao_prevista.dia,
           emprestimos[idx].data_devolucao_prevista.mes,
           emprestimos[idx].data_devolucao_prevista.ano,
           emprestimos[idx].renovacoes);
}
//funcao responsavel para listar emprestimos ativos
void listarEmprestimosAtivos(Emprestimo emprestimos[], int qtdEmprestimos,
                             Usuario usuarios[], int qtdUsuarios, Livro livros[], int qtdLivros) {
    printf("\n=== Empréstimos Ativos ===\n");
    int encontrou = 0;
    for (int i = 0; i < qtdEmprestimos; i++) {
        if (emprestimos[i].status == ATIVO) {
            encontrou = 1;
            int idxU = findUsuarioIndex(usuarios, qtdUsuarios, emprestimos[i].matricula_usuario);
            int idxL = findLivroIndex(livros, qtdLivros, emprestimos[i].codigo_livro);
            printf("\nCod Empréstimo: %d\n", emprestimos[i].codigoemprestimo);
            if (idxU != -1) printf("Usuário: %s (Mat: %d)\n", usuarios[idxU].nomecompleto, usuarios[idxU].matricula);
            if (idxL != -1) printf("Livro: %s (Cod: %d)\n", livros[idxL].titulo, livros[idxL].codigo);
            printf("Data empréstimo: %02d/%02d/%04d\n", emprestimos[i].data_emprestimo.dia, emprestimos[i].data_emprestimo.mes, emprestimos[i].data_emprestimo.ano);
            printf("Data prevista:   %02d/%02d/%04d\n", emprestimos[i].data_devolucao_prevista.dia, emprestimos[i].data_devolucao_prevista.mes, emprestimos[i].data_devolucao_prevista.ano);
            printf("Renovações: %d\n", emprestimos[i].renovacoes);
        }
    }
    if (!encontrou) printf("Nenhum empréstimo ativo.\n");
}
// funcao para listar relatorios dos usuarios atrasados
void relatorioUsuariosAtrasados(Emprestimo emprestimos[], int qtdEmprestimos, Usuario usuarios[], int qtdUsuarios) {
    time_t agora = time(NULL);
    int encontrou = 0;
    printf("\n=== Usuários com empréstimos em atraso ===\n");
    for (int i = 0; i < qtdEmprestimos; i++) {
        if (emprestimos[i].status == ATIVO) {
            time_t prevista = dataParaTimeT(emprestimos[i].data_devolucao_prevista);
            if (agora > prevista) {
                int idxU = findUsuarioIndex(usuarios, qtdUsuarios, emprestimos[i].matricula_usuario);
                if (idxU != -1) {
                    encontrou = 1;
                    printf("- Mat: %d  Nome: %s  Empréstimo: %d  Previsto: %02d/%02d/%04d\n",
                           usuarios[idxU].matricula, usuarios[idxU].nomecompleto,
                           emprestimos[i].codigoemprestimo,
                           emprestimos[i].data_devolucao_prevista.dia,
                           emprestimos[i].data_devolucao_prevista.mes,
                           emprestimos[i].data_devolucao_prevista.ano);
                }
            }
        }
    }
    if (!encontrou) printf("Nenhum usuário com empréstimo em atraso.\n");
}

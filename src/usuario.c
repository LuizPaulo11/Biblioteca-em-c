#include <stdio.h>
#include <string.h>
#include <time.h>
#include "emprestimo.h"
// responsavel por inicializar usuario
void inicializarUsuarios(Usuario usuario[], size_t tamanho) {
    for (int i = 0; i < tamanho; i++) {
        memset(&usuario[i], 0, sizeof(Usuario));
    }
}
// duncao logica cadastro usuario
void cadastrarUsuario(Usuario usuarios[], size_t *qtdUsuarios, size_t maxUsuarios) {
    if (*qtdUsuarios >= maxUsuarios) {
        printf("Não é possível cadastrar mais usuários (limite atingido).\n");
        return;
    }

    Usuario *u = &usuarios[*qtdUsuarios];

    printf("\n=== Cadastro de Usuário ===\n");
    printf("Matrícula: ");
    if (scanf("%d", &u->matricula) != 1) {
        printf("Entrada inválida.\n");
        int c; while ((c = getchar()) != '\n' && c != EOF) {}
        return;
    }
    getchar();

    printf("Nome completo: ");
    fgets(u->nomecompleto, sizeof(u->nomecompleto), stdin);
    u->nomecompleto[strcspn(u->nomecompleto, "\n")] = '\0';

    printf("Curso: ");
    fgets(u->curso, sizeof(u->curso), stdin);
    u->curso[strcspn(u->curso, "\n")] = '\0';

    printf("Telefone: ");
    fgets(u->telefone, sizeof(u->telefone), stdin);
    u->telefone[strcspn(u->telefone, "\n")] = '\0';

    printf("Data cadastro (dia mes ano): ");
    if (scanf("%d %d %d", &u->data_cadastro.dia, &u->data_cadastro.mes, &u->data_cadastro.ano) != 3) {
        printf("Data inválida, preenchendo zeros.\n");
        u->data_cadastro.dia = u->data_cadastro.mes = u->data_cadastro.ano = 0;
    }
    int c; while ((c = getchar()) != '\n' && c != EOF) {}

    (*qtdUsuarios)++;
    printf("Usuário cadastrado com sucesso!\n");
}
//funcao logica para pesquisar usuario por matricula
void pesquisarUsuarioPorMatricula(const Usuario usuarios[], size_t qtdUsuarios, int matricula) {
    for (size_t i = 0; i < qtdUsuarios; i++) {
        if (usuarios[i].matricula == matricula) {
            printf("\nUsuário encontrado:\n");
            printf("Matrícula: %d\n", usuarios[i].matricula);
            printf("Nome: %s\n", usuarios[i].nomecompleto);
            printf("Curso: %s\n", usuarios[i].curso);
            printf("Telefone: %s\n", usuarios[i].telefone);
            printf("Data cadastro: %02d/%02d/%04d\n",
                   usuarios[i].data_cadastro.dia,
                   usuarios[i].data_cadastro.mes,
                   usuarios[i].data_cadastro.ano);
            return;
        }
    }
    printf("Usuário com matrícula %d não encontrado.\n", matricula);
}
// funcao com logica para pesquisar usuario por nome
void pesquisarUsuarioPorNome(const Usuario usuarios[], size_t qtdUsuarios, const char *nome) {
    int achou = 0;
    for (size_t i = 0; i < qtdUsuarios; i++) {
        if (strstr(usuarios[i].nomecompleto, nome) != NULL) {
            if (!achou) { printf("\nResultados da pesquisa por nome:\n"); achou = 1; }
            printf("- Mat.: %d  Nome: %s\n", usuarios[i].matricula, usuarios[i].nomecompleto);
        }
    }
    if (!achou) printf("Nenhum usuário encontrado contendo '%s'.\n", nome);
}
// funcao com logica do menu
void pesquisarUsuarioMenu(const Usuario usuarios[], size_t qtdUsuarios) {
    int op;
    printf("\nPesquisar usuário por:\n1 - Matrícula\n2 - Nome\nEscolha: ");
    if (scanf("%d", &op) != 1) { int c; while ((c = getchar()) != '\n' && c != EOF) {} printf("Entrada inválida.\n"); return; }
    int c; while ((c = getchar()) != '\n' && c != EOF) {}

    if (op == 1) {
        int mat; printf("Digite a matrícula: ");
        if (scanf("%d", &mat) != 1) { printf("Entrada inválida.\n"); while ((c = getchar()) != '\n' && c != EOF) {} return; }
        pesquisarUsuarioPorMatricula(usuarios, qtdUsuarios, mat);
        while ((c = getchar()) != '\n' && c != EOF) {}
    } else if (op == 2) {
        char nome[101];
        printf("Digite parte do nome: ");
        fgets(nome, sizeof(nome), stdin); nome[strcspn(nome, "\n")] = '\0';
        pesquisarUsuarioPorNome(usuarios, qtdUsuarios, nome);
    } else {
        printf("Opção inválida.\n");
    }
}






#ifndef USUARIO_H
#define USUARIO_H

#include <stddef.h>

typedef struct Data {
    int dia;
    int mes;
    int ano;
} Data;

typedef struct Usuario {
    int matricula;
    char nomecompleto[101];
    char curso[51];
    char telefone[16];
    Data data_cadastro;
} Usuario;

void inicializarUsuarios(Usuario usuarios[], size_t tamanho);

void cadastrarUsuario(Usuario usuarios[], size_t *qtdUsuarios, size_t maxUsuarios);
void pesquisarUsuarioPorMatricula(const Usuario usuarios[], size_t qtdUsuarios, int matricula);
void pesquisarUsuarioPorNome(const Usuario usuarios[], size_t qtdUsuarios, const char *nome);

void pesquisarUsuarioMenu(const Usuario usuarios[], size_t qtdUsuarios);

#endif
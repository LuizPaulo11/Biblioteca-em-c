#include <string.h>
#include "usuario.h"

void inicializarUsuarios(Usuario usuario[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        memset(&usuario[i], 0, sizeof(Usuario));
    }
}








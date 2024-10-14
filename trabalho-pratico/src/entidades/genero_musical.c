#include <stdio.h>
#include <string.h>
#include <glib.h>
#include <stdlib.h>

#include "entidades/genero_musical.h"

struct genero_musical {
    char *nome;
    int likes;
};

GENERO_MUSICAL criar_genero_musical() {
    GENERO_MUSICAL novo_genero = malloc(sizeof(struct genero_musical));
    novo_genero->nome = NULL;
    novo_genero->likes = 0;
    return novo_genero;
}

char* getGeneroNome(GENERO_MUSICAL genero) {
    return strdup(genero->nome);
}

int getGeneroLikes(GENERO_MUSICAL genero) {
    return genero->likes;
}

void setGeneroNome(GENERO_MUSICAL genero, char *nome) {
    free(genero->nome);
    genero->nome = strdup(nome);
}

void setGeneroLikes(GENERO_MUSICAL genero, int likes) {
    genero->likes = likes;
}

void free_genero_musical(GENERO_MUSICAL genero) {
    if (genero != NULL) {
        free(genero->nome);
        free(genero);
    }
}
#ifndef GENERO_MUSICAL_H
#define GENERO_MUSICAL_H

typedef struct genero_musical *GENERO_MUSICAL;

GENERO_MUSICAL criar_genero_musical(void);

// Getters
char* getGeneroNome(GENERO_MUSICAL genero);
int getGeneroLikes(GENERO_MUSICAL genero);

// Setters
void setGeneroNome(GENERO_MUSICAL genero, char *nome);
void setGeneroLikes(GENERO_MUSICAL genero, int likes);

void free_genero_musical(GENERO_MUSICAL genero);

#endif

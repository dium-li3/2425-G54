#ifndef CATALOGO_MUSICS_H
#define CATALOGO_MUSICS_H

#include <glib.h>
#include "entidades/musics.h"

typedef struct musics_catalog *MUSICS_CATALOG;

typedef struct artists_catalog *ARTISTS_CATALOG;

typedef struct music *MUSIC;

MUSICS_CATALOG create_musics_catalog();

void insert_music(MUSICS_CATALOG catalogo, MUSIC music, char *key);

void inserir_musica_catalogo(GArray *parameters_array, MUSICS_CATALOG catalogo_musics, ARTISTS_CATALOG catalogo_artists);

MUSIC get_music_by_key(MUSICS_CATALOG catalogo, char *key);

void update_music(MUSICS_CATALOG catalogo, char *key, MUSIC music);

void free_musics_catalog(MUSICS_CATALOG catalogo);

#endif
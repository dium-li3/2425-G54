#ifndef CATALOGO_ARTISTS_H
#define CATALOGO_ARTISTS_H

#include <glib.h>
#include <entidades/artists.h>
#include "manager_dados/utils.h"

typedef struct artists_catalog *ARTISTS_CATALOG;

typedef struct artist *ARTIST;

ARTISTS_CATALOG create_artists_catalog();

void inserir_artist_catalogo(GArray *parameters_array, ARTISTS_CATALOG catalogo_artists, STATS *stats);

void insert_artist(ARTISTS_CATALOG catalogo, ARTIST artist, char *key);

ARTIST get_artist_by_key(ARTISTS_CATALOG catalogo, char *key);

void update_artist(ARTISTS_CATALOG catalogo, char *key, ARTIST artist);

void free_artists_catalog(ARTISTS_CATALOG catalogo);
#endif
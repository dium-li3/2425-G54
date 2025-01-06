#ifndef CATALOGO_ALBUMS_H
#define CATALOGO_ALBUMS_H

#include <glib.h>
#include "entidades/albums.h"
#include "catalogos/catalogo_artists.h"

typedef struct albums_catalog *ALBUMS_CATALOG;

// Create an albums catalog
ALBUMS_CATALOG create_albums_catalog();

// Insert an album into the catalog
void inserir_album_catalogo(GArray *parameters_array, ALBUMS_CATALOG catalogo_albums, ARTISTS_CATALOG catalogo_artists);

void insert_album(ALBUMS_CATALOG catalogo, ALBUM album, char *key);

// Retrieve an album by its key
ALBUM get_album_by_key(ALBUMS_CATALOG catalogo, char *key);

// Update an album in the catalog
void update_album(ALBUMS_CATALOG catalogo, char *key, ALBUM album);

// Free the albums catalog
void free_albums_catalog(ALBUMS_CATALOG catalogo);

#endif

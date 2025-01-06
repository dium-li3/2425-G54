#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "catalogos/catalogo_albums.h"
#include "entidades/albums.h"
#include "entidades/artists.h"

struct albums_catalog {
    GHashTable *albums;
};

// Create the albums catalog
ALBUMS_CATALOG create_albums_catalog() {
    ALBUMS_CATALOG new_catalog = malloc(sizeof(struct albums_catalog));
    new_catalog->albums = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, (GDestroyNotify)free_album);
    return new_catalog;
}

// Insert an album into the catalog
void inserir_album_catalogo(GArray *parameters_array, ALBUMS_CATALOG catalogo_albums, ARTISTS_CATALOG catalogo_artists) {
    char *id = g_array_index(parameters_array, char *, 0);
    char *artists_id = g_array_index(parameters_array, char *, 2);
    char *year_str = g_array_index(parameters_array, char *, 3);

    int year = atoi(year_str);

    ALBUM album = create_album();

    set_album_id(album, id);
    set_album_artists_ids(album, artists_id);
    set_album_year(album, year);

    insert_album(catalogo_albums, album, id);

    updateIndividualAlbums(album,catalogo_artists);
}

// Insert an album into the hash table
void insert_album(ALBUMS_CATALOG catalogo, ALBUM album, char *key) {
    char *key_dup = strdup(key);
    g_hash_table_insert(catalogo->albums, key_dup, album);
}

// Retrieve an album by its key
ALBUM get_album_by_key(ALBUMS_CATALOG catalogo, char *key) {
    return g_hash_table_lookup(catalogo->albums, key);
}

// Update an album in the catalog
void update_album(ALBUMS_CATALOG catalogo, char *key, ALBUM album) {
    g_hash_table_replace(catalogo->albums, key, album);
}

// Free the albums catalog
void free_albums_catalog(ALBUMS_CATALOG catalogo) {
    g_hash_table_destroy(catalogo->albums);
    free(catalogo);
}

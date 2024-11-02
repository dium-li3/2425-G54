#include <glib.h>

#include "entidades/artists.h"
#include "entidades/stats.h"

#include "catalogos/catalogo_artists.h"

#include "manager_dados/utils.h"

struct artists_catalog
{
    GHashTable *artists;
};

// GHashTable for Artists creation   ///////////////////////////////////

ARTISTS_CATALOG create_artists_catalog()
{
    ARTISTS_CATALOG new_catalog = malloc(sizeof(struct artists_catalog));
    new_catalog->artists = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, (GDestroyNotify)destroi_artists);
    return new_catalog;
}

// Insert User in Catalog    //////////////////////////////////////////

void inserir_artist_catalogo(GArray *parameters_array, ARTISTS_CATALOG catalogo_artists, STATS *stats)
{
    char *id = g_array_index(parameters_array, char *, 0);
    char *name = g_array_index(parameters_array, char *, 1);
    char *description = g_array_index(parameters_array, char *, 2);
    char *recipe_per_stream = g_array_index(parameters_array, char *, 3);
    char *id_constituent = g_array_index(parameters_array, char *, 4);
    char *country = g_array_index(parameters_array, char *, 5);
    char *type = g_array_index(parameters_array, char *, 6);

    ARTIST artist = criar_artist();

    setArtistId(artist, id);
    setArtistName(artist, name);
    setArtistDescription(artist, description);
    setRecipePerStream(artist, recipe_per_stream);
    setIdConstituent(artist, id_constituent);
    setArtistCountry(artist, country);
    setArtistType(artist, type);

    insert_artist(catalogo_artists, artist, id);

    add_artist_to_stats(stats,artist);
}

// GHashTable Help Functions /////////////////////////////////////////

void insert_artist(ARTISTS_CATALOG catalogo, ARTIST artist, char *key) 
{
  char *key_dup = strdup(key);
  g_hash_table_insert(catalogo->artists, key_dup, GINT_TO_POINTER(artist));
}

ARTIST get_artist_by_key(ARTISTS_CATALOG catalogo, char *key) 
{
  return g_hash_table_lookup(catalogo->artists, key);
}

void update_artist(ARTISTS_CATALOG catalogo, char *key, ARTIST artist)
{
  g_hash_table_replace (catalogo->artists,key,GINT_TO_POINTER(artist));
}

void free_artists_catalog(ARTISTS_CATALOG catalogo) 
{
  g_hash_table_destroy(catalogo->artists);
  free(catalogo);
}
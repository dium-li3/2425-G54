#include <glib.h>

#include "entidades/musics.h"
#include "catalogos/catalogo_musics.h"

#include "manager_dados/utils.h"

struct musics_catalog
{
    GHashTable *musics;
};

// GHashTable for musics creation   ////////////////////////////////////

MUSICS_CATALOG create_musics_catalog()
{
    MUSICS_CATALOG new_catalog = malloc(sizeof(struct musics_catalog));
    new_catalog->musics = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, (GDestroyNotify)destroi_musics);
    return new_catalog;
}

// Insert Music in Catalog    ////////////////////////////////////////

void inserir_musica_catalogo(GArray *parameters_array, MUSICS_CATALOG catalogo_musics, ARTISTS_CATALOG catalogo_artists)
{
    char *id = g_array_index(parameters_array, char *, 0);                                       
    char *artist_ids = g_array_index(parameters_array, char *, 2);    
    char *album_id = g_array_index(parameters_array, char *, 3);                 
    char *duration = g_array_index(parameters_array, char *, 4);      
    char *genre = g_array_index(parameters_array, char *, 5);                    
    char *year = g_array_index(parameters_array, char *, 6);                                      

    MUSIC music = criar_music();

    setId(music,id);
    setArtistIds(music,artist_ids);
    setAlbumId(music,album_id);
    setDuration(music,duration);
    setGenre(music,genre);
    setYear(music,atoi(year));

    insert_music(catalogo_musics, music, id);

    update_DiscographyTime(catalogo_artists, music);
}

// GHashTable Help Functions /////////////////////////////////////////

void insert_music(MUSICS_CATALOG catalogo, MUSIC music, char *key) 
{
  char *key_dup = strdup(key);
  g_hash_table_insert(catalogo->musics, key_dup, GINT_TO_POINTER(music));
}

MUSIC get_music_by_key(MUSICS_CATALOG catalogo, char *key) 
{
  return g_hash_table_lookup(catalogo->musics, key);
}

void update_music(MUSICS_CATALOG catalogo, char *key, MUSIC music)
{
  g_hash_table_replace (catalogo->musics,key,GINT_TO_POINTER(music));
}

void free_musics_catalog(MUSICS_CATALOG catalogo) 
{
  g_hash_table_destroy(catalogo->musics);
  free(catalogo);
}
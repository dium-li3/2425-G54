#include <glib.h>

#include "entidades/users.h"
#include "catalogos/catalogo_users.h"

#include "manager_dados/utils.h"

struct users_catalog
{
    GHashTable *users;
};

// GHashTable for users creation   /////////////////////////////////////

USERS_CATALOG create_users_catalog()
{
    USERS_CATALOG new_catalog = malloc(sizeof(struct users_catalog));
    new_catalog->users = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, (GDestroyNotify)destroi_users);
    return new_catalog;
}

// Insert User in Catalog    //////////////////////////////////////////

void inserir_user_catalogo(GArray *parameters_array, USERS_CATALOG catalogo_users, MUSICS_CATALOG catalogo_musics, STATS *stats)
{
    char *username = g_array_index(parameters_array, char *, 0);
    char *email = g_array_index(parameters_array, char *, 1);
    char *first_name = g_array_index(parameters_array, char *, 2);
    char *last_name = g_array_index(parameters_array, char *, 3);
    char *birth_date = g_array_index(parameters_array, char *, 4);
    char *country = g_array_index(parameters_array, char *, 5);
    char *liked_musics = g_array_index(parameters_array, char *, 7);

    USER user = criar_user();

    setUsername(user, username);
    setEmail(user, email);
    setFirstName(user, first_name);
    setLastName(user, last_name);
    setAge(user, birth_date);
    setCountry(user, country);
    setLikedMusics(user, liked_musics);

    insert_user(catalogo_users, user, username);

    update_statistics_for_genre(stats,catalogo_musics,user);
}

// GHashTable Help Functions /////////////////////////////////////////

void insert_user(USERS_CATALOG catalogo, USER user, char *key) 
{
  char *key_dup = strdup(key);
  g_hash_table_insert(catalogo->users, key_dup, GINT_TO_POINTER(user));
}

USER get_user_by_key(USERS_CATALOG catalogo, char *key) 
{
  return g_hash_table_lookup(catalogo->users, key);
}

void update_user(USERS_CATALOG catalogo, char *key, USER user)
{
  g_hash_table_replace (catalogo->users,key,GINT_TO_POINTER(user));
}

void free_user_catalog(USERS_CATALOG catalogo) 
{
  g_hash_table_destroy(catalogo->users);
  free(catalogo);
}
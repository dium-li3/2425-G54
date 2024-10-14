#ifndef CATALOGO_USERS_H
#define CATALOGO_USERS_H

#include <glib.h>
#include "entidades/users.h"

typedef struct users_catalog *USERS_CATALOG;

typedef struct musics_catalog *MUSICS_CATALOG;

typedef struct user *USER; 

typedef struct stats STATS;

USERS_CATALOG create_users_catalog();

void inserir_user_catalogo(GArray *parameters_array, USERS_CATALOG catalogo_users, MUSICS_CATALOG catalogo_musics, STATS *stats);

void insert_user(USERS_CATALOG catalogo, USER user, char *key);

USER get_user_by_key(USERS_CATALOG catalogo, char *key);

void update_user(USERS_CATALOG catalogo, char *key, USER user);

void free_user_catalog(USERS_CATALOG catalogo);

#endif
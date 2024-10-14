#ifndef VALIDATION_UTILS_H
#define VALIDATION_UTILS_H

#include <glib.h>

#include "entidades/musics.h"   
#include "entidades/users.h"
#include "entidades/artists.h"
#include "entidades/stats.h"

#include "catalogos/catalogo_musics.h"
#include "catalogos/catalogo_artists.h"
#include "catalogos/catalogo_users.h"

#include "manager_dados/utils.h"

int data_valida(char *data);

int duracao_valida(char *duracao);

int caracter_valido(char c);

int dominio_valido(char *part);

int verifica_email(char *email);

int verifa_if_is_list(char *id_artists);

int verifica_subscription_type(char *s_type);

int verifica_liked_musics(char *liked_musics, MUSICS_CATALOG catalogo_musics);

int verifica_music_artist(char *artists_id, ARTISTS_CATALOG catalogo_artists);

int verifica_artista_ou_banda(char *id_constituent, char *artist_type);

int valid_entity(int flag,GArray *parameters_array,ARTISTS_CATALOG catalogo_artists,MUSICS_CATALOG catalogo_musics);

#endif
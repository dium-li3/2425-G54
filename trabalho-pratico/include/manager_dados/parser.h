#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <glib.h>

#include "entidades/musics.h"   
#include "entidades/users.h"
#include "entidades/artists.h"
#include "entidades/albums.h"
#include "entidades/stats.h"

#include "catalogos/catalogo_musics.h"
#include "catalogos/catalogo_artists.h"
#include "catalogos/catalogo_users.h"
#include "catalogos/catalogo_albums.h"

#include "manager_dados/parser.h"
#include "manager_dados/querier.h"
#include "manager_dados/validation.h"
#include "manager_dados/utils.h"

char *get_error_file_path(int flag);

FILE *get_file_by_flag(int flag, FILE *artists_file, FILE *albums_file, FILE *musics_file, FILE *users_file, FILE *history_file);

void insert_catalogo(int flag,GArray *parameters_array,ARTISTS_CATALOG artists, ALBUMS_CATALOG albums, MUSICS_CATALOG musics, USERS_CATALOG users, STATS *stats);

void parser(ARTISTS_CATALOG artists, MUSICS_CATALOG musics, USERS_CATALOG users, ALBUMS_CATALOG albums, STATS *stats, FILE *artists_file, FILE *musics_file, FILE *users_file, FILE *history_file, FILE *albums_file);

#endif
#ifndef QUERIER_H
#define QUERIER_H

#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "entidades/musics.h"   
#include "entidades/users.h"
#include "entidades/artists.h"
#include "entidades/stats.h"

#include "catalogos/catalogo_musics.h"
#include "catalogos/catalogo_artists.h"
#include "catalogos/catalogo_users.h"

#include "manager_dados/utils.h"
#include "manager_dados/querier.h"

#include "queries/query1.h"

void querier(ARTISTS_CATALOG artists, MUSICS_CATALOG musics, USERS_CATALOG users, STATS *stats, FILE *input);

void exec_line(ARTISTS_CATALOG artists, MUSICS_CATALOG musics, USERS_CATALOG users, STATS *stats, char *linha, int count);

#endif 

#ifndef QUERY1_H
#define QUERY1_H

#include "entidades/musics.h"   
#include "entidades/users.h"
#include "entidades/artists.h"
#include "entidades/stats.h"

#include "catalogos/catalogo_musics.h"
#include "catalogos/catalogo_artists.h"
#include "catalogos/catalogo_users.h"

#include "manager_dados/utils.h"

void execute_query1(int numlinha, char *arg, int output_flag, USERS_CATALOG users, ARTISTS_CATALOG artists);

#endif
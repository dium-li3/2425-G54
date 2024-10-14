#ifndef EXEC_BATCH_MODE_H
#define EXEC_BATCH_MODE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>

#include "entidades/musics.h"   
#include "entidades/users.h"
#include "entidades/artists.h"
#include "entidades/stats.h"

#include "catalogos/catalogo_musics.h"
#include "catalogos/catalogo_artists.h"
#include "catalogos/catalogo_users.h"

#include "manager_dados/utils.h"
#include "manager_dados/querier.h"
#include "manager_dados/parser.h"
#include "manager_dados/validation.h"

#include "modos_execucao/programa-principal.h"

void exec_programa_principal(char* path, char* comandos);

#endif
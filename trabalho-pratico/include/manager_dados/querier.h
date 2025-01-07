/**
 * @file querier.h
 * @brief Ficheiro de cabeçalho para o módulo de processamento de queries.
 *
 * Este ficheiro define as funções necessárias para a execução de queries
 * sobre os diferentes catálogos e estruturas de dados da aplicação.
 */

#ifndef QUERIER_H
#define QUERIER_H

#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "entidades/musics.h"   
#include "entidades/users.h"
#include "entidades/artists.h"
#include "entidades/albums.h"
#include "entidades/stats.h"

#include "catalogos/catalogo_musics.h"
#include "catalogos/catalogo_artists.h"
#include "catalogos/catalogo_users.h"
#include "catalogos/catalogo_albums.h"

#include "manager_dados/utils.h"
#include "manager_dados/querier.h"

#include "queries/query1.h"

/**
 * @brief Processa todas as queries a partir de um ficheiro de entrada.
 *
 * Lê cada linha do ficheiro de entrada, identifica a query correspondente,
 * e chama as funções necessárias para a execução da mesma.
 *
 * @param artists Catálogo de artistas.
 * @param musics Catálogo de músicas.
 * @param users Catálogo de utilizadores.
 * @param albums Catálogo de álbuns.
 * @param stats Estrutura de estatísticas.
 * @param input Ficheiro de entrada contendo as queries.
 */
void querier(ARTISTS_CATALOG artists, MUSICS_CATALOG musics, USERS_CATALOG users, ALBUMS_CATALOG albums, STATS *stats, FILE *input);

/**
 * @brief Processa uma linha específica de uma query.
 *
 * Divide a linha da query em seus componentes, identifica o tipo de query,
 * e executa a função correspondente para o processamento da mesma.
 *
 * @param artists Catálogo de artistas.
 * @param musics Catálogo de músicas.
 * @param users Catálogo de utilizadores.
 * @param albums Catálogo de álbuns.
 * @param stats Estrutura de estatísticas.
 * @param linha Linha contendo a query.
 * @param count Número da linha sendo processada.
 */
void exec_line(ARTISTS_CATALOG artists, MUSICS_CATALOG musics, USERS_CATALOG users, ALBUMS_CATALOG albums, STATS *stats, char *linha, int count);

#endif


/**
 * @file query1.h
 * @brief Declarações da Query 1.
 *
 * Este ficheiro contém a declaração da função utilizada para executar a Query 1.
 */

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

/**
 * @brief Executa a Query 1.
 *
 * A Query 1 permite obter informações sobre um utilizador ou um artista
 * com base no ID fornecido. Os dados obtidos são escritos num formato
 * definido, dependendo do parâmetro `output_flag`.
 *
 * @param numlinha Número da linha em que a query será processada.
 * @param arg Argumento que contém o ID do utilizador ou artista.
 * @param output_flag Sinaliza o formato de saída (1 para formato detalhado, 2 para sumarizado).
 * @param users Catálogo de utilizadores.
 * @param artists Catálogo de artistas.
 */
void execute_query1(int numlinha, char *arg, int output_flag, USERS_CATALOG users, ARTISTS_CATALOG artists);

#endif

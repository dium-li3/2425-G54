/**
 * @file query2.h
 * @brief Interface para a execução da Query 2.
 *
 * Este ficheiro contém a definição da função necessária para a execução
 * da Query 2, que utiliza as estatísticas armazenadas para processar
 * e gerar os resultados solicitados.
 */

#ifndef QUERY2_H
#define QUERY2_H

#include <stdio.h>
#include <string.h>
#include <glib.h>
#include <stdlib.h>

#include "entidades/musics.h"
#include "entidades/users.h"
#include "entidades/artists.h"
#include "entidades/stats.h"

#include "catalogos/catalogo_musics.h"
#include "catalogos/catalogo_artists.h"
#include "catalogos/catalogo_users.h"

#include "manager_dados/utils.h"

/**
 * @brief Executa a Query 2.
 *
 * Esta função processa a Query 2, recebendo os argumentos necessários e utilizando
 * as estatísticas acumuladas no programa. Gera os resultados e escreve-os no
 * formato especificado pelo utilizador.
 *
 * @param numlinha Número da linha correspondente ao comando no ficheiro de entrada.
 * @param flag Indicador de formato de saída (1 para detalhado, 2 para resumido).
 * @param arg Argumentos passados para a execução da query.
 * @param stats Estrutura que contém as estatísticas a serem utilizadas.
 */
void execute_query2(int numlinha, int flag, char *arg, STATS *stats);

#endif

/**
 * @file query3.h
 * @brief Declarações de funções relacionadas com a execução da Query 3.
 *
 * Este ficheiro contém a declaração das funções necessárias para processar e executar
 * a Query 3, que calcula e apresenta os géneros musicais mais populares numa faixa etária
 * específica, baseada nas estatísticas recolhidas.
 */

#ifndef QUERY3_H
#define QUERY3_H

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
 * @brief Executa a Query 3.
 *
 * Calcula os géneros musicais mais populares dentro de uma faixa etária
 * fornecida e apresenta os resultados num formato específico.
 *
 * @param numlinha Número da linha de entrada para identificação dos resultados.
 * @param flag Formato de saída desejado (e.g., detalhado ou compacto).
 * @param arg Argumentos da Query (e.g., faixa etária como "min_age max_age").
 * @param stats Estrutura de estatísticas contendo os dados a serem processados.
 */
void execute_query3(int numlinha, int flag, char *arg, STATS *stats);

#endif

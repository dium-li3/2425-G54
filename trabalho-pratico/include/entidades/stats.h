/**
 * @file stats.h
 * @brief Ficheiro de interface para o módulo de estatísticas.
 *
 * Este ficheiro contém a definição de funções e estruturas utilizadas
 * para gerir as estatísticas no sistema, incluindo manipulação de dados
 * relacionados com artistas, géneros e idade dos utilizadores.
 */

#ifndef STATISTICS_H
#define STATISTICS_H

#include <glib.h>
#include <stdio.h>
#include <string.h>
#include <glib.h>
#include <stdlib.h>

/**
 * @brief Estrutura opaca para as estatísticas.
 *
 * Esta estrutura encapsula os detalhes de implementação das estatísticas,
 * armazenando informações sobre artistas, géneros e idades.
 */
typedef struct stats STATS;

/**
 * @brief Estrutura opaca para um artista.
 */
typedef struct artist *ARTIST;

/**
 * @brief Cria uma nova estrutura de estatísticas.
 *
 * Aloca memória e inicializa as tabelas e arrays necessários para as estatísticas.
 *
 * @return Um ponteiro para a nova estrutura de estatísticas.
 */
STATS* create_statistics(void);

/**
 * @brief Liberta a memória alocada para as estatísticas.
 *
 * Remove todos os dados associados às estatísticas e liberta os recursos
 * alocados.
 *
 * @param stats Ponteiro para a estrutura de estatísticas a ser libertada.
 */
void free_statistics(STATS *stats);

/**
 * @brief Obtém a tabela de géneros por faixas etárias.
 *
 * Retorna uma tabela hash que relaciona géneros com tabelas de idades e
 * respetivos contadores de likes.
 *
 * @param stats Ponteiro para a estrutura de estatísticas.
 * @return Tabela hash dos géneros por faixas etárias.
 */
GHashTable* get_genre_age_table(STATS *stats);

/**
 * @brief Obtém o array de artistas.
 *
 * Retorna um array que contém informações sobre os artistas.
 *
 * @param stats Ponteiro para a estrutura de estatísticas.
 * @return Array de artistas.
 */
GArray* get_artists_array(STATS *stats);

/**
 * @brief Adiciona um artista às estatísticas.
 *
 * Insere um artista no array de artistas da estrutura de estatísticas.
 *
 * @param stats Ponteiro para a estrutura de estatísticas.
 * @param artist Ponteiro para o artista a ser adicionado.
 */
void add_artist_to_stats(STATS *stats, ARTIST artist);

/**
 * @brief Incrementa os likes de um género para uma faixa etária.
 *
 * Atualiza o contador de likes para um género específico baseado na idade
 * do utilizador.
 *
 * @param stats Ponteiro para a estrutura de estatísticas.
 * @param user_age Idade do utilizador.
 * @param genre Nome do género.
 */
void increment_likes_for_genre(STATS *stats, int user_age, char *genre);

/**
 * @brief Obtém géneros mais populares numa faixa etária.
 *
 * Retorna uma lista de géneros musicais mais populares para a faixa etária
 * especificada.
 *
 * @param stats Ponteiro para a estrutura de estatísticas.
 * @param min_age Idade mínima da faixa.
 * @param max_age Idade máxima da faixa.
 * @return Array de géneros musicais dentro da faixa etária.
 */
GArray *get_genres_by_age_range(STATS *stats, int min_age, int max_age);

#endif

/**
 * @file catalogo_artists.h
 * @brief Ficheiro de interface para a gestão do catálogo de artistas.
 *
 * Este ficheiro contém as definições das funções e estruturas necessárias para a
 * manipulação do catálogo de artistas na aplicação.
 */

#ifndef CATALOGO_ARTISTS_H
#define CATALOGO_ARTISTS_H

#include <glib.h>
#include <entidades/artists.h>
#include <entidades/stats.h>
#include "manager_dados/utils.h"

/**
 * @typedef ARTISTS_CATALOG
 * Estrutura opaca que representa o catálogo de artistas.
 */
typedef struct artists_catalog *ARTISTS_CATALOG;

/**
 * @typedef ARTIST
 * Estrutura que representa um artista.
 */
typedef struct artist *ARTIST;

/**
 * @brief Cria e inicializa um novo catálogo de artistas.
 * 
 * @return Um ponteiro para o catálogo de artistas recém-criado.
 */
ARTISTS_CATALOG create_artists_catalog();

/**
 * @brief Insere um artista no catálogo a partir de um array de parâmetros.
 *
 * @param parameters_array Array contendo os parâmetros necessários para criar o artista.
 * @param catalogo_artists Ponteiro para o catálogo onde o artista será inserido.
 * @param stats Estrutura de estatísticas para atualização durante a inserção.
 */
void inserir_artist_catalogo(GArray *parameters_array, ARTISTS_CATALOG catalogo_artists, STATS *stats);

/**
 * @brief Insere diretamente um artista no catálogo.
 *
 * @param catalogo Ponteiro para o catálogo onde o artista será inserido.
 * @param artist Ponteiro para o artista a ser inserido.
 * @param key Chave identificadora do artista no catálogo.
 */
void insert_artist(ARTISTS_CATALOG catalogo, ARTIST artist, char *key);

/**
 * @brief Obtém um artista do catálogo a partir de uma chave.
 *
 * @param catalogo Ponteiro para o catálogo de artistas.
 * @param key Chave identificadora do artista.
 * @return Um ponteiro para o artista correspondente à chave, ou NULL se não encontrado.
 */
ARTIST get_artist_by_key(ARTISTS_CATALOG catalogo, char *key);

/**
 * @brief Atualiza um artista no catálogo.
 *
 * @param catalogo Ponteiro para o catálogo de artistas.
 * @param key Chave identificadora do artista.
 * @param artist Ponteiro para o artista atualizado.
 */
void update_artist(ARTISTS_CATALOG catalogo, char *key, ARTIST artist);

/**
 * @brief Libera a memória associada ao catálogo de artistas.
 *
 * @param catalogo Ponteiro para o catálogo de artistas a ser destruído.
 */
void free_artists_catalog(ARTISTS_CATALOG catalogo);

#endif

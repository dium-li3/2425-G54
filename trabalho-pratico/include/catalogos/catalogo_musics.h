/**
 * @file catalogo_musics.h
 * @brief Ficheiro de cabeçalho para a gestão do catálogo de músicas.
 *
 * Este ficheiro contém a definição de funções e estruturas utilizadas para
 * gerir o catálogo de músicas, incluindo inserção, recuperação, atualização
 * e gestão de memória.
 */

#ifndef CATALOGO_MUSICS_H
#define CATALOGO_MUSICS_H

#include <glib.h>
#include "entidades/musics.h"

/**
 * @brief Estrutura opaca para o catálogo de músicas.
 *
 * Esta estrutura encapsula os detalhes de implementação do catálogo de músicas.
 */
typedef struct musics_catalog *MUSICS_CATALOG;

/**
 * @brief Estrutura opaca para o catálogo de artistas.
 */
typedef struct artists_catalog *ARTISTS_CATALOG;

/**
 * @brief Estrutura opaca para uma música.
 */
typedef struct music *MUSIC;

/**
 * @brief Cria um novo catálogo de músicas.
 *
 * Aloca memória e inicializa um catálogo vazio para armazenar músicas.
 *
 * @return Um ponteiro para o catálogo de músicas recém-criado.
 */
MUSICS_CATALOG create_musics_catalog();

/**
 * @brief Insere uma música no catálogo.
 *
 * Insere uma nova música no catálogo associando-a à chave fornecida.
 *
 * @param catalogo Ponteiro para o catálogo de músicas.
 * @param music Ponteiro para a música a ser inserida.
 * @param key Chave a ser associada à música.
 */
void insert_music(MUSICS_CATALOG catalogo, MUSIC music, char *key);

/**
 * @brief Insere uma música no catálogo a partir de um conjunto de parâmetros.
 *
 * Insere uma nova música no catálogo utilizando os parâmetros fornecidos no
 * array de parâmetros e atualiza informações relacionadas ao catálogo de artistas.
 *
 * @param parameters_array Array contendo os detalhes da música.
 * @param catalogo_musics Ponteiro para o catálogo de músicas.
 * @param catalogo_artists Ponteiro para o catálogo de artistas para referência cruzada.
 */
void inserir_musica_catalogo(GArray *parameters_array, MUSICS_CATALOG catalogo_musics, ARTISTS_CATALOG catalogo_artists);

/**
 * @brief Recupera uma música pela sua chave.
 *
 * Pesquisa no catálogo a música associada à chave fornecida.
 *
 * @param catalogo Ponteiro para o catálogo de músicas.
 * @param key Chave da música a ser recuperada.
 * @return Ponteiro para a música associada à chave ou NULL se não encontrada.
 */
MUSIC get_music_by_key(MUSICS_CATALOG catalogo, char *key);

/**
 * @brief Atualiza uma música existente no catálogo.
 *
 * Substitui a música associada à chave fornecida pela música fornecida.
 *
 * @param catalogo Ponteiro para o catálogo de músicas.
 * @param key Chave da música a ser atualizada.
 * @param music Ponteiro para a nova música.
 */
void update_music(MUSICS_CATALOG catalogo, char *key, MUSIC music);

/**
 * @brief Libera a memória alocada para o catálogo de músicas.
 *
 * Libera todos os recursos utilizados pelo catálogo de músicas, incluindo as músicas armazenadas.
 *
 * @param catalogo Ponteiro para o catálogo de músicas a ser liberado.
 */
void free_musics_catalog(MUSICS_CATALOG catalogo);

#endif

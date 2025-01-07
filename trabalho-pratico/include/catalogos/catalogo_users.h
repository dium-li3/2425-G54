/**
 * @file catalogo_users.h
 * @brief Ficheiro de cabeçalho para gestão do catálogo de utilizadores.
 *
 * Este ficheiro contém a definição das funções e estruturas utilizadas
 * para gerir o catálogo de utilizadores, incluindo inserção, recuperação,
 * atualização e gestão de memória.
 */

#ifndef CATALOGO_USERS_H
#define CATALOGO_USERS_H

#include <glib.h>
#include "entidades/users.h"

/**
 * @brief Estrutura opaca para o catálogo de utilizadores.
 *
 * Esta estrutura encapsula os detalhes de implementação do catálogo de utilizadores.
 */
typedef struct users_catalog *USERS_CATALOG;

/**
 * @brief Estrutura opaca para o catálogo de músicas.
 *
 * Esta estrutura é utilizada para referência cruzada entre utilizadores e músicas.
 */
typedef struct musics_catalog *MUSICS_CATALOG;

/**
 * @brief Estrutura para um utilizador individual.
 */
typedef struct user *USER;

/**
 * @brief Estrutura para estatísticas globais.
 */
typedef struct stats STATS;

/**
 * @brief Cria um novo catálogo de utilizadores.
 *
 * Aloca memória e inicializa um catálogo vazio para armazenar utilizadores.
 *
 * @return Um apontador para o catálogo de utilizadores recém-criado.
 */
USERS_CATALOG create_users_catalog();

/**
 * @brief Insere um utilizador no catálogo.
 *
 * Insere um novo utilizador no catálogo com base nos parâmetros fornecidos.
 * Atualiza também os dados estatísticos globais e informações relacionadas às músicas.
 *
 * @param parameters_array Array que contém os detalhes do utilizador.
 * @param catalogo_users Apontador para o catálogo de utilizadores.
 * @param catalogo_musics Apontador para o catálogo de músicas.
 * @param stats Apontador para as estatísticas globais.
 */
void inserir_user_catalogo(GArray *parameters_array, USERS_CATALOG catalogo_users, MUSICS_CATALOG catalogo_musics, STATS *stats);

/**
 * @brief Insere um utilizador no catálogo com uma chave específica.
 *
 * Associa o utilizador fornecido a uma chave específica no catálogo.
 *
 * @param catalogo Apontador para o catálogo de utilizadores.
 * @param user Apontador para o utilizador a inserir.
 * @param key Chave associada ao utilizador.
 */
void insert_user(USERS_CATALOG catalogo, USER user, char *key);

/**
 * @brief Obtém um utilizador com base na chave.
 *
 * Pesquisa no catálogo um utilizador associado à chave fornecida.
 *
 * @param catalogo Apontador para o catálogo de utilizadores.
 * @param key Chave do utilizador a procurar.
 * @return Apontador para o utilizador associado à chave, ou NULL se não encontrado.
 */
USER get_user_by_key(USERS_CATALOG catalogo, char *key);

/**
 * @brief Atualiza um utilizador existente no catálogo.
 *
 * Substitui o utilizador associado à chave fornecida pelo novo utilizador.
 *
 * @param catalogo Apontador para o catálogo de utilizadores.
 * @param key Chave do utilizador a atualizar.
 * @param user Apontador para o novo utilizador.
 */
void update_user(USERS_CATALOG catalogo, char *key, USER user);

/**
 * @brief Liberta a memória alocada para o catálogo de utilizadores.
 *
 * Liberta todos os recursos utilizados pelo catálogo de utilizadores, incluindo os utilizadores armazenados.
 *
 * @param catalogo Apontador para o catálogo de utilizadores a ser libertado.
 */
void free_user_catalog(USERS_CATALOG catalogo);

#endif

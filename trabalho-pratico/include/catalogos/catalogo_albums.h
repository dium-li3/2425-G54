/**
 * @file catalogo_albums.h
 * @brief Ficheiro de cabeçalho para a gestão do catálogo de álbuns.
 *
 * Este ficheiro contém a definição de funções e estruturas utilizadas para
 * gerir o catálogo de álbuns, incluindo inserção, consulta, atualização e
 * gestão de memória.
 */

#ifndef CATALOGO_ALBUMS_H
#define CATALOGO_ALBUMS_H

#include <glib.h>
#include "entidades/albums.h"
#include "catalogos/catalogo_artists.h"

/**
 * @brief Estrutura opaca para o catálogo de álbuns.
 *
 * Esta estrutura encapsula os detalhes de implementação do catálogo de álbuns.
 */
typedef struct albums_catalog *ALBUMS_CATALOG;

/**
 * @brief Cria um novo catálogo de álbuns.
 *
 * Aloca memória e inicializa um catálogo vazio para armazenar álbuns.
 *
 * @return Um ponteiro para o catálogo de álbuns recém-criado.
 */
ALBUMS_CATALOG create_albums_catalog();

/**
 * @brief Insere um álbum no catálogo.
 *
 * Insere um novo álbum no catálogo utilizando os parâmetros fornecidos no
 * array de parâmetros. Atualiza informações relacionadas aos artistas, se necessário.
 *
 * @param parameters_array Array contendo os detalhes do álbum.
 * @param catalogo_albums Ponteiro para o catálogo de álbuns.
 * @param catalogo_artists Ponteiro para o catálogo de artistas para referência cruzada.
 */
void inserir_album_catalogo(GArray *parameters_array, ALBUMS_CATALOG catalogo_albums, ARTISTS_CATALOG catalogo_artists);

/**
 * @brief Insere um álbum no catálogo com uma chave específica.
 *
 * Associa o álbum fornecido a uma chave específica no catálogo.
 *
 * @param catalogo Ponteiro para o catálogo de álbuns.
 * @param album Ponteiro para o álbum a ser inserido.
 * @param key Chave a associar ao álbum.
 */
void insert_album(ALBUMS_CATALOG catalogo, ALBUM album, char *key);

/**
 * @brief Recupera um álbum pelo seu identificador.
 *
 * Pesquisa no catálogo por um álbum associado à chave fornecida.
 *
 * @param catalogo Ponteiro para o catálogo de álbuns.
 * @param key Identificador do álbum a ser recuperado.
 * @return Ponteiro para o álbum associado à chave ou NULL se não encontrado.
 */
ALBUM get_album_by_key(ALBUMS_CATALOG catalogo, char *key);

/**
 * @brief Atualiza um álbum existente no catálogo.
 *
 * Substitui o álbum associado à chave fornecida pelo álbum fornecido.
 *
 * @param catalogo Ponteiro para o catálogo de álbuns.
 * @param key Identificador do álbum a ser atualizado.
 * @param album Ponteiro para o novo álbum.
 */
void update_album(ALBUMS_CATALOG catalogo, char *key, ALBUM album);

/**
 * @brief Libera a memória alocada para o catálogo de álbuns.
 *
 * Liberta todos os recursos utilizados pelo catálogo de álbuns, incluindo os seus álbuns.
 *
 * @param catalogo Ponteiro para o catálogo de álbuns a ser liberado.
 */
void free_albums_catalog(ALBUMS_CATALOG catalogo);

#endif



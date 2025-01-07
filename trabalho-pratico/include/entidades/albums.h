/**
 * @file albums.h
 * @brief Interface para manipulação de álbuns.
 *
 * Este ficheiro contém a definição das funções e estruturas utilizadas para
 * manipular álbuns, incluindo criação, acesso a atributos, atualização e
 * libertação de memória.
 */

#ifndef ALBUMS_H
#define ALBUMS_H

#include <glib.h>

/**
 * @brief Estrutura opaca para um álbum.
 *
 * Esta estrutura encapsula os detalhes internos de um álbum.
 */
typedef struct album *ALBUM;

/**
 * @brief Cria um novo álbum vazio.
 *
 * Aloca memória e inicializa um álbum vazio com valores padrão.
 *
 * @return Ponteiro para o novo álbum criado.
 */
ALBUM create_album(void);

/**
 * @brief Obtém o ID do álbum.
 *
 * Retorna o ID do álbum formatado como uma string no formato "ALnnnnnn".
 *
 * @param album Ponteiro para o álbum.
 * @return String representando o ID do álbum.
 */
char* get_album_id(ALBUM album);

/**
 * @brief Obtém os IDs dos artistas associados ao álbum.
 *
 * Retorna um `GArray` contendo os IDs dos artistas associados ao álbum.
 *
 * @param album Ponteiro para o álbum.
 * @return `GArray` contendo os IDs dos artistas.
 */
GArray* get_album_artists_ids(ALBUM album);

/**
 * @brief Obtém o ano de lançamento do álbum.
 *
 * Retorna o ano de lançamento do álbum como um inteiro.
 *
 * @param album Ponteiro para o álbum.
 * @return Ano de lançamento do álbum.
 */
int get_album_year(ALBUM album);

/**
 * @brief Define o ID do álbum.
 *
 * Define o ID do álbum a partir de uma string no formato "ALnnnnnn".
 *
 * @param album Ponteiro para o álbum.
 * @param id String representando o ID do álbum.
 */
void set_album_id(ALBUM album, char *id);

/**
 * @brief Define os IDs dos artistas associados ao álbum.
 *
 * Define os IDs dos artistas do álbum a partir de uma string com IDs separados por vírgulas.
 *
 * @param album Ponteiro para o álbum.
 * @param artists_ids_str String com os IDs dos artistas separados por vírgulas.
 */
void set_album_artists_ids(ALBUM album, char *artists_ids_str);

/**
 * @brief Define o ano de lançamento do álbum.
 *
 * Define o ano de lançamento do álbum como um inteiro.
 *
 * @param album Ponteiro para o álbum.
 * @param year Ano de lançamento do álbum.
 */
void set_album_year(ALBUM album, int year);

/**
 * @brief Liberta a memória alocada para um álbum.
 *
 * Liberta todos os recursos associados ao álbum, incluindo IDs e outros atributos.
 *
 * @param album Ponteiro para o álbum a ser libertado.
 */
void free_album(ALBUM album);

#endif

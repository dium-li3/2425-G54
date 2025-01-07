/**
 * @file musics.h
 * @brief Ficheiro de cabeçalho para gestão de músicas.
 *
 * Este ficheiro contém a definição de funções e estruturas utilizadas para
 * gerir músicas, incluindo criação, acesso e modificação dos atributos de uma
 * música.
 */

#ifndef MUSICS_H
#define MUSICS_H

#include <stdio.h>
#include <string.h>
#include <glib.h>

#include "entidades/artists.h"
#include "catalogos/catalogo_musics.h"
#include "manager_dados/utils.h"

/**
 * @brief Estrutura opaca para representar uma música.
 *
 * Esta estrutura encapsula os detalhes da implementação de uma música.
 */
typedef struct music *MUSIC;

/**
 * @brief Cria uma nova música.
 *
 * Aloca memória e inicializa uma música vazia.
 *
 * @return Um ponteiro para a nova música criada.
 */
MUSIC criar_music(void);

/**
 * @brief Obtém o ID da música.
 *
 * Retorna o ID único associado à música.
 *
 * @param music Ponteiro para a música.
 * @return Uma string contendo o ID da música.
 */
char* getId(MUSIC music);

/**
 * @brief Obtém os IDs dos artistas da música.
 *
 * Retorna uma lista de IDs dos artistas associados à música.
 *
 * @param music Ponteiro para a música.
 * @return Um GArray contendo os IDs dos artistas.
 */
GArray *getArtistIds(MUSIC music);

/**
 * @brief Obtém o ID do álbum da música.
 *
 * Retorna o ID do álbum ao qual a música pertence.
 *
 * @param music Ponteiro para a música.
 * @return Uma string contendo o ID do álbum.
 */
char* getAlbumId(MUSIC music);

/**
 * @brief Obtém a duração da música.
 *
 * Retorna a duração da música em segundos.
 *
 * @param music Ponteiro para a música.
 * @return A duração da música em segundos.
 */
int getDuration(MUSIC music);

/**
 * @brief Obtém o género da música.
 *
 * Retorna o género musical associado à música.
 *
 * @param music Ponteiro para a música.
 * @return Uma string contendo o género da música.
 */
char* getGenre(MUSIC music);

/**
 * @brief Obtém o ano de lançamento da música.
 *
 * Retorna o ano em que a música foi lançada.
 *
 * @param music Ponteiro para a música.
 * @return O ano de lançamento da música.
 */
int getYear(MUSIC music);

/**
 * @brief Define o ID da música.
 *
 * Atualiza o ID único associado à música.
 *
 * @param music Ponteiro para a música.
 * @param id Uma string contendo o novo ID da música.
 */
void setId(MUSIC music, char *id);

/**
 * @brief Define os IDs dos artistas da música.
 *
 * Atualiza a lista de IDs dos artistas associados à música.
 *
 * @param music Ponteiro para a música.
 * @param artist_ids Uma string contendo os IDs dos artistas separados por vírgulas.
 */
void setArtistIds(MUSIC music, char* artist_ids);

/**
 * @brief Define o ID do álbum da música.
 *
 * Atualiza o ID do álbum ao qual a música pertence.
 *
 * @param music Ponteiro para a música.
 * @param album_id Uma string contendo o novo ID do álbum.
 */
void setAlbumId(MUSIC music,char* album_id);

/**
 * @brief Define a duração da música.
 *
 * Atualiza a duração da música em segundos.
 *
 * @param music Ponteiro para a música.
 * @param duration Uma string contendo a duração da música.
 */
void setDuration(MUSIC music, char *duration);

/**
 * @brief Define o género da música.
 *
 * Atualiza o género musical associado à música.
 *
 * @param music Ponteiro para a música.
 * @param genre Uma string contendo o novo género da música.
 */
void setGenre(MUSIC music, char *genre);

/**
 * @brief Define o ano de lançamento da música.
 *
 * Atualiza o ano em que a música foi lançada.
 *
 * @param music Ponteiro para a música.
 * @param year O novo ano de lançamento da música.
 */
void setYear(MUSIC music, int year);

/**
 * @brief Liberta a memória associada a uma música.
 *
 * Remove todos os dados associados à música e liberta os recursos.
 *
 * @param data Ponteiro para a música a ser destruída.
 */
void destroi_musics(gpointer data);

#endif

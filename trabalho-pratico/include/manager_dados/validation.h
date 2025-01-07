/**
 * @file validation.h
 * @brief Cabeçalho para funções de validação de dados.
 *
 * Este ficheiro contém a declaração de funções responsáveis por validar dados
 * como datas, durações, e-mails, listas, entre outros. Estas funções são 
 * utilizadas para garantir a integridade das entradas nos catálogos e 
 * entidades do programa.
 */

#ifndef VALIDATION_UTILS_H
#define VALIDATION_UTILS_H

#include <glib.h>
#include "entidades/musics.h"   
#include "entidades/users.h"
#include "entidades/artists.h"
#include "entidades/stats.h"
#include "catalogos/catalogo_musics.h"
#include "catalogos/catalogo_artists.h"
#include "catalogos/catalogo_users.h"
#include "manager_dados/utils.h"

/**
 * @brief Valida se a data fornecida está num formato válido.
 * @param data String representando a data a ser validada.
 * @return 1 se a data for válida, 0 caso contrário.
 */
int data_valida(char *data);

/**
 * @brief Verifica se a duração está num formato válido.
 * @param duracao String representando a duração no formato HH:MM:SS.
 * @return 1 se a duração for válida, 0 caso contrário.
 */
int duracao_valida(char *duracao);

/**
 * @brief Verifica se a data e hora estão num formato válido.
 * @param datetime String representando a data e hora.
 * @return 1 se o formato for válido, 0 caso contrário.
 */
int datetime_valida(char *datetime);

/**
 * @brief Verifica se o caractere fornecido é válido.
 * @param c Caractere a ser validado.
 * @return 1 se o caractere for válido, 0 caso contrário.
 */
int caracter_valido(char c);

/**
 * @brief Valida se o domínio de um e-mail é válido.
 * @param part Parte do domínio a ser validada.
 * @return 1 se o domínio for válido, 0 caso contrário.
 */
int dominio_valido(char *part);

/**
 * @brief Valida um endereço de e-mail.
 * @param email String representando o e-mail.
 * @return 1 se o e-mail for válido, 0 caso contrário.
 */
int verifica_email(char *email);

/**
 * @brief Verifica se uma string está no formato de lista.
 * @param string String a ser validada.
 * @return 1 se for uma lista válida, 0 caso contrário.
 */
int verify_if_is_list(char *string);

/**
 * @brief Valida o tipo de subscrição fornecido.
 * @param s_type String representando o tipo de subscrição.
 * @return 1 se o tipo de subscrição for válido, 0 caso contrário.
 */
int verifica_subscription_type(char *s_type);

/**
 * @brief Verifica se as músicas marcadas como "gostadas" são válidas.
 * @param liked_musics String representando as músicas.
 * @param catalogo_musics Catálogo de músicas para validação.
 * @return 1 se todas as músicas forem válidas, 0 caso contrário.
 */
int verifica_liked_musics(char *liked_musics, MUSICS_CATALOG catalogo_musics);

/**
 * @brief Valida se os IDs de artistas fornecidos existem no catálogo.
 * @param artists_id String com os IDs de artistas.
 * @param catalogo_artists Catálogo de artistas.
 * @return 1 se os IDs forem válidos, 0 caso contrário.
 */
int verifica_music_artist(char *artists_id, ARTISTS_CATALOG catalogo_artists);

/**
 * @brief Valida se o álbum fornecido existe no catálogo.
 * @param album_id ID do álbum a ser validado.
 * @param albums Catálogo de álbuns.
 * @return 1 se o álbum for válido, 0 caso contrário.
 */
int verifica_music_album(char *album_id, ALBUMS_CATALOG albums);

/**
 * @brief Normaliza e valida a plataforma fornecida.
 * @param platform String representando a plataforma.
 * @return 1 se a plataforma for válida, 0 caso contrário.
 */
int validate_and_normalize_platform(char *platform);

/**
 * @brief Normaliza e valida o tipo fornecido.
 * @param type String representando o tipo.
 * @return 1 se o tipo for válido, 0 caso contrário.
 */
int validate_and_normalize_type(char *type);

/**
 * @brief Verifica se o ID de um artista ou banda é válido.
 * @param id_constituent String representando o ID.
 * @param artist_type Tipo de artista ("individual" ou "grupo").
 * @return 1 se o ID for válido, 0 caso contrário.
 */
int verifica_artista_ou_banda(char *id_constituent, char *artist_type);

/**
 * @brief Valida uma entidade com base no seu tipo e parâmetros fornecidos.
 * @param flag Indica o tipo de entidade (artista, música, álbum, etc.).
 * @param parameters_array Array de parâmetros da entidade.
 * @param catalogo_artists Catálogo de artistas.
 * @param catalogo_musics Catálogo de músicas.
 * @param catalogo_albums Catálogo de álbuns.
 * @return 1 se a entidade for válida, 0 caso contrário.
 */
int valid_entity(int flag, GArray *parameters_array, ARTISTS_CATALOG catalogo_artists, MUSICS_CATALOG catalogo_musics, ALBUMS_CATALOG catalogo_albums);

#endif

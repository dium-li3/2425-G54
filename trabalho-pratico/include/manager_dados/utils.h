/**
 * @file utils.h
 * @brief Conjunto de funções utilitárias para manipulação e processamento de dados.
 *
 * Este ficheiro contém a definição de funções utilitárias usadas em várias partes do projeto,
 * como formatação de strings, cálculos de datas e manipulação de entidades.
 */

#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <string.h>
#include <glib.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

#include "entidades/albums.h"
#include "entidades/musics.h"   
#include "entidades/users.h"
#include "entidades/artists.h"
#include "entidades/stats.h"

#include "catalogos/catalogo_musics.h"
#include "catalogos/catalogo_artists.h"
#include "catalogos/catalogo_users.h"

/**
 * @brief Cria uma string com a mensagem de erro para o diretório especificado.
 * @param directory O diretório onde o erro ocorreu.
 * @return Uma string alocada dinamicamente contendo a mensagem de erro.
 */
char *create_errors(char *directory);

/**
 * @brief Cria e abre um ficheiro para escrita.
 * @param errors Caminho para o ficheiro de erros.
 * @return Um ponteiro para o ficheiro aberto.
 */
FILE *create_file(char *errors);

/**
 * @brief Converte uma duração no formato "HH:MM:SS" para o número total de segundos.
 * @param duration String contendo a duração no formato "HH:MM:SS".
 * @return Número total de segundos.
 */
int convert_duration_to_seconds(char *duration);

/**
 * @brief Converte segundos para uma string no formato "HH:MM:SS".
 * @param total_seconds Número total de segundos.
 * @return Uma string alocada dinamicamente com a duração no formato "HH:MM:SS".
 */
char* convert_seconds_to_duration(int total_seconds);

/**
 * @brief Calcula a idade com base na data de nascimento.
 * @param birthdate String contendo a data de nascimento no formato "YYYY-MM-DD".
 * @return Idade calculada em anos.
 */
int calculate_age(char *birthdate);

/**
 * @brief Remove espaços em branco e ajusta o formato de uma string.
 * @param str String a ser formatada.
 */
void format_string(char *str);

/**
 * @brief Converte uma string para minúsculas.
 * @param str String a ser convertida.
 */
void to_lowercase(char *str);

/**
 * @brief Remove aspas de uma string.
 * @param str String a ser modificada.
 */
void removeQuotes(char *str);

/**
 * @brief Remove caracteres de nova linha de uma string.
 * @param str String a ser modificada.
 */
void remove_newline(char *str);

/**
 * @brief Calcula o dia do ano com base na data fornecida.
 * @param year Ano.
 * @param month Mês.
 * @param day Dia.
 * @return O número do dia do ano.
 */
int calculate_day_of_year(int year, int month, int day);

/**
 * @brief Calcula o mês e o dia com base no número do dia do ano.
 * @param year Ano.
 * @param day_of_year O número do dia no ano.
 * @param month Ponteiro para armazenar o mês calculado.
 * @param day Ponteiro para armazenar o dia calculado.
 */
void calculate_month_and_day(int year, int day_of_year, int *month, int *day);

/**
 * @brief Atualiza informações com base no histórico fornecido.
 * @param parameters_array Array contendo os parâmetros do histórico.
 * @param catalogo_musics Catálogo de músicas.
 * @param catalogo_artists Catálogo de artistas.
 * @param catalogo_users Catálogo de utilizadores.
 * @param stats Estrutura de estatísticas.
 */
void update_info_with_history(GArray *parameters_array, MUSICS_CATALOG catalogo_musics, ARTISTS_CATALOG catalogo_artists, USERS_CATALOG catalogo_users, STATS *stats);

/**
 * @brief Atualiza a receita de um artista com base numa música.
 * @param music_id ID da música.
 * @param catalogo_musics Catálogo de músicas.
 * @param artists_catalog Catálogo de artistas.
 */
void updateArtistRecipe(char *music_id, MUSICS_CATALOG catalogo_musics, ARTISTS_CATALOG artists_catalog);

/**
 * @brief Atualiza os álbuns individuais de um artista.
 * @param album Álbum a ser atualizado.
 * @param catalogo_artists Catálogo de artistas.
 */
void updateIndividualAlbums(ALBUM album, ARTISTS_CATALOG catalogo_artists);

/**
 * @brief Função de ordenação para o tempo de discografia.
 * @param a Ponteiro para o primeiro elemento.
 * @param b Ponteiro para o segundo elemento.
 * @return Valor para determinar a ordem.
 */
gint sort_DiscographyTime(gconstpointer a, gconstpointer b);

/**
 * @brief Atualiza o tempo de discografia de um artista com base numa música.
 * @param catalogo_artists Catálogo de artistas.
 * @param music Música para cálculo do tempo.
 */
void update_DiscographyTime(ARTISTS_CATALOG catalogo_artists, MUSIC music);

/**
 * @brief Função de ordenação para géneros musicais.
 * @param a Ponteiro para o primeiro género.
 * @param b Ponteiro para o segundo género.
 * @return Valor para determinar a ordem.
 */
gint sort_GeneroMusical(gconstpointer a, gconstpointer b);

/**
 * @brief Atualiza estatísticas de género com base nos dados de um utilizador.
 * @param stats Estrutura de estatísticas.
 * @param catalogo_musics Catálogo de músicas.
 * @param user Utilizador para análise.
 */
void update_statistics_for_genre(STATS *stats, MUSICS_CATALOG catalogo_musics, USER user);

#endif

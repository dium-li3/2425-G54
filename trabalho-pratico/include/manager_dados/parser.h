/**
 * @file parser.h
 * @brief Ficheiro de cabeçalho para o processamento e análise de dados.
 *
 * Este ficheiro contém funções para o processamento de dados, inserção em catálogos
 * e validação de entradas provenientes de ficheiros.
 */

#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <glib.h>

#include "entidades/musics.h"   
#include "entidades/users.h"
#include "entidades/artists.h"
#include "entidades/albums.h"
#include "entidades/stats.h"

#include "catalogos/catalogo_musics.h"
#include "catalogos/catalogo_artists.h"
#include "catalogos/catalogo_users.h"
#include "catalogos/catalogo_albums.h"

#include "manager_dados/parser.h"
#include "manager_dados/querier.h"
#include "manager_dados/validation.h"
#include "manager_dados/utils.h"

/**
 * @brief Obtém o caminho para o ficheiro de erro baseado no flag fornecido.
 *
 * Esta função devolve o caminho apropriado para o ficheiro de erro 
 * dependendo do flag de entrada.
 *
 * @param flag O flag que identifica o tipo de erro.
 * @return O caminho do ficheiro de erro correspondente.
 */
char *get_error_file_path(int flag);

/**
 * @brief Obtém o ficheiro correspondente ao flag fornecido.
 *
 * Esta função devolve o ficheiro apropriado com base no flag 
 * e nos ficheiros fornecidos como entrada.
 *
 * @param flag O flag que identifica o ficheiro desejado.
 * @param artists_file Ficheiro de artistas.
 * @param albums_file Ficheiro de álbuns.
 * @param musics_file Ficheiro de músicas.
 * @param users_file Ficheiro de utilizadores.
 * @param history_file Ficheiro de histórico.
 * @return Ponteiro para o ficheiro correspondente ou NULL se não encontrado.
 */
FILE *get_file_by_flag(int flag, FILE *artists_file, FILE *albums_file, FILE *musics_file, FILE *users_file, FILE *history_file);

/**
 * @brief Insere dados nos catálogos apropriados com base no flag.
 *
 * Esta função insere dados em catálogos como artistas, álbuns, músicas e utilizadores 
 * usando os parâmetros fornecidos.
 *
 * @param flag Flag que determina o catálogo alvo.
 * @param parameters_array Array com os parâmetros a serem inseridos.
 * @param artists Catálogo de artistas.
 * @param albums Catálogo de álbuns.
 * @param musics Catálogo de músicas.
 * @param users Catálogo de utilizadores.
 * @param stats Estrutura de estatísticas para armazenamento de informações adicionais.
 */
void insert_catalogo(int flag, GArray *parameters_array, ARTISTS_CATALOG artists, ALBUMS_CATALOG albums, MUSICS_CATALOG musics, USERS_CATALOG users, STATS *stats);

/**
 * @brief Processa os ficheiros de entrada e preenche os catálogos.
 *
 * Esta função processa os ficheiros fornecidos, valida os dados e insere 
 * informações nos catálogos e na estrutura de estatísticas.
 *
 * @param artists Catálogo de artistas.
 * @param musics Catálogo de músicas.
 * @param users Catálogo de utilizadores.
 * @param albums Catálogo de álbuns.
 * @param stats Estrutura de estatísticas para armazenamento de informações.
 * @param artists_file Ficheiro de entrada para artistas.
 * @param musics_file Ficheiro de entrada para músicas.
 * @param users_file Ficheiro de entrada para utilizadores.
 * @param history_file Ficheiro de entrada para histórico.
 * @param albums_file Ficheiro de entrada para álbuns.
 */
void parser(ARTISTS_CATALOG artists, MUSICS_CATALOG musics, USERS_CATALOG users, ALBUMS_CATALOG albums, STATS *stats, FILE *artists_file, FILE *musics_file, FILE *users_file, FILE *history_file, FILE *albums_file);

#endif

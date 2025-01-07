/**
 * @file artists.h
 * @brief Interface para a manipulação de entidades ARTIST.
 *
 * Este ficheiro contém as definições e assinaturas das funções utilizadas para
 * criar, acessar, atualizar e destruir entidades ARTIST no sistema.
 */

#ifndef ARTISTS_H
#define ARTISTS_H

#include <stdio.h>
#include <string.h>
#include <glib.h>
#include <stdlib.h>

#include "catalogos/catalogo_artists.h"

/**
 * @brief Tipo opaco que representa um artista.
 *
 * Este tipo encapsula as informações relacionadas a um artista e seus métodos
 * de manipulação.
 */
typedef struct artist *ARTIST;

/**
 * @brief Cria uma nova entidade ARTIST.
 *
 * Inicializa um artista vazio com valores padrão.
 *
 * @return Uma nova instância de ARTIST.
 */
ARTIST criar_artist(void);

/**
 * @brief Obtém o ID do artista.
 * @param artist A entidade ARTIST.
 * @return Uma string contendo o ID do artista.
 */
char* getArtistId(ARTIST artist);

/**
 * @brief Obtém o nome do artista.
 * @param artist A entidade ARTIST.
 * @return Uma string contendo o nome do artista.
 */
char* getArtistName(ARTIST artist);

/**
 * @brief Obtém a receita por stream do artista.
 * @param artist A entidade ARTIST.
 * @return Um valor em double representando a receita por stream.
 */
double getRecipePerStream(ARTIST artist);

/**
 * @brief Obtém os IDs dos constituintes do artista.
 * @param artist A entidade ARTIST.
 * @return Um GArray contendo os IDs dos constituintes.
 */
GArray* getIdConstituents(ARTIST artist);

/**
 * @brief Obtém o país de origem do artista.
 * @param artist A entidade ARTIST.
 * @return Uma string contendo o país de origem do artista.
 */
char* getArtistCountry(ARTIST artist);

/**
 * @brief Obtém o tipo do artista (individual ou grupo).
 * @param artist A entidade ARTIST.
 * @return Uma string indicando o tipo do artista.
 */
char* getArtistType(ARTIST artist);

/**
 * @brief Obtém a duração da discografia do artista.
 * @param artist A entidade ARTIST.
 * @return Um valor inteiro representando a duração em anos.
 */
int getDiscographyDuration(ARTIST artist);

/**
 * @brief Obtém o número de álbuns individuais do artista.
 * @param artist A entidade ARTIST.
 * @return Um valor inteiro representando o número de álbuns.
 */
int getIndividualAlbuns(ARTIST artist);

/**
 * @brief Obtém a receita total do artista.
 * @param artist A entidade ARTIST.
 * @return Um valor em double representando a receita total.
 */
double getArtistRecipe(ARTIST artist);

/**
 * @brief Define o ID do artista.
 * @param artist A entidade ARTIST.
 * @param id O ID a ser atribuído.
 */
void setArtistId(ARTIST artist, char *id);

/**
 * @brief Define o nome do artista.
 * @param artist A entidade ARTIST.
 * @param name O nome a ser atribuído.
 */
void setArtistName(ARTIST artist, char *name);

/**
 * @brief Define a receita por stream do artista.
 * @param artist A entidade ARTIST.
 * @param recipe_per_stream A receita a ser atribuída.
 */
void setRecipePerStream(ARTIST artist, char *recipe_per_stream);

/**
 * @brief Define os IDs dos constituintes do artista.
 * @param artist A entidade ARTIST.
 * @param id_constituents_str Uma string contendo os IDs separados por vírgula.
 */
void setArtistIdConstituents(ARTIST artist, char *id_constituents_str);

/**
 * @brief Define o país de origem do artista.
 * @param artist A entidade ARTIST.
 * @param country O país a ser atribuído.
 */
void setArtistCountry(ARTIST artist, char *country);

/**
 * @brief Define o tipo do artista.
 * @param artist A entidade ARTIST.
 * @param type O tipo (individual ou grupo) a ser atribuído.
 */
void setArtistType(ARTIST artist, char *type);

/**
 * @brief Incrementa a duração da discografia do artista.
 * @param artist A entidade ARTIST.
 * @param duration O valor a ser incrementado.
 */
void setDiscographyDuration(ARTIST artist, int duration);

/**
 * @brief Incrementa o número de álbuns individuais do artista.
 * @param artist A entidade ARTIST.
 */
void setIndividualAlbuns(ARTIST artist);

/**
 * @brief Incrementa a receita total do artista.
 * @param artist A entidade ARTIST.
 * @param recipe A receita a ser adicionada.
 */
void setArtistRecipe(ARTIST artist, double recipe);

/**
 * @brief Libera os recursos alocados para uma entidade ARTIST.
 * @param data Um ponteiro para a entidade ARTIST.
 */
void destroi_artists(gpointer data);

#endif

/**
 * @file output.h
 * @brief Interface para a escrita de saídas no formato especificado.
 *
 * Este ficheiro contém as funções responsáveis por produzir as saídas
 * formatadas para os ficheiros de resultado das queries.
 */

#ifndef OUTPUT_H
#define OUTPUT_H

#include <glib.h>
#include <stdio.h>

/**
 * @brief Escreve uma saída nula.
 *
 * Produz uma linha indicando que a query não teve resultados.
 *
 * @param numlinha Número da linha da query no ficheiro de entrada.
 */
void write_null(int numlinha);

/**
 * @brief Escreve a saída da Query 1 para utilizadores.
 *
 * Produz os dados do utilizador especificado, formatados segundo a query 1.
 *
 * @param numlinha Número da linha da query no ficheiro de entrada.
 * @param output_flag Flag que indica o formato da saída (detalhado ou resumido).
 * @param email Email do utilizador.
 * @param first_name Primeiro nome do utilizador.
 * @param last_name Último nome do utilizador.
 * @param age Idade do utilizador.
 * @param country País do utilizador.
 */
void write_query1_user_output(int numlinha, int output_flag, char *email, char *first_name, char *last_name, int age, char *country);

/**
 * @brief Escreve a saída da Query 1 para artistas.
 *
 * Produz os dados do artista especificado, formatados segundo a query 1.
 *
 * @param numlinha Número da linha da query no ficheiro de entrada.
 * @param output_flag Flag que indica o formato da saída (detalhado ou resumido).
 * @param name Nome do artista.
 * @param type Tipo do artista (individual ou grupo).
 * @param country País do artista.
 * @param individual_albuns Número de álbuns individuais do artista.
 * @param recipe Receita associada ao artista.
 */
void write_query1_artist_output(int numlinha, int output_flag, char *name, char *type, char *country, int individual_albuns, double recipe);

/**
 * @brief Escreve a saída da Query 2.
 *
 * Produz os dados de um artista conforme os requisitos da query 2.
 *
 * @param numlinha Número da linha da query no ficheiro de entrada.
 * @param output_flag Flag que indica o formato da saída (detalhado ou resumido).
 * @param artistName Nome do artista.
 * @param artistType Tipo do artista (individual ou grupo).
 * @param duration Duração das músicas associadas ao artista.
 * @param artistCountry País do artista.
 */
void write_query2_output(int numlinha, int output_flag, char *artistName, char *artistType, char *duration, char *artistCountry);

/**
 * @brief Escreve a saída da Query 3.
 *
 * Produz os dados do género musical conforme os requisitos da query 3.
 *
 * @param numlinha Número da linha da query no ficheiro de entrada.
 * @param output_flag Flag que indica o formato da saída (detalhado ou resumido).
 * @param nomeGenero Nome do género musical.
 * @param likesGenero Número de "likes" associados ao género.
 */
void write_query3_output(int numlinha, int output_flag, char *nomeGenero, int likesGenero);

#endif

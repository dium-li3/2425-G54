/**
 * @file query_results.h
 * @brief Interface para a gestão de resultados de queries.
 *
 * Este ficheiro contém as definições de funções e estruturas utilizadas para
 * criar e manipular os resultados de queries no sistema.
 */

#ifndef QUERYRESULTS_H
#define QUERYRESULTS_H

#include <glib.h>

/**
 * @brief Estrutura opaca para armazenar os resultados das queries.
 *
 * Esta estrutura encapsula os detalhes de implementação relacionados com os
 * resultados das queries.
 */
typedef struct queryresults *QUERYRESULTS;

/**
 * @brief Cria uma nova instância para armazenar resultados de queries.
 *
 * @return Um ponteiro para uma nova estrutura QUERYRESULTS.
 */
QUERYRESULTS create_query_results(void);

/**
 * @brief Obtém o tempo total gasto na execução da query.
 *
 * @param query_results Estrutura QUERYRESULTS com os resultados da query.
 * @return Tempo total de execução da query.
 */
double get_query_time(QUERYRESULTS query_results);

/**
 * @brief Obtém o número total de queries executadas.
 *
 * @param query_results Estrutura QUERYRESULTS com os resultados da query.
 * @return Número total de queries executadas.
 */
int get_number_of_queries(QUERYRESULTS query_results);

/**
 * @brief Obtém o número total de queries corretas.
 *
 * @param query_results Estrutura QUERYRESULTS com os resultados da query.
 * @return Número total de queries corretas.
 */
int get_total_correct_queries(QUERYRESULTS query_results);

/**
 * @brief Obtém as queries falhadas e as suas linhas associadas.
 *
 * @param query_results Estrutura QUERYRESULTS com os resultados da query.
 * @return Um GArray contendo as queries falhadas e as respetivas linhas.
 */
GArray *get_failed_queries(QUERYRESULTS query_results);

/**
 * @brief Define o tempo de execução de uma query.
 *
 * @param query_results Estrutura QUERYRESULTS com os resultados da query.
 * @param time Tempo total de execução da query.
 */
void set_query_time(QUERYRESULTS query_results, double time);

/**
 * @brief Define o número total de queries executadas.
 *
 * @param query_results Estrutura QUERYRESULTS com os resultados da query.
 * @param number_of_queries Número total de queries executadas.
 */
void set_number_of_queries(QUERYRESULTS query_results, int number_of_queries);

/**
 * @brief Define o número total de queries corretas.
 *
 * @param query_results Estrutura QUERYRESULTS com os resultados da query.
 * @param total_correct_queries Número total de queries corretas.
 */
void set_total_correct_queries(QUERYRESULTS query_results, int total_correct_queries);

/**
 * @brief Adiciona uma query falhada e a sua linha associada.
 *
 * @param query_results Estrutura QUERYRESULTS com os resultados da query.
 * @param failed_query ID da query falhada.
 * @param line_failed Linha onde ocorreu a falha.
 */
void set_failed_queries(QUERYRESULTS query_results, int failed_query, int line_failed);

/**
 * @brief Liberta a memória associada a uma estrutura QUERYRESULTS.
 *
 * Esta função é utilizada para destruir os dados armazenados na estrutura.
 *
 * @param data Ponteiro para a estrutura QUERYRESULTS a ser destruída.
 */
void query_destroy_function(gpointer data);

#endif

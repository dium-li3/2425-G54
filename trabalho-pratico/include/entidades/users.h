/**
 * @file users.h
 * @brief Interface para a gestão de utilizadores.
 *
 * Este ficheiro contém as definições de funções e estruturas utilizadas para
 * criar, manipular e gerir informações de utilizadores no sistema.
 */

#ifndef USERS_H
#define USERS_H

#include <stdio.h>
#include <string.h>
#include <glib.h>
#include <stdlib.h>

/**
 * @brief Estrutura opaca que representa um utilizador.
 *
 * Esta estrutura encapsula os detalhes de implementação relacionados a um utilizador.
 */
typedef struct user *USER;

/**
 * @brief Estrutura opaca que representa estatísticas de utilizadores.
 *
 * Esta estrutura encapsula os detalhes de implementação relacionados às estatísticas dos utilizadores.
 */
typedef struct user_statistics *USER_STATISTICS;

/**
 * @brief Cria um novo utilizador vazio.
 *
 * Aloca memória e inicializa os campos do utilizador com valores padrão.
 *
 * @return Um ponteiro para o novo utilizador criado.
 */
USER criar_user(void);

/**
 * @brief Obtém o nome de utilizador (username).
 *
 * Retorna o username formatado do utilizador.
 *
 * @param user Ponteiro para o utilizador.
 * @return Uma string com o username do utilizador.
 */
char* getUsername(USER user);

/**
 * @brief Obtém o email do utilizador.
 *
 * Retorna o email associado ao utilizador.
 *
 * @param user Ponteiro para o utilizador.
 * @return Uma string com o email do utilizador.
 */
char* getEmail(USER user);

/**
 * @brief Obtém o primeiro nome do utilizador.
 *
 * Retorna o primeiro nome associado ao utilizador.
 *
 * @param user Ponteiro para o utilizador.
 * @return Uma string com o primeiro nome do utilizador.
 */
char* getFirstName(USER user);

/**
 * @brief Obtém o último nome do utilizador.
 *
 * Retorna o último nome associado ao utilizador.
 *
 * @param user Ponteiro para o utilizador.
 * @return Uma string com o último nome do utilizador.
 */
char* getLastName(USER user);

/**
 * @brief Obtém a idade do utilizador.
 *
 * Retorna a idade calculada do utilizador.
 *
 * @param user Ponteiro para o utilizador.
 * @return A idade do utilizador como um inteiro.
 */
int getAge(USER user);

/**
 * @brief Obtém o país do utilizador.
 *
 * Retorna o país associado ao utilizador.
 *
 * @param user Ponteiro para o utilizador.
 * @return Uma string com o país do utilizador.
 */
char* getCountry(USER user);

/**
 * @brief Obtém as músicas favoritas do utilizador.
 *
 * Retorna um array com os IDs das músicas favoritas do utilizador.
 *
 * @param user Ponteiro para o utilizador.
 * @return Um GArray contendo os IDs das músicas favoritas.
 */
GArray *getLikedMusics(USER user);

/**
 * @brief Define o nome de utilizador (username).
 *
 * Configura o username do utilizador a partir de uma string formatada.
 *
 * @param user Ponteiro para o utilizador.
 * @param username String contendo o novo username.
 */
void setUsername(USER user, char *username);

/**
 * @brief Define o email do utilizador.
 *
 * Atualiza o email associado ao utilizador.
 *
 * @param user Ponteiro para o utilizador.
 * @param email String contendo o novo email.
 */
void setEmail(USER user, char *email);

/**
 * @brief Define o primeiro nome do utilizador.
 *
 * Atualiza o primeiro nome associado ao utilizador.
 *
 * @param user Ponteiro para o utilizador.
 * @param first_name String contendo o novo primeiro nome.
 */
void setFirstName(USER user, char *first_name);

/**
 * @brief Define o último nome do utilizador.
 *
 * Atualiza o último nome associado ao utilizador.
 *
 * @param user Ponteiro para o utilizador.
 * @param last_name String contendo o novo último nome.
 */
void setLastName(USER user, char *last_name);

/**
 * @brief Define a idade do utilizador.
 *
 * Calcula e atualiza a idade do utilizador a partir da sua data de nascimento.
 *
 * @param user Ponteiro para o utilizador.
 * @param birth_date String contendo a data de nascimento.
 */
void setAge(USER user, char *birth_date);

/**
 * @brief Define o país do utilizador.
 *
 * Atualiza o país associado ao utilizador.
 *
 * @param user Ponteiro para o utilizador.
 * @param country String contendo o novo país.
 */
void setCountry(USER user, char *country);

/**
 * @brief Define as músicas favoritas do utilizador.
 *
 * Atualiza a lista de IDs das músicas favoritas do utilizador.
 *
 * @param user Ponteiro para o utilizador.
 * @param liked_musics String contendo os IDs das músicas favoritos separados por vírgulas.
 */
void setLikedMusics(USER user, char* liked_musics);

/**
 * @brief Libera a memória associada ao utilizador.
 *
 * Libera todos os recursos utilizados pela estrutura de utilizador.
 *
 * @param data Ponteiro para a estrutura de utilizador a ser destruída.
 */
void destroi_users(gpointer data);

#endif

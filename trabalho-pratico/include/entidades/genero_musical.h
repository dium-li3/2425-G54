/**
 * @file genero_musical.h
 * @brief Interface para manipulação de entidades de gêneros musicais.
 *
 * Este ficheiro contém as definições de funções e estruturas utilizadas
 * para criar, gerir e libertar instâncias de gêneros musicais.
 */

#ifndef GENERO_MUSICAL_H
#define GENERO_MUSICAL_H

/**
 * @brief Estrutura opaca que representa um gênero musical.
 *
 * Esta estrutura encapsula os detalhes de implementação de um gênero musical.
 */
typedef struct genero_musical *GENERO_MUSICAL;

/**
 * @brief Cria uma nova instância de gênero musical.
 *
 * Aloca memória e inicializa uma nova entidade de gênero musical.
 *
 * @return Um ponteiro para a nova instância de gênero musical.
 */
GENERO_MUSICAL criar_genero_musical(void);

// Getters

/**
 * @brief Obtém o nome do gênero musical.
 *
 * Retorna o nome associado ao gênero musical fornecido.
 *
 * @param genero Ponteiro para a instância do gênero musical.
 * @return Uma cópia da string com o nome do gênero musical.
 */
char* getGeneroNome(GENERO_MUSICAL genero);

/**
 * @brief Obtém o número de likes do gênero musical.
 *
 * Retorna o número de likes associado ao gênero musical fornecido.
 *
 * @param genero Ponteiro para a instância do gênero musical.
 * @return Número de likes do gênero musical.
 */
int getGeneroLikes(GENERO_MUSICAL genero);

// Setters

/**
 * @brief Define o nome do gênero musical.
 *
 * Atribui um nome à instância de gênero musical fornecida.
 *
 * @param genero Ponteiro para a instância do gênero musical.
 * @param nome Nome do gênero musical a ser atribuído.
 */
void setGeneroNome(GENERO_MUSICAL genero, char *nome);

/**
 * @brief Define o número de likes do gênero musical.
 *
 * Atualiza o número de likes da instância de gênero musical fornecida.
 *
 * @param genero Ponteiro para a instância do gênero musical.
 * @param likes Número de likes a ser atribuído.
 */
void setGeneroLikes(GENERO_MUSICAL genero, int likes);

/**
 * @brief Liberta a memória alocada para o gênero musical.
 *
 * Destrói a instância do gênero musical, libertando toda a memória associada.
 *
 * @param genero Ponteiro para a instância do gênero musical a ser libertada.
 */
void free_genero_musical(GENERO_MUSICAL genero);

#endif

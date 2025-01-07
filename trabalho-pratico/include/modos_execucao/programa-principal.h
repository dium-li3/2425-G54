/**
 * @file programa-principal.h
 * @brief Declarações de funções para a execução do programa principal no modo interativo.
 *
 * Este ficheiro contém as funções e estruturas necessárias para gerir
 * o programa principal, incluindo a execução de comandos e interação com os catálogos
 * de dados e entidades.
 */

#ifndef EXEC_BATCH_MODE_H
#define EXEC_BATCH_MODE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>

#include "entidades/musics.h"   
#include "entidades/users.h"
#include "entidades/artists.h"
#include "entidades/stats.h"

#include "catalogos/catalogo_musics.h"
#include "catalogos/catalogo_artists.h"
#include "catalogos/catalogo_users.h"

#include "manager_dados/utils.h"
#include "manager_dados/querier.h"
#include "manager_dados/parser.h"
#include "manager_dados/validation.h"

#include "modos_execucao/programa-principal.h"

/**
 * @brief Executa o programa principal no modo interativo.
 *
 * Esta função inicializa os componentes principais do programa, carrega os dados
 * dos catálogos a partir do caminho especificado e processa os comandos fornecidos
 * no ficheiro de entrada.
 *
 * @param path Caminho para os ficheiros de dados que devem ser carregados.
 * @param comandos Caminho para o ficheiro de comandos que será processado.
 */
void exec_programa_principal(char* path, char* comandos);

#endif

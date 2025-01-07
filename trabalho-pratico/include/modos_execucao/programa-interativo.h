/**
 * @file programa-interativo.h
 * @brief Declaração do modo interativo do programa.
 *
 * Este ficheiro contém as declarações necessárias para o modo interativo
 * do programa, onde é possível interagir diretamente com o sistema através
 * de comandos e inputs em tempo real.
 */

#ifndef INTERATIVO_MODE_H
#define INTERATIVO_MODE_H

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
 * @brief Executa o programa no modo interativo.
 *
 * Permite ao utilizador interagir diretamente com o sistema, fornecendo
 * comandos e inputs em tempo real para executar funcionalidades do programa.
 *
 * Esta função controla o fluxo do programa enquanto está no modo interativo.
 */
void exec_programa_interativo();

#endif

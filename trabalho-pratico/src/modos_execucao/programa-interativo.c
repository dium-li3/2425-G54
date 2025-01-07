#include <stdio.h>
#include <string.h>
#include <glib.h>
#include <stdlib.h>
#include <unistd.h>

#include "entidades/musics.h"   
#include "entidades/users.h"
#include "entidades/artists.h"
#include "entidades/albums.h"
#include "entidades/stats.h"

#include "catalogos/catalogo_musics.h"
#include "catalogos/catalogo_artists.h"
#include "catalogos/catalogo_users.h"
#include "catalogos/catalogo_albums.h"

#include "manager_dados/utils.h"
#include "manager_dados/querier.h"
#include "manager_dados/parser.h"
#include "manager_dados/validation.h"

#include "modos_execucao/programa-interativo.h"

void clear_terminal() {
    printf("\033[H\033[J"); 
}

void print_menu() {
    printf("\n======== Modo Interativo =========\n");
    printf("1. Executar Query 1\n");
    printf("2. Executar Query 2\n");
    printf("3. Executar Query 3\n");
    printf("0. Sair\n");
    printf("==================================\n");
    printf("Escolhe uma opção: ");
}

void read_command_output(int num_pedidos) {
    // Prepare the file path
    char file_path[256];
    snprintf(file_path, sizeof(file_path), "resultados/command%d_output.txt", num_pedidos);

    // Open the file
    FILE *file = fopen(file_path, "r");
    if (!file) {
        fprintf(stderr, "Erro: Não foi possível abri o ficheiro '%s'. Por favor verifique ele existe.\n", file_path);
        return;
    }

    printf("\n============= OUTPUT =============\n\n");
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file)) {
        printf("%s\n", buffer); 
    }
    printf("==================================\n");

    fclose(file);
}


void exec_programa_interativo() {

int num_pedidos = 1;

clear_terminal();

char path[256];
printf("Insira o caminho para o dataset (ou pressione Enter para escolher o default '../../fase2-small/small/dataset/com_erros'):");
if (fgets(path, sizeof(path), stdin) == NULL) {
    perror("Falha ao ler input");
    exit(EXIT_FAILURE);
}

path[strcspn(path, "\n")] = 0;

if (strlen(path) == 0) {
    strcpy(path, "../../fase2-small/small/dataset/com_erros");
}

if (access(path, F_OK) != 0) {
    fprintf(stderr, "Error: Caminho '%s' não existe. Por favor confirme e tente de novo.\n", path);
    exit(EXIT_FAILURE);
}

ARTISTS_CATALOG artists_hashtable = create_artists_catalog();
MUSICS_CATALOG musics_hashtable = create_musics_catalog(); 
USERS_CATALOG users_hashtable = create_users_catalog();
ALBUMS_CATALOG album_hashtable = create_albums_catalog();
STATS *stats = create_statistics();

//PARA LER O ARTISTS.CSV
size_t tamanho_artists = strlen(path) + strlen("artists.csv");
char *artists_path = malloc(tamanho_artists + sizeof(char) + 1);
if (artists_path == NULL) printf("Falha\n");
strcpy(artists_path, path);
strcat(artists_path, "/artists.csv");
FILE *artists_file = fopen(artists_path, "r"); 
if (artists_file == NULL) perror("Falha");

//PARA LER O MUSICS.CSV
size_t tamanho_musics = strlen(path) + strlen("musics.csv");
char *musics_path = malloc(tamanho_musics + sizeof(char) + 1);
if (musics_path == NULL) printf("Falha\n");
strcpy(musics_path, path);
strcat(musics_path, "/musics.csv");
FILE *musics_file = fopen(musics_path, "r"); 
if (musics_file == NULL) perror("Falha");

//PARA LER O USERS.CSV
size_t tamanho_users = strlen(path) + strlen("users.csv");
char *users_path = malloc(tamanho_users + sizeof(char) + 1);
if (users_path == NULL) printf("Falha\n");
strcpy(users_path, path);
strcat(users_path, "/users.csv");
FILE *users_file = fopen(users_path, "r"); 
if (users_file == NULL) perror("Falha");

//PARA LER O ALBUMS.CSV
size_t tamanho_albums = strlen(path) + strlen("albums.csv");
char *albums_path = malloc(tamanho_albums + sizeof(char) + 1);
if (albums_path == NULL) printf("Falha\n");
strcpy(albums_path, path);
strcat(albums_path, "/albums.csv");
FILE *albums_file = fopen(albums_path, "r"); 
if (albums_file == NULL) perror("Falha");

//PARA LER O HISTORY.CSV
size_t tamanho_history = strlen(path) + strlen("history.csv");
char *history_path = malloc(tamanho_history + sizeof(char) + 1);
if (history_path == NULL) printf("Falha\n");
strcpy(history_path, path);
strcat(history_path, "/history.csv");
FILE *history_file = fopen(history_path, "r"); 
if (history_file == NULL) perror("Falha");

parser(artists_hashtable, musics_hashtable, users_hashtable, album_hashtable, stats, artists_file, musics_file, users_file, history_file, albums_file);

printf("Dataset carregado.\n");

int option = -1;
    do {
        print_menu();

        if (scanf("%d", &option) != 1) {
            printf("Input inválido. Por favor insira um número.\n");
            while (getchar() != '\n'); 
            continue;
        }

        switch (option) {
            case 1: {
                char id[256]; 
                printf("Por favor insira o ID que deseja para a Query 1: ");
                while (getchar() != '\n'); 
                if (fgets(id, sizeof(id), stdin) == NULL) {
                    printf("Input inválido. Por favor tente novamente.\n");
                    break;
                }

                id[strcspn(id, "\n")] = 0;

                int mode = 0;
                printf("Escolha o formato do output:\n");
                printf("1. Modo Normal (;)\n");
                printf("2. Modo Especial (=)\n");
                printf("Insira o modo que deseja (1 ou 2): ");
                if (scanf("%d", &mode) != 1 || (mode != 1 && mode != 2)) {
                    printf("Escolha inválida. Tente outra vez.\n");
                    while (getchar() != '\n');
                    break;
                }
                while (getchar() != '\n'); 

                char command[300];
                if (mode == 1) {
                    snprintf(command, sizeof(command), "1 %s", id);
                } else if (mode == 2) {
                    snprintf(command, sizeof(command), "1S %s", id);
                }

                exec_line(artists_hashtable, musics_hashtable, users_hashtable, album_hashtable, stats, command, num_pedidos);

                printf("\nQuery 1 executada com o ID: %s\n", id);

                read_command_output(num_pedidos);

                num_pedidos++;
                break;
            }
            case 2: {
                int n_artists; 
                char country[256]; 
                char command[300];

                printf("Por favor insira o número de artistas para a Query 2: ");
                if (scanf("%d", &n_artists) != 1 || n_artists <= 0) {
                    printf("Número inválido. Por favor tente novamente.\n");
                    while (getchar() != '\n'); 
                    break;
                }
                while (getchar() != '\n'); 

                printf("Por favor insira o país (ou pressione Enter para ignorar): ");
                if (fgets(country, sizeof(country), stdin) == NULL) {
                    printf("Input inválido. Por favor tente novamente.\n");
                    break;
                }
                country[strcspn(country, "\n")] = 0; 

                int mode = 0;
                printf("Escolha o formato do output:\n");
                printf("1. Modo Normal (;)\n");
                printf("2. Modo Especial (=)\n");
                printf("Insira o modo que deseja (1 ou 2): ");
                if (scanf("%d", &mode) != 1 || (mode != 1 && mode != 2)) {
                    printf("Escolha inválida. Tente outra vez.\n");
                    while (getchar() != '\n');
                    break;
                }
                while (getchar() != '\n'); 

                if (mode == 1) {
                    if (strlen(country) > 0) {
                    snprintf(command, sizeof(command), "2 %d %s", n_artists, country);
                    } else {
                    snprintf(command, sizeof(command), "2 %d", n_artists);
                    }
                } else if (mode == 2) {
                    if (strlen(country) > 0) {
                    snprintf(command, sizeof(command), "2S %d %s", n_artists, country);
                    } else {
                    snprintf(command, sizeof(command), "2S %d", n_artists);
                    }
                }

                exec_line(artists_hashtable, musics_hashtable, users_hashtable, album_hashtable, stats, command, num_pedidos);

                printf("Query 2 executada com os parâmetros: Número de Artistas = %d, País = %s\n", n_artists, (strlen(country) > 0) ? country : "Sem filtro de país");

                read_command_output(num_pedidos);

                num_pedidos++;
                break;
            }
            case 3:{
                int min_age, max_age;
                char command[300];

                printf("Por favor insira a idade mínima para a Query 3: ");
                if (scanf("%d", &min_age) != 1 || min_age < 0) {
                    printf("Idade mínima inválida. Por favor tente novamente.\n");
                    while (getchar() != '\n'); 
                    break;
                }

                printf("Por favor insira a idade máxima para a Query 3: ");
                if (scanf("%d", &max_age) != 1 || max_age < min_age) {
                    printf("Idade máxima inválida ou menor que a idade mínima. Por favor tente novamente.\n");
                    while (getchar() != '\n'); 
                    break;
                }
                while (getchar() != '\n'); 


                int mode = 0;
                printf("Escolha o formato do output:\n");
                printf("1. Modo Normal (;)\n");
                printf("2. Modo Especial (=)\n");
                printf("Insira o modo que deseja (1 ou 2): ");
                if (scanf("%d", &mode) != 1 || (mode != 1 && mode != 2)) {
                    printf("Escolha inválida. Tente outra vez.\n");
                    while (getchar() != '\n');
                    break;
                }
                while (getchar() != '\n'); 

                if (mode == 1) {
                    snprintf(command, sizeof(command), "3 %d %d", min_age, max_age);
                } else if (mode == 2) {
                    snprintf(command, sizeof(command), "3S %d %d", min_age, max_age);
                }

                exec_line(artists_hashtable, musics_hashtable, users_hashtable, album_hashtable, stats, command, num_pedidos);

                printf("\nQuery 3 executada com os parâmetros: Idade Mínima = %d, Idade Máxima = %d\n", min_age, max_age);

                read_command_output(num_pedidos);

                num_pedidos++;
                break;
            }
            case 0:
                printf("A sair do programa...\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (option != 0);


fclose(artists_file);
fclose(musics_file);
fclose(users_file);
fclose(history_file);
fclose(albums_file);

free(artists_path);
free(musics_path);
free(users_path);
free(history_path);
free(albums_path);

free_artists_catalog(artists_hashtable);
free_musics_catalog(musics_hashtable);
free_user_catalog(users_hashtable);
free_albums_catalog(album_hashtable);
free_statistics(stats);
}
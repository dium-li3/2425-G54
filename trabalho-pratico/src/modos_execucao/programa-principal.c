#include <stdio.h>
#include <string.h>
#include <glib.h>
#include <stdlib.h>

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

void exec_programa_principal(char* path, char* comandos)
{
ARTISTS_CATALOG artists_hashtable = create_artists_catalog();
MUSICS_CATALOG musics_hashtable = create_musics_catalog(); 
USERS_CATALOG users_hashtable = create_users_catalog();
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

FILE *qs = fopen(comandos, "r");
if (qs == NULL) perror("Falha");

parser(artists_hashtable, musics_hashtable, users_hashtable, stats, artists_file, musics_file, users_file);

querier(artists_hashtable,musics_hashtable,users_hashtable, stats,qs);

fclose(artists_file);
fclose(musics_file);
fclose(users_file);
fclose(qs);

free(artists_path);
free(musics_path);
free(users_path);

free_artists_catalog(artists_hashtable);
free_musics_catalog(musics_hashtable);
free_user_catalog(users_hashtable);
free_statistics(stats);
}
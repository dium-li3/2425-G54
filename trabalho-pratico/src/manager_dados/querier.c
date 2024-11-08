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

#include "queries/query1.h"
#include "queries/query2.h"
#include "queries/query3.h"

void querier(ARTISTS_CATALOG artists, MUSICS_CATALOG musics, USERS_CATALOG users, STATS *stats, FILE *input)
{
int count = 1;
char linha[1024];
    while (fgets(linha, sizeof(linha), input) != NULL) 
    {
        exec_line(artists, musics, users, stats, linha, count);
        count++;
    }
}

void exec_line(ARTISTS_CATALOG artists, MUSICS_CATALOG musics, USERS_CATALOG users, STATS *stats, char *linha, int count){
    
        linha[strcspn(linha, "\n")] = '\0';
        char *query, *args;
        query = strsep(&linha, " ");
        args = (linha != NULL) ? linha : "";
        if(strcmp(query, "1") == 0)
        {
            execute_query1(count, args, users);
        }
        else if(strcmp(query, "2") == 0)
        {
            execute_query2(count, args, stats);
        }
        if(strcmp(query, "3") == 0)
        {
            execute_query3(count, args, stats);
        }
  
}
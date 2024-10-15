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

#include "queries/query2.h"

void execute_query2(int numlinha, char *arg, STATS *stats)
{
    //---------------------ESCREVER FICHEIRO---------------------
    char query2_path[60];
    char numero[10];
    sprintf(numero, "%d", numlinha);
    strcpy(query2_path, "resultados/command");
    strcat(query2_path, numero);
    strcat(query2_path, "_output.txt");

    char *query2_ficheiro = strdup(query2_path);
    FILE *ficheiro = fopen(query2_ficheiro, "w");
    if (ficheiro == NULL)
    {
        perror("Erro ao abrir o arquivo de erros");
        free(query2_ficheiro);
    }
    //----------------------------------------------------------

    //---------------------BUSCA DE ARGUMENTOS------------------
    char *number_of_artists, *country;
    number_of_artists = strsep(&arg, " ");
    country = (arg != NULL) ? arg : "";

    int number = atoi(number_of_artists);
    //----------------------------------------------------------

    GArray *list_artists = get_artists_array(stats);
    
    g_array_sort(list_artists, sort_DiscographyTime);

    if (list_artists->len == 0){
        fprintf(ficheiro,"\n");
    }

    if (strcmp(country,"") == 0)
    {
        for (int i = 0; i < number; i++)
        {
            ARTIST artist = g_array_index(list_artists, ARTIST, i);
            fprintf(ficheiro, "%s;%s;%s;%s\n",getArtistName(artist),getArtistType(artist),convert_seconds_to_duration(getDiscographyDuration(artist)),getArtistCountry(artist));
        }
    }
    else
    {
        removeQuotes(country);
        int count_artists = 0;
        for (int i = 0; i < list_artists->len; i++)
        {
            ARTIST artist = g_array_index(list_artists, ARTIST, i);
            if(strcmp(getArtistCountry(artist),country)==0){
                fprintf(ficheiro, "%s;%s;%s;%s\n",getArtistName(artist),getArtistType(artist),convert_seconds_to_duration(getDiscographyDuration(artist)),getArtistCountry(artist));
                count_artists++;
            }
            if (count_artists>=number) break;
        }
    }
    
    fclose(ficheiro);  
    free(query2_ficheiro);
}
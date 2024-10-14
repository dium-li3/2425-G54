#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <glib.h>

#include "entidades/musics.h"   
#include "entidades/users.h"
#include "entidades/artists.h"
#include "entidades/stats.h"

#include "catalogos/catalogo_musics.h"
#include "catalogos/catalogo_artists.h"
#include "catalogos/catalogo_users.h"

#include "manager_dados/utils.h"

// Funções de Validação de Parâmetros ///////////////////////////////////////////

int data_valida(char *data) 
{
    int ano, mes, dia;
    if (sscanf(data, "%4d/%2d/%2d", &ano, &mes, &dia) == 3)
    {
        if (ano >= 1900 && ano <= 2024 && dia <= 31 && dia >= 1 && mes >= 1 && mes <= 12)
        {
            if ((ano == 2024 && mes > 9) || (ano == 2024 && mes == 9 && dia > 9))  return 0;
            return 1;
        }          
    }
    return 0;
}

int duracao_valida(char *duracao) 
{
    int horas, minutos, segundos;
    if (sscanf(duracao, "%2d:%2d:%2d", &horas, &minutos, &segundos) == 3)
    {
        if (horas <= 99 && horas >= 0 && minutos >= 0 && minutos <= 59 && segundos >= 0 && segundos <= 59)
            return 1;
    }
    return 0;
}

int caracter_valido(char c) {
    return (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9');
}

int dominio_valido(char *part) {
    while (*part) {
        if (!(*part >= 'a' && *part <= 'z')) {
            return 0;
        }
        part++;
    }
    return 1;
}

int verifica_email(char *email) {
    char username[100], domain[50], tld[20];
    if (sscanf(email, "%99[^@]@%49[^.].%19s", username, domain, tld) == 3) {
        for (char *c = username; *c != '\0'; c++) {
            if (!caracter_valido(*c)) {
                return 0; 
            }
        }
        if (strlen(username) < 1) return 0;
        if (!dominio_valido(domain) || strlen(domain) < 1) {
            return 0;
        }
        if (strlen(tld) < 2 || strlen(tld) > 3 || !dominio_valido(tld)) {
            return 0;
        }

        return 1;
    }
    return 0;
}

int verifica_subscription_type(char *s_type){
    if (strcmp(s_type,"normal") == 0 || strcmp(s_type,"premium") == 0) return 1;
return 0;    
}

int verifica_liked_musics(char *liked_musics, MUSICS_CATALOG catalogo_musics){

    format_string(liked_musics);

    char *music_id = strtok(liked_musics, ",");

     while (music_id != NULL) {

        MUSIC music = get_music_by_key(catalogo_musics, music_id);

        if(!music) return 0; 

        music_id = strtok(NULL, ",");
    }

return 1;
}

int verifa_if_is_list(char *id_artists){

    if (id_artists[0] == '[')
        return 1;

return 0;
}

int verifica_music_artist(char *artists_id, ARTISTS_CATALOG catalogo_artists){

    format_string(artists_id);

    char *artist_id = strtok(artists_id, ",");

    while (artist_id != NULL) {
        ARTIST artist = get_artist_by_key(catalogo_artists,artist_id);

        if(!artist) return 0; 

        artist_id = strtok(NULL, ",");
    }
    
return 1;
}

int verifica_artista_ou_banda(char *id_constituent, char *artist_type){
    if (strcmp(artist_type,"individual") == 0){
        if(strcmp(id_constituent,"[]") != 0) return 0;
    }
return 1;
}

// Funções de Validação de Entidades ///////////////////////////////////////////

int valid_entity(int flag,GArray *parameters_array,ARTISTS_CATALOG catalogo_artists,MUSICS_CATALOG catalogo_musics){

    int check = 1;

    if (flag == 1) //ARTIST
    {
        char *id = strdup(g_array_index(parameters_array, char *, 0));
        char *id_constituent = strdup(g_array_index(parameters_array, char *, 4));
        char *type = strdup(g_array_index(parameters_array, char *, 6));

        if(strcmp(id,"id") == 0) check = 0;
        if (verifica_artista_ou_banda(id_constituent,type) == 0) check = 0;

        free(id);
        free(id_constituent);
        free(type);
    }
    else if(flag == 2) //MUSIC
    {
        char *duration = strdup(g_array_index(parameters_array, char *, 3));
        char *year = strdup(g_array_index(parameters_array, char *, 5));
        char *artist_ids = strdup(g_array_index(parameters_array, char *, 2));

        if(duracao_valida(duration) == 0)
            check = 0;
        if (atoi(year) > 2024) 
            check = 0; 
        if (verifa_if_is_list(artist_ids) == 0)
            check = 0;
        else if (verifica_music_artist(artist_ids, catalogo_artists) == 0)
            check = 0;

        free(duration);
        free(year);
        free(artist_ids);
    }
    else if(flag == 3) // USER
    {
        char *birth_date = strdup(g_array_index(parameters_array, char *, 4));
        char *email = strdup(g_array_index(parameters_array, char *, 1));
        char *subscription_type = strdup(g_array_index(parameters_array, char *, 6));
        char *liked_musics = strdup(g_array_index(parameters_array, char *, 7));

        if(data_valida(birth_date) == 0)
            check = 0;
        if(verifica_email(email) == 0)
            check = 0;
        if (verifica_subscription_type(subscription_type) == 0)
            check = 0;
        if (verifica_liked_musics(liked_musics,catalogo_musics) == 0)
            check = 0;

        free(email);
        free(birth_date);
        free(subscription_type);
        free(liked_musics);
    }
    else return 0;

return check;
}
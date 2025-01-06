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
#include "manager_dados/output.h"

#include "queries/query1.h"

void execute_query1(int numlinha, char *arg, int output_flag, USERS_CATALOG users, ARTISTS_CATALOG artists)
{
    USER user = get_user_by_key(users, arg);
    ARTIST artist = get_artist_by_key(artists, arg);

    if (user){

        char *email = getEmail(user);
        char *first_name = getFirstName(user);
        char *last_name = getLastName(user);
        int age = getAge(user);
        char *country = getCountry(user);

        write_query1_user_output(numlinha,output_flag,email,first_name,last_name,age,country);

        free(email);
        free(first_name);
        free(last_name);
        free(country);

    }
    else if (artist){

        char *name = getArtistName(artist);
        char *type = getArtistType(artist);
        char *country = getArtistCountry(artist);
        int individual_albuns = getIndividualAlbuns(artist);
        double artist_recipe = getArtistRecipe(artist);

        write_query1_artist_output(numlinha,output_flag,name,type,country,individual_albuns,artist_recipe);

        free(name);
        free(type);
        free(country);

    }
    else write_null(numlinha);
}
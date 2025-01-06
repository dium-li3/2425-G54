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

#include "queries/query2.h"

int process_artist(int numlinha, int flag, ARTIST artist, char *country_filter) {
    char *artistName = getArtistName(artist);
    char *artistType = getArtistType(artist);
    char *duration = convert_seconds_to_duration(getDiscographyDuration(artist));
    char *artistCountry = getArtistCountry(artist);

    int is_match = (country_filter == NULL || strcmp(artistCountry, country_filter) == 0);

    if (is_match) {
        write_query2_output(numlinha, flag, artistName, artistType, duration, artistCountry);
    }

    free(artistName);
    free(artistType);
    free(duration);
    free(artistCountry);

    return is_match;
}

void execute_query2(int numlinha, int flag, char *arg, STATS *stats) {
    //---------------------BUSCA DE ARGUMENTOS------------------
    char *number_of_artists, *country;
    number_of_artists = strsep(&arg, " ");
    country = (arg != NULL) ? arg : "";

    int number = atoi(number_of_artists);
    //----------------------------------------------------------

    GArray *list_artists = get_artists_array(stats);
    g_array_sort(list_artists, sort_DiscographyTime);

    if (list_artists->len == 0 || number == 0) {
        write_null(numlinha);
        g_array_free(list_artists, TRUE);
        return;
    }

    // Filter and process artists
    char *country_filter = (strcmp(country, "") == 0) ? NULL : country;
    if (country_filter) removeQuotes(country_filter);

    int count = 0;
    for (int i = 0; i < list_artists->len && count < number; i++) {
        ARTIST artist = g_array_index(list_artists, ARTIST, i);
        if (process_artist(numlinha, flag, artist, country_filter)) {
            count++;
        }
    }

    g_array_free(list_artists, TRUE);
}

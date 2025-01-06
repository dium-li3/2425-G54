#include <stdio.h>
#include <string.h>
#include <glib.h>
#include <stdlib.h>

#include "entidades/musics.h"   
#include "entidades/users.h"
#include "entidades/artists.h"
#include "entidades/stats.h"
#include "entidades/genero_musical.h"
#include "entidades/listening_time.h"

#include "catalogos/catalogo_musics.h"
#include "catalogos/catalogo_artists.h"
#include "catalogos/catalogo_users.h"

#include "manager_dados/utils.h"
#include "manager_dados/output.h"

#include "queries/query6.h"

/*
void execute_query6(int numlinha, int flag, char *arg, USERS_CATALOG users_catalog) {
    //---------------------BUSCA DE ARGUMENTOS------------------
    char *user_id, *year, *number_artists;
    user_id = strsep(&arg, " ");
    year = strsep(&arg, " ");
    number_artists = (arg != NULL) ? arg : "";

    int year_stats = atoi(year);
    int number = 0;
    if (number_artists != NULL) number = atoi(number_artists);
    //----------------------------------------------------------

    // Buscar o utilizador
    USER user = get_user_by_key(users_catalog, user_id);
    if (!user) {
        write_null(numlinha);
        return;
    }

    // Obter estatísticas do ano
    USER_STATISTICS user_stats = get_user_statistics_by_year(user, year_stats);
    if (!user_stats) {
        write_null(numlinha);
        return;
    }

    int unique_musics_listened = get_unique_musics_listened(user_stats);

    char *total_listening_time = get_listening_time_total(user_stats);
    
    GHashTableIter iter;
    gpointer key, value;

    // Determinar o gênero favorito com desempate por ordem alfabética
    char *favorite_genre = NULL; int max_genre_count = 0;
    g_hash_table_iter_init(&iter, get_genre_count_table(user_stats));
    while (g_hash_table_iter_next(&iter, &key, &value)) {
        int *genre_count = (int *)value;
        char *genre = (char *)key;

        if (*genre_count > max_genre_count || (*genre_count == max_genre_count && strcmp(genre, favorite_genre) > 0)) {
            max_genre_count = *genre_count;
            favorite_genre = genre;
        }
    }

    // Determinar o álbum favorito com desempate por ordem alfabética
    int favorite_album = -1, max_album_count = 0;
    g_hash_table_iter_init(&iter, get_album_count_table(user_stats));
    while (g_hash_table_iter_next(&iter, &key, &value)) {
        int *album_id = (int *)key;
        int *album_count = (int *)value;

        if (*album_count > max_album_count || (*album_count == max_album_count && *album_id < favorite_album)) {
            max_album_count = *album_count;
            favorite_album = *album_id;
        }
    }
    char *favorite_album_id = malloc(10);
    sprintf(favorite_album_id, "AL%06d", favorite_album);

    // Determinar o dia com mais músicas reproduzidas (desempate por data mais recente)
    int max_daily_count = 0, favorite_day = 0;
    g_hash_table_iter_init(&iter, get_daily_listening_time_table(user_stats));
    while (g_hash_table_iter_next(&iter, &key, &value)) {
        int *day = (int *)key;
        int *daily_count = (int *)value;

        if (*daily_count > max_daily_count || (*daily_count == max_daily_count && *day > favorite_day)) {
            max_daily_count = *daily_count;
            favorite_day = *day;
        }
    }
    int month_of_year = 0, day_of_year = 0;
    calculate_month_and_day(year_stats, favorite_day, &month_of_year, &day_of_year);
    char formatted_date[11];
    snprintf(formatted_date, sizeof(formatted_date), "%04d/%02d/%02d", year_stats, month_of_year, day_of_year);

    // Determinar a hora mais ouvida (desempate pela hora mais cedo no dia)
    int max_hourly_count = 0, favorite_hour = 0;
    g_hash_table_iter_init(&iter, get_hourly_listening_time_table(user_stats));
    while (g_hash_table_iter_next(&iter, &key, &value)) {
        int *hour = (int *)key;
        int *hourly_count = (int *)value;

        if (*hourly_count > max_hourly_count || (*hourly_count == max_hourly_count && *hour < favorite_hour)) {
            max_hourly_count = *hourly_count;
            favorite_hour = *hour;
        }
    }
    char formatted_hour[3]; 
    snprintf(formatted_hour, 3, "%02d", favorite_hour);

    // Determinar artistas
    GHashTable *listening_times = get_listening_times(user_stats);
    GArray *artist_entries = g_array_new(FALSE, FALSE, sizeof(ArtistListeningTime));

    g_hash_table_iter_init(&iter, listening_times);
    while (g_hash_table_iter_next(&iter, &key, &value)) {
        g_array_append_val(artist_entries, value);
    }

    if (artist_entries->len > 1) g_array_sort(artist_entries, (GCompareFunc)compare_listening_time);
    
    ArtistListeningTime top_entry = g_array_index(artist_entries, ArtistListeningTime, 0);
    char *top_artist = strdup(getArtistIdFromListeningTime(top_entry));

    GArray *top_artists = g_array_new(FALSE, FALSE, sizeof(char *));
    int count = 0;

    for (guint i = 0; i < artist_entries->len && count < number; i++) {
        ArtistListeningTime entry = g_array_index(artist_entries, ArtistListeningTime, i);
        char *artist_id = getArtistIdFromListeningTime(entry);

        int distinct_songs = getUniqueMusicCount(entry);
        int listening_time = getListeningTime(entry);
        char *duration_listening = convert_seconds_to_duration(listening_time);

        char *formatted_string;
        if (flag == 1) {
            formatted_string = g_strdup_printf("%s;%d;%s", artist_id, distinct_songs, duration_listening);
        } else {
            formatted_string = g_strdup_printf("%s=%d=%d", artist_id, distinct_songs, listening_time);
        }

        g_array_append_val(top_artists, formatted_string);

        free(artist_id);
        free(duration_listening);
        count++;
    }

    write_query6_output(numlinha,flag,total_listening_time,unique_musics_listened,top_artist,formatted_date,favorite_genre,favorite_album_id,formatted_hour,top_artists);

    for (guint i = 0; i < top_artists->len; i++) {
    char *artist_string = g_array_index(top_artists, char *, i);
    free(artist_string);
    }
    g_array_free(artist_entries, TRUE);
    g_array_free(top_artists, TRUE);
    free(top_artist);
}
*/
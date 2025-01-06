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

#include "queries/query4.h"

/*
gint compare_artist_listening_time(gconstpointer a, gconstpointer b) {
    const ArtistListeningTime artist_a = *(const ArtistListeningTime *)a;
    const ArtistListeningTime artist_b = *(const ArtistListeningTime *)b;

    int b_list_time = getListeningTime(artist_b);
    int a_list_time = getListeningTime(artist_a);

    return b_list_time - a_list_time;
}

void sort_artists_by_listening_time(GArray *artists_list) {
    if (artists_list) {
        g_array_sort(artists_list, compare_artist_listening_time);
    }
}

void execute_query4(int numlinha, int flag, char *arg, ARTISTS_CATALOG artists, STATS *stats) {
    //---------------------BUSCA DE ARGUMENTOS------------------
    char *begin_date = NULL, *end_date = NULL;

    if (strcmp(arg, "") != 0) {
        begin_date = strsep(&arg, " ");
        end_date = (arg != NULL) ? arg : "";
    }
    //----------------------------------------------------------
    
    if (begin_date && end_date) {

        char *current_sunday = get_sunday_from_date(begin_date);
        char *end_sunday = get_sunday_from_date(end_date);

        GArray *top_artists = g_array_new(FALSE, FALSE, sizeof(ArtistListeningTime));

        while (compare_dates(current_sunday, end_sunday) <= 0) {

            GArray *artists_list = g_hash_table_lookup(get_weekly_top_artists(stats), current_sunday);
            if (artists_list) {
                sort_artists_by_listening_time(artists_list);

                for (guint i = 0; i < artists_list->len && i < 10; i++) {
                    ArtistListeningTime artist_time = g_array_index(artists_list, ArtistListeningTime, i);
                    g_array_append_val(top_artists, artist_time);
                }
            } 

            char *next_sunday = get_next_sunday(current_sunday);
            free(current_sunday);
            current_sunday = next_sunday;
        }

        // Contar aparições dos artistas
        GHashTable *artist_counts = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, g_free);
        for (guint i = 0; i < top_artists->len; i++) {
            ArtistListeningTime artist_time = g_array_index(top_artists, ArtistListeningTime, i);
            char *artist_id = getArtistIdFromListeningTime(artist_time);

            int *count = g_hash_table_lookup(artist_counts, artist_id);
            if (!count) {
                count = malloc(sizeof(int));
                *count = 0;
                g_hash_table_insert(artist_counts, strdup(artist_id), count);
            }
            (*count)++;
            free(artist_id);
        }

        char *top_artist_id = NULL;
        int max_count = 0;

        GHashTableIter iter;
        gpointer key, value;
        g_hash_table_iter_init(&iter, artist_counts);

        while (g_hash_table_iter_next(&iter, &key, &value)) {
            char *artist_id = (char *)key;
            int *count = (int *)value;

            if (*count > max_count || (top_artist_id && *count == max_count && strcmp(artist_id, top_artist_id) < 0)) {
                top_artist_id = artist_id;
                max_count = *count;
            }
        }

        if (top_artist_id) {
            ARTIST top_artist = get_artist_by_key(artists, top_artist_id);
            if (top_artist) {
                char *artist_type = getArtistType(top_artist);

                write_query4_output(numlinha, flag, top_artist_id, artist_type, max_count);

                free(artist_type);
            } else {
                write_null(numlinha);
            }
        } else {
            write_null(numlinha);
        }

        // Cleanup
        g_hash_table_destroy(artist_counts);
        g_array_free(top_artists, TRUE);
        free(current_sunday);
        free(end_sunday);
    } else {
        GHashTable *weekly_top_artists = get_weekly_top_artists(stats);
        GHashTableIter iter;
        gpointer key, value;

        GHashTable *artist_counts = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, g_free);
        g_hash_table_iter_init(&iter, weekly_top_artists);

        while (g_hash_table_iter_next(&iter, &key, &value)) {
            GArray *artists_list = (GArray *)value;
            for (guint i = 0; i < artists_list->len && i < 10; i++) {
                ArtistListeningTime artist_time = g_array_index(artists_list, ArtistListeningTime, i);
                char *artist_id = getArtistIdFromListeningTime(artist_time);

                int *count = g_hash_table_lookup(artist_counts, artist_id);
                if (!count) {
                    count = malloc(sizeof(int));
                    *count = 0;
                    g_hash_table_insert(artist_counts, strdup(artist_id), count);
                }
                (*count)++;
                free(artist_id);
            }
        }

        // Encontrar o artista mais mencionado
        char *top_artist_id = NULL;
        int max_count = 0;

        g_hash_table_iter_init(&iter, artist_counts);

        while (g_hash_table_iter_next(&iter, &key, &value)) {
            char *artist_id = (char *)key;
            int *count = (int *)value;

            if (*count > max_count || (top_artist_id && *count == max_count && strcmp(artist_id, top_artist_id) < 0)) {
                top_artist_id = artist_id;
                max_count = *count;
            }
        }

        if (top_artist_id) {
            ARTIST top_artist = get_artist_by_key(artists, top_artist_id);
            if (top_artist) {
                char *artist_type = getArtistType(top_artist);

                write_query4_output(numlinha, flag, top_artist_id, artist_type, max_count);

                free(artist_type);
            } else {
                write_null(numlinha);
            }
        } else {
            write_null(numlinha);
        }

        // Cleanup
        g_hash_table_destroy(artist_counts);
    }
}
*/
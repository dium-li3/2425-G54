#include <glib.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "entidades/stats.h"
#include "entidades/listening_time.h"
#include "entidades/artists.h"

//STRUCTS//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct stats {
    GHashTable *genre_age_table;
    GArray *artists_array;
    //GHashTable *weekly_top_artists;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//CONSTRUCTOR/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

STATS* create_statistics() {
    STATS* stats = malloc(sizeof(STATS));
    stats->genre_age_table = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, (GDestroyNotify)g_hash_table_destroy);
    stats->artists_array = g_array_new(FALSE, FALSE, sizeof(ARTIST));
    //stats->weekly_top_artists = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, (GDestroyNotify)g_array_free);
    return stats;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//FREES////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void free_statistics(STATS *stats) {
    if (stats) {
        g_hash_table_destroy(stats->genre_age_table);
        //g_hash_table_destroy(stats->weekly_top_artists);

        if (stats->artists_array != NULL) {
            g_array_free(stats->artists_array, TRUE);
        }
        
        free(stats);
    }
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//STATS FUNCTIONS//////////////////////////////////////////////////////////////////////////////////////////////////////////////

GHashTable* get_genre_age_table(STATS *stats) {
    if (stats != NULL) {
        return stats->genre_age_table;
    }
    return NULL;
}

GArray* get_artists_array(STATS *stats) {
    if (stats != NULL) {
        return g_array_copy(stats->artists_array);
    }
    return NULL;
}

void add_artist_to_stats(STATS *stats, ARTIST artist) {
    if (stats != NULL && stats->artists_array != NULL) {
        g_array_append_val(stats->artists_array, artist);
    }
}

/*
GHashTable* get_weekly_top_artists(STATS *stats) {
    return stats->weekly_top_artists;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

gint compare_listening_time(gconstpointer a, gconstpointer b) {

    if (!a || !b) return 0; 

    const ArtistListeningTime artist_a = *(const ArtistListeningTime *)a;
    const ArtistListeningTime artist_b = *(const ArtistListeningTime *)b;

    if (!artist_a || !artist_b) return 0;

    int listening_time_diff = getListeningTime(artist_b) - getListeningTime(artist_a);

    if (listening_time_diff != 0) {
        return listening_time_diff; 
    } else {
        char *id_a = getArtistIdFromListeningTime(artist_a);
        char *id_b = getArtistIdFromListeningTime(artist_b);
        int id_comparison = strcmp(id_b, id_a);
        free(id_a);
        free(id_b);
        return id_comparison; 
    }
}

void organize_weekly_top_artists(STATS *stats) {
    if (!stats) {
        fprintf(stderr, "[ERROR] As stats fornecidas são NULL.\n");
        return;
    }

    GHashTable *weekly_table = get_weekly_top_artists(stats);
    if (!weekly_table) {
        fprintf(stderr, "[ERROR] A tabela weekly_top_artists é NULL.\n");
        return;
    }

    GHashTableIter iter;
    gpointer key, value;

    g_hash_table_iter_init(&iter, weekly_table);
    while (g_hash_table_iter_next(&iter, &key, &value)) {
        GArray *artists_list = (GArray *)value;

        g_array_sort(artists_list, compare_listening_time);

        if (artists_list->len > 10) {
            g_array_set_size(artists_list, 10);
        }
    }
}
*/
#include <glib.h>
#include <stdio.h>
#include <string.h>
#include <glib.h>
#include <stdlib.h>

#include "entidades/stats.h"
#include "entidades/artists.h"  

struct stats {
    GHashTable *genre_age_table;
    GArray *artists_array;       
};

STATS* create_statistics() {
    STATS* stats = malloc(sizeof(STATS));
    stats->genre_age_table = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, (GDestroyNotify)g_hash_table_destroy);

    stats->artists_array = g_array_new(FALSE, FALSE, sizeof(ARTIST));

    return stats;
}

void free_statistics(STATS *stats) {

    g_hash_table_destroy(stats->genre_age_table);

    if (stats->artists_array != NULL) {
        g_array_free(stats->artists_array, TRUE);
    }

    free(stats);
}

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

void print_genre_age_table(STATS *stats) {
    GHashTable *genre_age_table = stats->genre_age_table;
    if (!genre_age_table) {
        printf("No data in genre_age_table.\n");
        return;
    }

    GHashTableIter genre_iter;
    gpointer genre_key, age_table_value;

    g_hash_table_iter_init(&genre_iter, genre_age_table);

    while (g_hash_table_iter_next(&genre_iter, &genre_key, &age_table_value)) {
        char *genre = (char *)genre_key;
        GHashTable *age_table = (GHashTable *)age_table_value;

        printf("Genre: %s\n", genre);

        GHashTableIter age_iter;
        gpointer age_key, likes_value;

        g_hash_table_iter_init(&age_iter, age_table);

        while (g_hash_table_iter_next(&age_iter, &age_key, &likes_value)) {
            int age = *(int *)age_key; 
            int likes = *(int *)likes_value; 

            printf("   Age: %d, Likes: %d\n", age, likes);
        }
        printf("\n");
    }
}
#include <glib.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "entidades/stats.h"
#include "entidades/listening_time.h"
#include "entidades/artists.h"
#include "entidades/genero_musical.h"

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

void increment_likes_for_genre(STATS *stats, int user_age, char *genre) {
    if (!stats || !genre) {
        fprintf(stderr, "[ERROR] Argumentos inválidos para incrementar likes por género.\n");
        return;
    }

    // Obter a tabela de géneros por idades
    GHashTable *genre_age_table = get_genre_age_table(stats);

    // Procurar ou criar a tabela para o género específico
    GHashTable *age_table = g_hash_table_lookup(genre_age_table, genre);

    if (!age_table) {
        age_table = g_hash_table_new_full(g_int_hash, g_int_equal, g_free, g_free);
        g_hash_table_insert(genre_age_table, strdup(genre), age_table);
    }

    // Procurar ou criar o registo para a idade específica
    int *likes = g_hash_table_lookup(age_table, &user_age);
    if (!likes) {
        int *new_age_key = malloc(sizeof(int));
        *new_age_key = user_age;

        int *new_likes = malloc(sizeof(int));
        *new_likes = 1;

        g_hash_table_insert(age_table, new_age_key, new_likes);
    } else {
        (*likes)++;
    }
}

GArray *get_genres_by_age_range(STATS *stats, int min_age, int max_age) {
    if (!stats) {
        fprintf(stderr, "[ERROR] Stats não está inicializado.\n");
        return g_array_new(FALSE, FALSE, sizeof(GENERO_MUSICAL));
    }

    GHashTable *genre_age_table = get_genre_age_table(stats);
    if (!genre_age_table) {
        fprintf(stderr, "[ERROR] A tabela genre_age_table está vazia.\n");
        return g_array_new(FALSE, FALSE, sizeof(GENERO_MUSICAL));
    }

    GArray *generos_musicais_array = g_array_new(FALSE, FALSE, sizeof(GENERO_MUSICAL));
    GHashTableIter genre_iter;
    gpointer genre_key, age_table_value;

    g_hash_table_iter_init(&genre_iter, genre_age_table);
    while (g_hash_table_iter_next(&genre_iter, &genre_key, &age_table_value)) {
        char *genre = (char *)genre_key;
        GHashTable *age_table = (GHashTable *)age_table_value;

        int total_likes = 0;

        for (int age = min_age; age <= max_age; age++) {
            int *likes = g_hash_table_lookup(age_table, &age);
            if (likes) {
                total_likes += *likes;
            }
        }

        if (total_likes > 0) {
            GENERO_MUSICAL genero = criar_genero_musical();
            setGeneroNome(genero, genre);
            setGeneroLikes(genero, total_likes);
            g_array_append_val(generos_musicais_array, genero);
        }
    }

    return generos_musicais_array;
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
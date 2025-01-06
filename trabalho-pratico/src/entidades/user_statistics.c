#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include <string.h>

#include "entidades/user_statistics.h"
#include "entidades/listening_time.h"

/*
struct user_statistics {
    int listening_time;
    GHashTable *listening_times; // Key: int (ID do ArtistListeningTime), Value: ArtistListeningTime
    int unique_musics_listened; // Número de músicas únicas ouvidas
    GHashTable *daily_listening_time; // Key: dia (1-366), Value: int tempo total em segundos
    GHashTable *hourly_listening_time; // Key: hora (1-24), Value: int tempo total em segundos
    GHashTable *genre_count; // Key: char* género, Value: int contador
    GHashTable *album_count; // Key: int album_id, Value: int contador
};

// Criação de uma nova instância de user_statistics
USER_STATISTICS create_user_statistics(void) {
    USER_STATISTICS stats = malloc(sizeof(struct user_statistics));
    stats->listening_time = 0;
    stats->listening_times = g_hash_table_new_full(g_int_hash, g_int_equal, g_free, (GDestroyNotify)destroy_listening_time);
    stats->unique_musics_listened = 0;
    stats->daily_listening_time = g_hash_table_new(g_int_hash, g_int_equal);
    stats->hourly_listening_time = g_hash_table_new(g_int_hash, g_int_equal);
    stats->genre_count = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, free);
    stats->album_count = g_hash_table_new_full(g_int_hash, g_int_equal, g_free, free);

    return stats;
}

// Funções de manipulação para listening time
char* get_listening_time_total(USER_STATISTICS stats) {
    return convert_seconds_to_duration(stats->listening_time);
}

void set_listening_time_total(USER_STATISTICS stats, int listening_time) {
    stats->listening_time += listening_time;
}

// Funções de manipulação para listening_times
GHashTable* get_listening_times(USER_STATISTICS stats) {
    if (!stats) {
        fprintf(stderr, "[ERROR] User statistics are NULL.\n");
        return NULL;
    }
    return stats->listening_times;
}

void add_listening_time_user_stats(USER_STATISTICS stats, int artist_id, ArtistListeningTime lt) {
    int *key = malloc(sizeof(int));
    *key = artist_id;
    g_hash_table_insert(stats->listening_times, key, lt);
}

ArtistListeningTime get_listening_time(USER_STATISTICS stats, int artist_id) {
    return (ArtistListeningTime)g_hash_table_lookup(stats->listening_times, &artist_id);
}

void remove_listening_time(USER_STATISTICS stats, int artist_id) {
    g_hash_table_remove(stats->listening_times, &artist_id);
}

// Funções para unique_musics_listened
int get_unique_musics_listened(USER_STATISTICS stats) {
    return stats->unique_musics_listened;
}

void set_unique_musics_listened(USER_STATISTICS stats) {
    stats->unique_musics_listened += 1;
}

// Funções para daily_listening_time
GHashTable* get_daily_listening_time_table(USER_STATISTICS stats) {
    return stats->daily_listening_time;
}

void add_daily_listening_time(USER_STATISTICS stats, int day) {
    int *existing_musics = g_hash_table_lookup(stats->daily_listening_time, &day);
    if (existing_musics) {
        *existing_musics += 1;
    } else {
        int *new_value = malloc(sizeof(int));
        *new_value = 1;
        g_hash_table_insert(stats->daily_listening_time, g_memdup2(&day, sizeof(int)), new_value);
    }
}

int get_daily_listening_time(USER_STATISTICS stats, int day) {
    int *time = g_hash_table_lookup(stats->daily_listening_time, &day);
    return time ? *time : 0;
}

// Funções para hourly_listening_time
GHashTable* get_hourly_listening_time_table(USER_STATISTICS stats) {
    return stats->hourly_listening_time;
}

void add_hourly_listening_time(USER_STATISTICS stats, int hour, int seconds) {
    int *existing_time = g_hash_table_lookup(stats->hourly_listening_time, &hour);
    if (existing_time) {
        *existing_time += seconds;
    } else {
        int *new_time = malloc(sizeof(int));
        *new_time = seconds;
        g_hash_table_insert(stats->hourly_listening_time, g_memdup2(&hour, sizeof(int)), new_time);
    }
}

int get_hourly_listening_time(USER_STATISTICS stats, int hour) {
    int *time = g_hash_table_lookup(stats->hourly_listening_time, &hour);
    return time ? *time : 0;
}

// Funções para genre_count
GHashTable* get_genre_count_table(USER_STATISTICS stats) {
    if (!stats) {
        fprintf(stderr, "[ERROR] stats é NULL.\n");
        return NULL;
    }
    return stats->genre_count;
}

void add_genre_count(USER_STATISTICS stats, char *genre) {
    int *count = g_hash_table_lookup(stats->genre_count, genre);
    if (count) {
        (*count)++;
    } else {
        int *new_count = malloc(sizeof(int));
        *new_count = 1;
        g_hash_table_insert(stats->genre_count, strdup(genre), new_count);
    }
}

int get_genre_count(USER_STATISTICS stats, char *genre) {
    int *count = g_hash_table_lookup(stats->genre_count, genre);
    return count ? *count : 0;
}

// Funções para album_count
GHashTable* get_album_count_table(USER_STATISTICS stats) {
    if (!stats) {
        fprintf(stderr, "[ERROR] stats é NULL.\n");
        return NULL;
    }
    return stats->album_count;
}

void add_album_count(USER_STATISTICS stats, int album_id) {
    int *count = g_hash_table_lookup(stats->album_count, &album_id);
    if (count) {
        (*count)++;
    } else {
        int *new_count = malloc(sizeof(int));
        *new_count = 1;
        g_hash_table_insert(stats->album_count, g_memdup2(&album_id, sizeof(int)), new_count);
    }
}

int get_album_count(USER_STATISTICS stats, int album_id) {
    int *count = g_hash_table_lookup(stats->album_count, &album_id);
    return count ? *count : 0;
}

// Liberação de memória da estrutura
void destroy_user_statistics(USER_STATISTICS stats) {
    if (!stats) return;

    g_hash_table_destroy(stats->listening_times);
    g_hash_table_destroy(stats->daily_listening_time);
    g_hash_table_destroy(stats->hourly_listening_time);
    g_hash_table_destroy(stats->genre_count);
    g_hash_table_destroy(stats->album_count);

    free(stats);
}
*/
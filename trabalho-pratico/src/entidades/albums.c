#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "entidades/albums.h"
#include "manager_dados/utils.h"

struct album {
    int id;            
    GArray *artists_ids; 
    int year;
};

ALBUM create_album(void) {
    ALBUM new_album = malloc(sizeof(struct album));
    new_album->id = -1;
    new_album->artists_ids = g_array_new(FALSE, FALSE, sizeof(int)); 
    new_album->year = 0;
    return new_album;
}

// Getters
char* get_album_id(ALBUM album) {
    char *formatted_id = malloc(10);
    if (!formatted_id) {
        fprintf(stderr, "[ERROR] Falha ao alocar memória para o ID do álbum.\n");
        return NULL;
    }
    sprintf(formatted_id, "AL%06d", album->id); 
    return formatted_id;
}

GArray* get_album_artists_ids(ALBUM album) {
    if (!album->artists_ids || album->artists_ids->len == 0) {
        return g_array_new(FALSE, FALSE, sizeof(char *));
    }

    GArray *artists_ids_array = g_array_new(FALSE, FALSE, sizeof(char *));

    for (guint i = 0; i < album->artists_ids->len; i++) {
        int artist_id = g_array_index(album->artists_ids, int, i);
        char *formatted_artist_id = malloc(10);
        sprintf(formatted_artist_id, "A%07d", artist_id); 
        g_array_append_val(artists_ids_array, formatted_artist_id);
    }

    return artists_ids_array; 
}

int get_album_year(ALBUM album) { return album->year; }

// Setters
void set_album_id(ALBUM album, char *id) {
    int numeric_id = atoi(id + 2);
    album->id = numeric_id;
}

void set_album_artists_ids(ALBUM album, char *artists_ids_str) {

    g_array_set_size(album->artists_ids, 0);

    char *artist_id_string = strdup(artists_ids_str);
    format_string(artist_id_string);

    GString *copy_of_artists = g_string_new(artist_id_string);
    gchar **tokens = g_strsplit(copy_of_artists->str, ",", -1);

    for (int i = 0; tokens[i] != NULL ; i++)
    {
        int artist_id = atoi(tokens[i] + 1); 
        g_array_append_val(album->artists_ids, artist_id);
    }

    free(artist_id_string);
    g_string_free(copy_of_artists, TRUE);
    g_strfreev(tokens);
}

void set_album_year(ALBUM album, int year) { album->year = year; }

// Free memory
void free_album(ALBUM album) {
    g_array_free(album->artists_ids, TRUE);
    free(album);
}

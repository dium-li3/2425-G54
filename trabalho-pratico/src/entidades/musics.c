#include <stdio.h>
#include <string.h>
#include <glib.h>

#include "entidades/musics.h"

struct music {
    int id;                                 
    GArray *artist_ids;                     
    int album_id;                            
    int duration;                            
    char *genre;                             
    int year;                               
    int streams;                          
};

// FUNCTION TO CREATE AN EMPTY MUSIC //////////////////////////////
MUSIC criar_music(void) {
    MUSIC nova_music = malloc(sizeof(struct music));
    nova_music->id = 0;
    nova_music->artist_ids = g_array_new(FALSE, FALSE, sizeof(int));
    nova_music->album_id = 0;
    nova_music->duration = 0;
    nova_music->genre = NULL;
    nova_music->year = 0;

    return nova_music;
}

// GETTERS /////////////////////////////////////////////////////////

char *getId(MUSIC music) {
    char *formatted_id = malloc(10);
    sprintf(formatted_id, "S%07d", music->id);
    return formatted_id;
}

GArray *getArtistIds(MUSIC music) {
    if (!music->artist_ids || music->artist_ids->len == 0) {
        return g_array_new(FALSE, FALSE, sizeof(char *));
    }

    GArray *artists_ids_array = g_array_new(FALSE, FALSE, sizeof(char *));

    for (guint i = 0; i < music->artist_ids->len; i++) {
        int artist_id = g_array_index(music->artist_ids, int, i);
        char *formatted_artist_id = malloc(10);
        sprintf(formatted_artist_id, "A%07d", artist_id); 
        g_array_append_val(artists_ids_array, formatted_artist_id);
    }

    return artists_ids_array; 
}

char *getAlbumId(MUSIC music) {
    char *formatted_album_id = malloc(10);
    sprintf(formatted_album_id, "AL%06d", music->album_id);
    return formatted_album_id;
}

int getDuration(MUSIC music) {
    return music->duration;
}

char *getGenre(MUSIC music) {
    return strdup(music->genre);
}

int getYear(MUSIC music) {
    return music->year;
}

// SETTERS /////////////////////////////////////////////////////////

void setId(MUSIC music, char *id) {
    music->id = atoi(id + 1); 
}

void setArtistIds(MUSIC music, char *artist_ids_str) {
    g_array_set_size(music->artist_ids, 0); 

    char *artist_ids_copy = strdup(artist_ids_str);
    format_string(artist_ids_copy);

    GString *copy_of_artists = g_string_new(artist_ids_copy);
    gchar **tokens = g_strsplit(copy_of_artists->str, ",", -1);

    for (int i = 0; tokens[i] != NULL; i++) {
        int artist_id = atoi(tokens[i] + 1); 
        g_array_append_val(music->artist_ids, artist_id);
    }

    g_string_free(copy_of_artists, TRUE);
    g_strfreev(tokens);
    free(artist_ids_copy);
}

void setAlbumId(MUSIC music, char *album_id) {
    music->album_id = atoi(album_id + 2); 
}

void setDuration(MUSIC music, char *duration) {
    music->duration = convert_duration_to_seconds(duration); 
}

void setGenre(MUSIC music, char *genre) {
    free(music->genre);
    music->genre = strdup(genre);
}

void setYear(MUSIC music, int year) {
    music->year = year;
}

// FUNCTION TO DESTROY MUSIC ///////////////////////////////////////
void destroi_musics(gpointer data) {
    MUSIC music = (MUSIC)data;

    g_array_free(music->artist_ids, TRUE); 
    free(music->genre);

    free(music);
}

#include <glib.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "entidades/stats.h"
#include "entidades/artists.h"
#include "entidades/listening_time.h"

/*
struct artistlisteningtime {
    int artist_id;
    int listening_time;
    GArray *unique_musics;
};

// CONSTRUCTOR /////////////////////////////////////////////////////////////////////////////////////////////////////////////

ArtistListeningTime createArtistListeningTime() {
    ArtistListeningTime entry = malloc(sizeof(struct artistlisteningtime));
    if (!entry) {
        fprintf(stderr, "Memory allocation failed for ArtistListeningTime\n");
        exit(EXIT_FAILURE);
    }
    entry->artist_id = -1; 
    entry->listening_time = 0;
    entry->unique_musics = g_array_new(FALSE, FALSE, sizeof(int));
    return entry;
}

// LISTENING TIME FUNCTIONS ////////////////////////////////////////////////////////////////////////////////////////////////

int extractArtistId(char *artist_id_str) {
    if (!artist_id_str || strlen(artist_id_str) < 2) {
        fprintf(stderr, "[ERROR] Formato inválido para o ID do artista: %s\n", artist_id_str);
        return -1;
    }

    return atoi(artist_id_str + 1);
}

char *constructArtistId(int artist_id_num) {
    char *artist_id_str = malloc(10);
    if (!artist_id_str) {
        fprintf(stderr, "[ERROR] Falha ao alocar memória para o ID do artista\n");
        exit(EXIT_FAILURE);
    }

    sprintf(artist_id_str, "A%07d", artist_id_num);
    return artist_id_str;
}

void setArtistIdInListeningTime(ArtistListeningTime entry, char *artist_id_str) {
    int artist_id_num = extractArtistId(artist_id_str);
    if (artist_id_num == -1) {
        fprintf(stderr, "[ERROR] ID inválido: %s\n", artist_id_str);
        return;
    }
    entry->artist_id = artist_id_num;
}

char *getArtistIdFromListeningTime(ArtistListeningTime entry) {
    return constructArtistId(entry->artist_id);
}

int getListeningTime(ArtistListeningTime entry) {
    return entry->listening_time;
}

void setListeningTime(ArtistListeningTime entry, int listening_time) {
    entry->listening_time += listening_time;
}

GArray *getUniqueMusics(ArtistListeningTime entry) {
    return entry->unique_musics;
}

int addUniqueMusic(ArtistListeningTime entry, char *music_id) {
    int id = atoi(music_id + 1);
    for (guint i = 0; i < entry->unique_musics->len; i++) {
        if (g_array_index(entry->unique_musics, int, i) == id) {
            return 0; 
        }
    }
    g_array_append_val(entry->unique_musics, music_id);
    return 1;
}

int getUniqueMusicCount(ArtistListeningTime entry) {
    return entry->unique_musics->len;
}

void destroy_listening_time(gpointer data) {
    ArtistListeningTime lt = (ArtistListeningTime)data;
    g_array_free(lt->unique_musics, TRUE);
    free(lt);
}

*/
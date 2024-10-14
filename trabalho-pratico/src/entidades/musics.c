#include <stdio.h>
#include <string.h>
#include <glib.h>

#include "entidades/musics.h"

struct music {
    char *id;                          
    char *title;                   
    char *artist_ids;                              
    char *duration;        
    char *genre;                    
    int year;                                        
    char *lyrics;                
};

// FUNCTION TO CREATE AN EMPTY MUSIC //////////////////////////////

MUSIC criar_music(void)
{
    MUSIC nova_music = malloc(sizeof(struct music));
    nova_music->id = NULL;
    nova_music->title = NULL;
    nova_music->artist_ids = NULL;
    nova_music->duration = NULL;
    nova_music->genre = NULL;
    nova_music->year = 0;
    nova_music->lyrics = NULL;

    return nova_music;
}

//GETTERS/////////////////////////////////////////////////////////

char* getId(MUSIC music) {
    return strdup(music->id);
}

char* getTitle(MUSIC music) {
    return strdup(music->title);
}

char* getArtistIds(MUSIC music) {
    return strdup(music->artist_ids);
}

char* getDuration(MUSIC music) {
    return strdup(music->duration);
}

char* getGenre(MUSIC music) {
    return strdup(music->genre);
}

int getYear(MUSIC music) {
    return music->year;
}

char* getLyrics(MUSIC music) {
    return strdup(music->lyrics);
}

//SETTERS////////////////////////////////////////////////////////

void setId(MUSIC music,char *id) {
    free(music->id);
    music->id = strdup(id);
}

void setTitle(MUSIC music,char *title) {
    free(music->title);
    music->title = strdup(title);
}

void setArtistIds(MUSIC music,char* artist_ids) {
    free(music->artist_ids);
    music->artist_ids = strdup(artist_ids);
}

void setDuration(MUSIC music,char *duration) {
    free(music->duration);
    music->duration = strdup(duration);
}

void setGenre(MUSIC music,char *genre) {
    free(music->genre);
    music->genre = strdup(genre);
}

void setYear(MUSIC music, int year) {
    music->year = year;
}

void setLyrics(MUSIC music,char *lyrics) {
    free(music->lyrics);
    music->lyrics = strdup(lyrics);
}

void destroi_musics(gpointer data) {
    MUSIC music = (MUSIC)data;

    free(music->id);
    free(music->title);
    free(music->artist_ids);
    free(music->duration);
    free(music->genre);
    free(music->lyrics);
    
    free(music);
}
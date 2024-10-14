#ifndef MUSICS_H
#define MUSICS_H

#include <stdio.h>
#include <string.h>
#include <glib.h>

#include "entidades/artists.h"

#include "catalogos/catalogo_musics.h"

#include "manager_dados/utils.h"

typedef struct music *MUSIC;

MUSIC criar_music(void);

char* getId(MUSIC music);
char* getTitle(MUSIC music);
char* getArtistIds(MUSIC music);
char* getDuration(MUSIC music);
char* getGenre(MUSIC music);
int getYear(MUSIC music);
char* getLyrics(MUSIC music);

void setId(MUSIC music, char *id);
void setTitle(MUSIC music, char *title);
void setArtistIds(MUSIC music, char* artist_ids);
void setDuration(MUSIC music, char *duration);
void setGenre(MUSIC music, char *genre);
void setYear(MUSIC music, int year);
void setLyrics(MUSIC music, char *lyrics);

void destroi_musics(gpointer data);

#endif
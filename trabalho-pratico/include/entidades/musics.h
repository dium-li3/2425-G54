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
GArray *getArtistIds(MUSIC music);
char* getAlbumId(MUSIC music);
int getDuration(MUSIC music);
char* getGenre(MUSIC music);
int getYear(MUSIC music);

void setId(MUSIC music, char *id);
void setArtistIds(MUSIC music, char* artist_ids);
void setAlbumId(MUSIC music,char* album_id);
void setDuration(MUSIC music, char *duration);
void setGenre(MUSIC music, char *genre);
void setYear(MUSIC music, int year);

void destroi_musics(gpointer data);

#endif
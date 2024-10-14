#ifndef ARTISTS_H
#define ARTISTS_H

#include <stdio.h>
#include <string.h>
#include <glib.h>
#include <stdlib.h>

#include "catalogos/catalogo_artists.h"

typedef struct artist *ARTIST;

ARTIST criar_artist(void);

// Getter functions
char* getArtistId(ARTIST artist);
char* getArtistName(ARTIST artist);
char* getArtistDescription(ARTIST artist);
char* getRecipePerStream(ARTIST artist);
char* getIdConstituent(ARTIST artist);
char* getArtistCountry(ARTIST artist);
char* getArtistType(ARTIST artist);
int getDiscographyDuration(ARTIST artist);

void setArtistId(ARTIST artist, char *id);
void setArtistName(ARTIST artist, char *name);
void setArtistDescription(ARTIST artist, char *description);
void setRecipePerStream(ARTIST artist, char *recipe_per_stream);
void setIdConstituent(ARTIST artist, char *id_constituent);
void setArtistCountry(ARTIST artist, char *country);
void setArtistType(ARTIST artist, char *type);
void setDiscographyDuration(ARTIST artist, int duration);

void destroi_artists(gpointer data);

#endif
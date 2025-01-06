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
double getRecipePerStream(ARTIST artist);
GArray* getIdConstituents(ARTIST artist);
char* getArtistCountry(ARTIST artist);
char* getArtistType(ARTIST artist);
int getDiscographyDuration(ARTIST artist);
int getIndividualAlbuns(ARTIST artist);
double getArtistRecipe(ARTIST artist);

void setArtistId(ARTIST artist, char *id);
void setArtistName(ARTIST artist, char *name);
void setRecipePerStream(ARTIST artist, char *recipe_per_stream);
void setArtistIdConstituents(ARTIST artist, char *id_constituents_str);
void setArtistCountry(ARTIST artist, char *country);
void setArtistType(ARTIST artist, char *type);
void setDiscographyDuration(ARTIST artist, int duration);
void setIndividualAlbuns(ARTIST artist);
void setArtistRecipe(ARTIST artist, double recipe);

void destroi_artists(gpointer data);

#endif
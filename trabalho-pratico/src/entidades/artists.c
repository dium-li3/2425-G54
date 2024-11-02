#include <stdio.h>
#include <string.h>
#include <glib.h>
#include <stdlib.h>

#include "entidades/artists.h"

struct artist {
    char *id;
    char *name;
    char *description;
    char *recipe_per_stream;
    char *id_constituent;
    char *country;
    char *type;
    int discography_duration;
};

// FUNCTION TO CREATE AN EMPTY ARTIST /////////////////////////////////

ARTIST criar_artist(void)
{
    ARTIST novo_artist = malloc(sizeof(struct artist));
    novo_artist->id = NULL;
    novo_artist->name = NULL;
    novo_artist->description = NULL;
    novo_artist->recipe_per_stream = NULL;
    novo_artist->id_constituent = NULL;
    novo_artist->country = NULL;
    novo_artist->type = NULL;
    novo_artist->discography_duration = 0;

    return novo_artist;
}

// GETTERS ////////////////////////////////////////////////////////////

char* getArtistId(ARTIST artist) {
    return strdup(artist->id);
}

char* getArtistName(ARTIST artist) {
    return strdup(artist->name);
}

char* getArtistDescription(ARTIST artist) {
    return strdup(artist->description);
}

char* getRecipePerStream(ARTIST artist) {
    return strdup(artist->recipe_per_stream);
}

char* getIdConstituent(ARTIST artist) {
    return strdup(artist->id_constituent);
}

char* getArtistCountry(ARTIST artist) {
    return strdup(artist->country);
}

char* getArtistType(ARTIST artist) {
    return strdup(artist->type);
}

int getDiscographyDuration(ARTIST artist) {
    return artist->discography_duration;
}

// SETTERS ////////////////////////////////////////////////////////////

void setArtistId(ARTIST artist, char *id) {
    free(artist->id);
    artist->id = strdup(id);
}

void setArtistName(ARTIST artist, char *name) {
    free(artist->name);
    artist->name = strdup(name);
}

void setArtistDescription(ARTIST artist, char *description) {
    free(artist->description);
    artist->description = strdup(description);
}

void setRecipePerStream(ARTIST artist, char *recipe_per_stream) {
    free(artist->recipe_per_stream);
    artist->recipe_per_stream = strdup(recipe_per_stream);
}

void setIdConstituent(ARTIST artist, char *id_constituent) {
    free(artist->id_constituent);
    artist->id_constituent = strdup(id_constituent);
}

void setArtistCountry(ARTIST artist, char *country) {
    free(artist->country);
    artist->country = strdup(country);
}

void setArtistType(ARTIST artist, char *type) {
    free(artist->type);
    artist->type = strdup(type);
}

void setDiscographyDuration(ARTIST artist, int duration) {
    artist->discography_duration += duration;
}

//////////////////////////////////////////////////////////////

void destroi_artists(gpointer data) {
    ARTIST artist = (ARTIST)data;

    free(artist->id);
    free(artist->name);
    free(artist->description);
    free(artist->recipe_per_stream);
    free(artist->id_constituent);
    free(artist->country);
    free(artist->type);
    
    free(artist);
}
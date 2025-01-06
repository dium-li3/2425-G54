#include <stdio.h>
#include <string.h>
#include <glib.h>
#include <stdlib.h>

#include "entidades/artists.h"

struct artist {
    int id;
    char *name;
    double recipe_per_stream;
    GArray *id_constituent;
    char *country;
    int type; // 1 == "individual", 2 == "group"
    int discography_duration;
    int individual_albuns;
    double recipe;
};

// FUNCTION TO CREATE AN EMPTY ARTIST /////////////////////////////////

ARTIST criar_artist(void) {
    ARTIST novo_artist = malloc(sizeof(struct artist));
    novo_artist->id = -1;
    novo_artist->name = NULL;
    novo_artist->recipe_per_stream = 0.0;
    novo_artist->id_constituent = g_array_new(FALSE, FALSE, sizeof(int));
    novo_artist->country = NULL;
    novo_artist->type = 0;
    novo_artist->discography_duration = 0;
    novo_artist->individual_albuns = 0;
    novo_artist->recipe = 0.0;

    return novo_artist;
}

char* getArtistId(ARTIST artist) {
    char *formatted_id = malloc(10);
    sprintf(formatted_id, "A%07d", artist->id);
    return formatted_id;
}

char* getArtistName(ARTIST artist) {
    return strdup(artist->name);
}

double getRecipePerStream(ARTIST artist) {
    return artist->recipe_per_stream;
}

GArray* getIdConstituents(ARTIST artist) {
    // Verifica se `id_constituents` existe e tem elementos
    if (!artist->id_constituent || artist->id_constituent->len == 0) {
        return g_array_new(FALSE, FALSE, sizeof(char *));
    }

    GArray *constituents_ids_array = g_array_new(FALSE, FALSE, sizeof(char *));

    for (guint i = 0; i < artist->id_constituent->len; i++) {
        int constituent_id = g_array_index(artist->id_constituent, int, i);
        char *formatted_constituent_id = malloc(10);
        sprintf(formatted_constituent_id, "A%07d", constituent_id);
        g_array_append_val(constituents_ids_array, formatted_constituent_id);
    }

    return constituents_ids_array; 
}

char* getArtistCountry(ARTIST artist) {
    return strdup(artist->country);
}

char* getArtistType(ARTIST artist) {
    if (artist->type == 1) {
        return strdup("individual");
    } else if (artist->type == 2) {
        return strdup("group");
    } else {
        return strdup("unknown");
    }
}

int getDiscographyDuration(ARTIST artist) {
    return artist->discography_duration;
}

int getIndividualAlbuns(ARTIST artist) {
    return artist->individual_albuns;
}

double getArtistRecipe(ARTIST artist){
    return artist->recipe;
}

// SETTERS ////////////////////////////////////////////////////////////

void setArtistId(ARTIST artist, char *id) {
    artist->id = atoi(id + 1);
}

void setArtistName(ARTIST artist, char *name) {
    free(artist->name);
    artist->name = strdup(name);
}

void setRecipePerStream(ARTIST artist, char *recipe_per_stream) {
    artist->recipe_per_stream = atof(recipe_per_stream);
}

void setArtistIdConstituents(ARTIST artist, char *id_constituents_str) {

    g_array_set_size(artist->id_constituent, 0);

    char *constituent_id_string = strdup(id_constituents_str);
    format_string(constituent_id_string);

    GString *copy_of_constituents = g_string_new(constituent_id_string);
    gchar **tokens = g_strsplit(copy_of_constituents->str, ",", -1);

    for (int i = 0; tokens[i] != NULL; i++) {
        int constituent_id = atoi(tokens[i] + 1); 
        g_array_append_val(artist->id_constituent, constituent_id);
    }

    free(constituent_id_string);
    g_string_free(copy_of_constituents, TRUE);
    g_strfreev(tokens);
}


void setArtistCountry(ARTIST artist, char *country) {
    free(artist->country);
    artist->country = strdup(country);
}

void setArtistType(ARTIST artist, char *type) {
    if (strcmp(type, "individual") == 0) {
        artist->type = 1;
    } else if (strcmp(type, "group") == 0) {
        artist->type = 2;
    } else {
        artist->type = 0; 
    }
}

void setDiscographyDuration(ARTIST artist, int duration) {
    artist->discography_duration += duration;
}

void setIndividualAlbuns(ARTIST artist) {
    artist->individual_albuns += 1;
}

void setArtistRecipe(ARTIST artist, double recipe) {
    artist->recipe += recipe;
}

//////////////////////////////////////////////////////////////

void destroi_artists(gpointer data) {
    ARTIST artist = (ARTIST)data;

    free(artist->name);
    g_array_free(artist->id_constituent, TRUE);
    free(artist->country);

    free(artist);
}
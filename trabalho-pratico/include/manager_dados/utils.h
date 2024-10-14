#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <string.h>
#include <glib.h>
#include <stdlib.h>

#include "entidades/musics.h"   
#include "entidades/users.h"
#include "entidades/artists.h"
#include "entidades/stats.h"

#include "catalogos/catalogo_musics.h"
#include "catalogos/catalogo_artists.h"
#include "catalogos/catalogo_users.h"

#include "manager_dados/utils.h"

typedef struct artists_catalog *ARTISTS_CATALOG;

typedef struct musics_catalog *MUSICS_CATALOG;

char *create_errors(char *directory);

FILE *create_file(char *errors);

int convert_duration_to_seconds(char *duration);

char* convert_seconds_to_duration(int total_seconds);

int calculate_age(char *birthdate);

void format_string(char *str);

void removeQuotes(char *str);

void remove_newline(char *str);

gint sort_DiscographyTime(gconstpointer a, gconstpointer b);

void update_DiscographyTime(ARTISTS_CATALOG catalogo_artists, char *artist_ids, char *duration_to_add);

gint sort_GeneroMusical(gconstpointer a, gconstpointer b);

void increment_likes_for_genre(STATS *stats, int user_age, char *genre);

void update_statistics_for_genre(STATS *stats, MUSICS_CATALOG catalogo_musics, USER user);

#endif
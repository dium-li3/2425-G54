#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <string.h>
#include <glib.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

#include "entidades/albums.h"
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

void to_lowercase(char *str);

void removeQuotes(char *str);

void remove_newline(char *str);

int calculate_day_of_year(int year, int month, int day);

void calculate_month_and_day(int year, int day_of_year, int *month, int *day);

void update_info_with_history(GArray *parameters_array, MUSICS_CATALOG catalogo_musics, ARTISTS_CATALOG catalogo_artists, USERS_CATALOG catalogo_users, STATS *stats);

void updateArtistRecipe(char *music_id, MUSICS_CATALOG catalogo_musics, ARTISTS_CATALOG artists_catalog);

void updateIndividualAlbums(ALBUM album, ARTISTS_CATALOG catalogo_artists);

gint sort_DiscographyTime(gconstpointer a, gconstpointer b);

void update_DiscographyTime(ARTISTS_CATALOG catalogo_artists, MUSIC music);

gint sort_GeneroMusical(gconstpointer a, gconstpointer b);

void increment_likes_for_genre(STATS *stats, int user_age, char *genre);

void update_statistics_for_genre(STATS *stats, MUSICS_CATALOG catalogo_musics, USER user);

/*
int compare_dates(char *date1,char *date2);

char* get_next_sunday(char *current_sunday);

char* get_sunday_from_date(char *date);

void update_weekly_top_artists(STATS *stats, MUSICS_CATALOG catalogo_musics, ARTISTS_CATALOG catalogo_artists, char *timestamp, char *duration, char *music_id);

void preencher_user_statistics(char *user_id, char *music_id, char *time_stamp, char *duration, MUSICS_CATALOG catalogo_musics, USERS_CATALOG catalogo_users);
*/

#endif
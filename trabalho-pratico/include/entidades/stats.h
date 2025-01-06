#ifndef STATISTICS_H
#define STATISTICS_H

#include <glib.h>
#include <stdio.h>
#include <string.h>
#include <glib.h>
#include <stdlib.h>

typedef struct stats STATS;
typedef struct artist *ARTIST;

STATS* create_statistics(void);

void free_statistics(STATS *stats);

GHashTable* get_genre_age_table(STATS *stats);

GArray* get_artists_array(STATS *stats);

GHashTable* get_weekly_top_artists(STATS *stats);

void add_artist_to_stats(STATS *stats, ARTIST artist);

//gint compare_listening_time(gconstpointer a, gconstpointer b);

//void organize_weekly_top_artists(STATS *stats);

#endif
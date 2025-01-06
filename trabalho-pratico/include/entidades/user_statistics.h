#ifndef USER_STATISTICS_H
#define USER_STATISTICS_H

#include <glib.h>
#include <entidades/listening_time.h>
/*
// Tipo de estrutura user_statistics
typedef struct user_statistics *USER_STATISTICS;
typedef struct artistlisteningtime *ArtistListeningTime;

// Funções de manipulação para listening time
char* get_listening_time_total(USER_STATISTICS stats);
void set_listening_time_total(USER_STATISTICS stats, int listening_time);

// Funções para criar e destruir a estrutura
USER_STATISTICS create_user_statistics(void);
void destroy_user_statistics(USER_STATISTICS stats);

// Funções para manipular listening_times
GHashTable* get_listening_times(USER_STATISTICS stats);
void add_listening_time_user_stats(USER_STATISTICS stats, int artist_id, ArtistListeningTime lt);
ArtistListeningTime get_listening_time(USER_STATISTICS stats, int artist_id);
void remove_listening_time(USER_STATISTICS stats, int artist_id);

// Funções para unique_musics_listened
int get_unique_musics_listened(USER_STATISTICS stats);
void set_unique_musics_listened(USER_STATISTICS stats);

// Funções para daily_listening_time
GHashTable* get_daily_listening_time_table(USER_STATISTICS stats);
void add_daily_listening_time(USER_STATISTICS stats, int day);
int get_daily_listening_time(USER_STATISTICS stats, int day);

// Funções para hourly_listening_time
GHashTable* get_hourly_listening_time_table(USER_STATISTICS stats);
void add_hourly_listening_time(USER_STATISTICS stats, int hour, int seconds);
int get_hourly_listening_time(USER_STATISTICS stats, int hour);

// Funções para genre_count
GHashTable* get_genre_count_table(USER_STATISTICS stats);
void add_genre_count(USER_STATISTICS stats, char *genre);
int get_genre_count(USER_STATISTICS stats, char *genre);

// Funções para album_count
GHashTable* get_album_count_table(USER_STATISTICS stats);
void add_album_count(USER_STATISTICS stats, int album_id);
int get_album_count(USER_STATISTICS stats, int album_id);
*/
#endif 

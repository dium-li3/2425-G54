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
#include "entidades/genero_musical.h"
#include "entidades/listening_time.h"
#include "entidades/user_statistics.h"

#include "catalogos/catalogo_musics.h"
#include "catalogos/catalogo_artists.h"
#include "catalogos/catalogo_users.h"

#include "manager_dados/utils.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// HELP FUNCTIONS /////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

char *create_errors(char *directory)
{
    char *errors = strdup(directory);
    return errors;
}

FILE *create_file(char *errors)
{
    FILE *file = fopen(errors, "a");
    if (file == NULL)
    {
        perror("Erro ao abrir o arquivo de erros");
        free(errors);
    }
    return file;
}

int convert_duration_to_seconds(char *duration)
{
    int hours, minutes, seconds;
    sscanf(duration, "%d:%d:%d", &hours, &minutes, &seconds);
    return hours * 3600 + minutes * 60 + seconds;
}

char *convert_seconds_to_duration(int total_seconds)
{
    int hours = total_seconds / 3600;
    int minutes = (total_seconds % 3600) / 60;
    int seconds = total_seconds % 60;

    char *duration = (char *)malloc(16 * sizeof(char));

    if (duration != NULL)
    {
        sprintf(duration, "%02d:%02d:%02d", hours, minutes, seconds);
    }

    return duration;
}

int calculate_age(char *birthdate)
{

    int current_year = 2024;
    int current_month = 9;
    int current_day = 9;

    int birth_year, birth_month, birth_day;

    sscanf(birthdate, "%d/%d/%d", &birth_year, &birth_month, &birth_day);

    int age = current_year - birth_year;

    if (current_month < birth_month || (current_month == birth_month && current_day < birth_day))
    {
        age--;
    }

    return age;
}

void format_string(char *str)
{

    int j = 0;

    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n')
    {
        str[len - 1] = '\0';
    }

    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] != '[' && str[i] != ']' && str[i] != '\'' && str[i] != ' ')
        {
            str[j++] = str[i];
        }
        if (str[i] == ',' && str[i + 1] == ' ')
        {
            i++;
        }
    }

    str[j] = '\0';
}

void to_lowercase(char *str)
{
    for (int i = 0; str[i]; i++)
    {
        str[i] = tolower((unsigned char)str[i]);
    }
}

void removeQuotes(char *str)
{
    int i = 0, j = 0;
    while (str[i])
    {
        if (str[i] != '"')
        {
            str[j++] = str[i];
        }
        i++;
    }
    str[j] = '\0';
}

void remove_newline(char *str)
{
    size_t len = strlen(str);

    if (len > 0 && str[len - 1] == '\n')
    {
        str[len - 1] = '\0';
    }
}

int calculate_day_of_year(int year, int month, int day) {
    int days_in_month[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    // Ajustar para anos bissextos
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
        days_in_month[1] = 29; // Fevereiro tem 29 dias em anos bissextos
    }

    // Calcular o dia do ano
    int day_of_year = day; // Começar com o dia do mês atual
    for (int i = 0; i < month - 1; i++) { // Somar os dias dos meses anteriores
        day_of_year += days_in_month[i];
    }

    return day_of_year;
}

void calculate_month_and_day(int year, int day_of_year, int *month, int *day) {
    int days_in_month[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    // Ajustar para anos bissextos
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
        days_in_month[1] = 29; // Fevereiro tem 29 dias em anos bissextos
    }

    *month = 0;
    for (int i = 0; i < 12; i++) {
        if (day_of_year <= days_in_month[i]) {
            *month = i + 1;
            *day = day_of_year;
            break;
        } else {
            day_of_year -= days_in_month[i];
        }
    }
}

void update_info_with_history(GArray *parameters_array, MUSICS_CATALOG catalogo_musics, ARTISTS_CATALOG catalogo_artists, USERS_CATALOG catalogo_users, STATS *stats) {
    //char *user_id = g_array_index(parameters_array, char *, 1);
    char *music_id = g_array_index(parameters_array, char *, 2);
    //char *timestamp = g_array_index(parameters_array, char *, 3);
    //char *duration = g_array_index(parameters_array, char *, 4); 

    updateArtistRecipe(music_id,catalogo_musics,catalogo_artists);

    //update_weekly_top_artists(stats, catalogo_musics, catalogo_artists, timestamp, duration, music_id);
    //preencher_user_statistics(user_id,music_id,timestamp,duration,catalogo_musics,catalogo_users);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QUERY 1 HELP /////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

void updateArtistRecipe(char *music_id, MUSICS_CATALOG catalogo_musics, ARTISTS_CATALOG artists_catalog)
{

    MUSIC music = get_music_by_key(catalogo_musics, music_id);

    GArray *artist_ids = getArtistIds(music);

    for (guint i = 0; i < artist_ids->len; i++) {
        char *artist_id = g_array_index(artist_ids, char *, i);
        ARTIST artist = get_artist_by_key(artists_catalog, artist_id);
        char *type = getArtistType(artist);

        if (strcmp(type, "group") == 0)
        {
            double recipe_per_stream = getRecipePerStream(artist);
            if (artist)
                setArtistRecipe(artist, recipe_per_stream);

            GArray *constituents = getIdConstituents(artist);
            if (!constituents || constituents->len == 0) {
                fprintf(stderr, "[ERROR] Artista não possui constituintes.\n");
                return;
            }

            int num_artists = constituents->len;
            for (guint z = 0; z < num_artists; z++) {
                char *constituent_id = g_array_index(constituents, char *, z);

                ARTIST artist_from_group = get_artist_by_key(artists_catalog, constituent_id);
                if (artist_from_group) {
                    double recipe_percent = recipe_per_stream / num_artists;
                    setArtistRecipe(artist_from_group, recipe_percent);
                } else {
                    fprintf(stderr, "[WARNING] Artista com ID %s não encontrado no catálogo.\n", constituent_id);
                }

                free(constituent_id);
            }

            g_array_free(constituents,TRUE);
        }
        else
        {
            double recipe_per_stream = getRecipePerStream(artist);

            if (artist) setArtistRecipe(artist, recipe_per_stream);
        }

        free(type);
        free(artist_id);
    }

    g_array_free(artist_ids,TRUE);
}

void updateIndividualAlbums(ALBUM album, ARTISTS_CATALOG catalogo_artists) {
    GArray *artists_ids = get_album_artists_ids(album);

    if (!artists_ids || artists_ids->len == 0) {
        fprintf(stderr, "[ERROR] Nenhum artista encontrado para o álbum.\n");
        return;
    }

    for (guint i = 0; i < artists_ids->len; i++) {
        char *artist_id = g_array_index(artists_ids, char *, i);

        ARTIST artist = get_artist_by_key(catalogo_artists, artist_id);
        if (!artist) {
            fprintf(stderr, "[WARNING] Artista com ID %s não encontrado.\n", artist_id);
            continue;
        }
        setIndividualAlbuns(artist);

        free(artist_id);
    }

    g_array_free(artists_ids, TRUE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QUERY 2 HELP /////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

gint sort_DiscographyTime(gconstpointer a, gconstpointer b)
{
    ARTIST artist_a = *(ARTIST *)a;
    ARTIST artist_b = *(ARTIST *)b;

    int duration_a = getDiscographyDuration(artist_a);
    int duration_b = getDiscographyDuration(artist_b);

    char *artist_a_ID = getArtistId(artist_a);
    char *artist_b_ID = getArtistId(artist_b);

    int result = strcmp(artist_a_ID, artist_b_ID);

    free(artist_a_ID);
    free(artist_b_ID);

    if (duration_b != duration_a)
        return duration_b - duration_a;

    return result;
}

void update_DiscographyTime(ARTISTS_CATALOG catalogo_artists, MUSIC music) {

    GArray *artist_ids = getArtistIds(music);
    if (!artist_ids || artist_ids->len == 0) {
        return;
    }

    int duration_to_add = getDuration(music);

    for (guint i = 0; i < artist_ids->len; i++) {
        char *artist_id = g_array_index(artist_ids, char *, i);

        ARTIST artist = get_artist_by_key(catalogo_artists, artist_id);

        if (artist) {
            setDiscographyDuration(artist, duration_to_add);
        }

        free(artist_id);
    }

    g_array_free(artist_ids,TRUE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QUERY 3 HELP /////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

gint sort_GeneroMusical(gconstpointer a, gconstpointer b)
{
    const GENERO_MUSICAL genero_a = *(const GENERO_MUSICAL *)a;
    const GENERO_MUSICAL genero_b = *(const GENERO_MUSICAL *)b;

    int genero_a_likes = getGeneroLikes(genero_a);
    int genero_b_likes = getGeneroLikes(genero_b);

    char *genero_a_nome = getGeneroNome(genero_a);
    char *genero_b_nome = getGeneroNome(genero_b);

    int result = g_ascii_strcasecmp(genero_a_nome, genero_b_nome);

    free(genero_a_nome);
    free(genero_b_nome);

    if (genero_a_likes != genero_b_likes)
        return genero_b_likes - genero_a_likes;

    return result;
}

void update_statistics_for_genre(STATS *stats, MUSICS_CATALOG catalogo_musics, USER user)
{

    char *liked_musics = getLikedMusics(user);

    if (!liked_musics || strlen(liked_musics) == 0)
    {
        return;
    }

    int age = getAge(user);

    format_string(liked_musics);
    GString *copy_of_line = g_string_new(liked_musics);
    gchar **tokens = g_strsplit(copy_of_line->str, ",", -1);

    for (int i = 0; tokens[i] != NULL; i++)
    {
        MUSIC music = get_music_by_key(catalogo_musics, tokens[i]);
        char *musicGenre = getGenre(music);

        if (music && musicGenre)
        {
            increment_likes_for_genre(stats, age, musicGenre);
        }

        free(musicGenre);
    }

    g_string_free(copy_of_line, TRUE);
    g_strfreev(tokens);
    free(liked_musics);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QUERY 4 HELP /////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
int compare_dates(char *date1,char *date2) {
    int day1, month1, year1;
    int day2, month2, year2;

    sscanf(date1, "%4d/%2d/%2d", &year1, &month1, &day1);
    sscanf(date2, "%4d/%2d/%2d", &year2, &month2, &day2);

    if (year1 != year2)
        return year1 - year2;
    if (month1 != month2)
        return month1 - month2;
    return day1 - day2;
}

char* get_next_sunday(char *current_sunday) {
    struct tm tm_date = {0};
    time_t time;

    sscanf(current_sunday, "%4d/%2d/%2d", &tm_date.tm_year, &tm_date.tm_mon, &tm_date.tm_mday);
    tm_date.tm_year -= 1900;  
    tm_date.tm_mon -= 1;     

    time = mktime(&tm_date);

    time += 7 * 24 * 3600;

    struct tm *next_sunday_tm = localtime(&time);

    char *next_sunday = malloc(11);
    if (!next_sunday) {
        fprintf(stderr, "Erro ao alocar memória.\n");
        exit(EXIT_FAILURE);
    }

    strftime(next_sunday, 11, "%Y/%m/%d", next_sunday_tm);

    return next_sunday;
}

char* get_sunday_from_date(char *date) {
    struct tm tm_date = {0};
    time_t time;

    sscanf(date, "%4d/%2d/%2d", &tm_date.tm_year, &tm_date.tm_mon, &tm_date.tm_mday);
    tm_date.tm_year -= 1900;  
    tm_date.tm_mon -= 1;    

    time = mktime(&tm_date);

    int day_of_week = tm_date.tm_wday; 
    time -= day_of_week * 24 * 3600;  

    struct tm *sunday = localtime(&time);

    char *sunday_date = malloc(11);
    strftime(sunday_date, 11, "%Y/%m/%d", sunday);

    return sunday_date;
}

void update_weekly_top_artists(STATS *stats, MUSICS_CATALOG catalogo_musics, ARTISTS_CATALOG catalogo_artists, char *timestamp, char *duration, char *music_id) {

    char *sunday = get_sunday_from_date(timestamp);

    int duration_seconds = convert_duration_to_seconds(duration);

    GHashTable *weekly_table = get_weekly_top_artists(stats);
    GArray *artists_list = g_hash_table_lookup(weekly_table, sunday);

    if (!artists_list) {
        artists_list = g_array_new(FALSE, FALSE, sizeof(ArtistListeningTime));
        g_hash_table_insert(weekly_table, strdup(sunday), artists_list);
    }

    MUSIC music = get_music_by_key(catalogo_musics, music_id);
    if (!music) {
        free(sunday);
        return;
    }

    char *artist_ids = getArtistIds(music);
    format_string(artist_ids);
    GString *copy_of_artists = g_string_new(artist_ids);
    gchar **tokens = g_strsplit(copy_of_artists->str, ",", -1);

    for (int i = 0; tokens[i] != NULL; i++) {
        ARTIST artist = get_artist_by_key(catalogo_artists, tokens[i]);
        if (!artist) {
            continue;
        }

        gboolean found = FALSE;
        for (guint j = 0; j < artists_list->len; j++) {
            ArtistListeningTime entry = g_array_index(artists_list, ArtistListeningTime, j);
            char *id = getArtistIdFromListeningTime(entry);
            if (strcmp(tokens[i], id) == 0) {
                setListeningTime(entry, duration_seconds);
                found = TRUE;
                free(id);
                break;
            }
            free(id);
        }

        if (!found) {
            ArtistListeningTime new_entry = createArtistListeningTime();
            setArtistIdInListeningTime(new_entry, tokens[i]);
            setListeningTime(new_entry, duration_seconds);
            g_array_append_val(artists_list, new_entry);
        }
    }

    free(artist_ids);
    g_string_free(copy_of_artists, TRUE);
    g_strfreev(tokens);
    free(sunday);

}
*/
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QUERY 6 HELP /////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
void preencher_user_statistics(char *user_id, char *music_id, char *time_stamp, char *duration, MUSICS_CATALOG catalogo_musics, USERS_CATALOG catalogo_users) {

    int duration_of_listening = convert_duration_to_seconds(duration);

    int day, month, year, hour, minute, second;
    sscanf(time_stamp, "%04d/%02d/%02d  %02d:%02d:%02d",
                        &year, &month, &day, &hour, &minute, &second);

    USER user = get_user_by_key(catalogo_users,user_id);
    MUSIC music = get_music_by_key(catalogo_musics, music_id);

    USER_STATISTICS user_stats = get_user_statistics_by_year(user, year);
    if (!user_stats) {
        user_stats = create_user_statistics();
        addYearlyStatistic(user, year, user_stats);
    }

    char *artist_id_string = getArtistIds(music);
    format_string(artist_id_string);

    GString *copy_of_artists = g_string_new(artist_id_string);
    gchar **tokens = g_strsplit(copy_of_artists->str, ",", -1);

    for (int i = 0; tokens[i] != NULL; i++)
    {
        int artist_id = extractArtistId(tokens[i]);
        int unique = 0;

        ArtistListeningTime artist_entry = get_listening_time(user_stats,artist_id);

        if (!artist_entry) {
            artist_entry = createArtistListeningTime();
            setArtistIdInListeningTime(artist_entry, tokens[i]);
            setListeningTime(artist_entry, duration_of_listening);
            unique = addUniqueMusic(artist_entry,music_id);
            if(unique) set_unique_musics_listened(user_stats);

            add_listening_time_user_stats(user_stats,artist_id,artist_entry);
        } else {
            setListeningTime(artist_entry, duration_of_listening);
            unique = addUniqueMusic(artist_entry,music_id);
            if(unique) set_unique_musics_listened(user_stats);   
        }
    }

    set_listening_time_total(user_stats,duration_of_listening);

    int day_of_year = calculate_day_of_year(year,month,day);
    add_daily_listening_time(user_stats, day_of_year);

    add_hourly_listening_time(user_stats, hour, duration_of_listening);

    char *genre = getGenre(music);
    if (genre) {
        add_genre_count(user_stats, genre);
        free(genre);
    }

    // Atualização das contagens por álbum
    char *album_id = getAlbumId(music);
    int id_album = atoi(album_id + 2);
    add_album_count(user_stats, id_album);

    g_string_free(copy_of_artists, TRUE);
    g_strfreev(tokens);
    free(artist_id_string);
}
*/

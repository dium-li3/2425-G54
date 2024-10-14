#include <stdio.h>
#include <string.h>
#include <glib.h>
#include <stdlib.h>

#include "entidades/musics.h"   
#include "entidades/users.h"
#include "entidades/artists.h"
#include "entidades/stats.h"
#include "entidades/genero_musical.h"

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

int convert_duration_to_seconds(char *duration) {
    int hours, minutes, seconds;
    sscanf(duration, "%d:%d:%d", &hours, &minutes, &seconds);
    return hours * 3600 + minutes * 60 + seconds;
}

char* convert_seconds_to_duration(int total_seconds) {
    int hours = total_seconds / 3600;
    int minutes = (total_seconds % 3600) / 60;
    int seconds = total_seconds % 60;

    char *duration = (char *)malloc(16 * sizeof(char));

    if (duration != NULL) {
        sprintf(duration, "%02d:%02d:%02d", hours, minutes, seconds);
    }

    return duration;
}

int calculate_age(char *birthdate) {
    
    int current_year = 2024;
    int current_month = 9;
    int current_day = 9;

    int birth_year, birth_month, birth_day;

    sscanf(birthdate, "%d/%d/%d", &birth_year, &birth_month, &birth_day);

    int age = current_year - birth_year;

    if (current_month < birth_month || (current_month == birth_month && current_day < birth_day)) {
        age--;
    }

    return age;
}

void format_string(char *str) {

    int j = 0;

    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] != '[' && str[i] != ']' && str[i] != '\'' && str[i] != ' ') {
            str[j++] = str[i];
        }
        if (str[i] == ',' && str[i+1] == ' ') {
            i++;
        }
    }

    str[j] = '\0';

}

void removeQuotes(char *str) {
    int i = 0, j = 0;
    while (str[i]) {
        if (str[i] != '"') {
            str[j++] = str[i];
        }
        i++;
    }
    str[j] = '\0';  // Null-terminate the modified string
}

void remove_newline(char *str) {
    size_t len = strlen(str);

    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0'; 
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QUERY 2 HELP /////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

gint sort_DiscographyTime(gconstpointer a, gconstpointer b) {
    ARTIST artist_a = *(ARTIST *)a;
    ARTIST artist_b = *(ARTIST *)b;

    int duration_a = getDiscographyDuration(artist_a);
    int duration_b = getDiscographyDuration(artist_b);

    char *artist_a_ID = getArtistId(artist_a);
    char *artist_b_ID = getArtistId(artist_b);

    if (duration_b != duration_a) {
        return duration_b - duration_a;
    }

    return strcmp(artist_a_ID, artist_b_ID);
}

void update_DiscographyTime(ARTISTS_CATALOG catalogo_artists, char *artist_ids, char *duration_to_add) {

    if (!artist_ids || strlen(artist_ids) == 0) {
        return;
    }

    format_string(artist_ids);

    char *token = strtok(artist_ids, ",");

    while (token != NULL) {
        ARTIST artist = get_artist_by_key(catalogo_artists, token); 
        
        if (artist) 
            setDiscographyDuration(artist, convert_duration_to_seconds(duration_to_add));

        token = strtok(NULL, ",");
    }

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QUERY 3 HELP /////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

gint sort_GeneroMusical(gconstpointer a, gconstpointer b) {
    const GENERO_MUSICAL genero_a = *(const GENERO_MUSICAL *)a;
    const GENERO_MUSICAL genero_b = *(const GENERO_MUSICAL *)b;

    int genero_a_likes = getGeneroLikes(genero_a);
    int genero_b_likes = getGeneroLikes(genero_b);

    char *genero_a_nome = getGeneroNome(genero_a);
    char *genero_b_nome = getGeneroNome(genero_b);


    if (genero_a_likes != genero_b_likes) {
        return genero_b_likes - genero_a_likes; 
    }

    return g_ascii_strcasecmp(genero_a_nome, genero_b_nome);
}

void increment_likes_for_genre(STATS *stats, int user_age, char *genre) {
    GHashTable *age_table = g_hash_table_lookup(get_genre_age_table(stats), genre);

    if (!age_table) {
        age_table = g_hash_table_new_full(g_int_hash, g_int_equal, g_free, g_free);
        g_hash_table_insert(get_genre_age_table(stats), strdup(genre), age_table);
    }

    int *age_key = g_hash_table_lookup(age_table, &user_age);
    if (!age_key) {
        int *new_age_key = malloc(sizeof(int));
        *new_age_key = user_age;

        int *likes = malloc(sizeof(int));
        *likes = 1;
        g_hash_table_insert(age_table, new_age_key, likes);
    } else {
        (*age_key)++;
    }
}

void update_statistics_for_genre(STATS *stats, MUSICS_CATALOG catalogo_musics, USER user) {
    if (!getLikedMusics(user) || strlen(getLikedMusics(user)) == 0) {
        return;
    }
    
    char *liked_musics = getLikedMusics(user);
    format_string(liked_musics);

    char *music_id = strtok(liked_musics, ",");

    int age = calculate_age(getBirthDate(user));

    while (music_id != NULL) {
        MUSIC music = get_music_by_key(catalogo_musics, music_id);

        if (music && getGenre(music)) {
            increment_likes_for_genre(stats, age, getGenre(music));
        }
        music_id = strtok(NULL, ",");
    }

    free(liked_musics);
}

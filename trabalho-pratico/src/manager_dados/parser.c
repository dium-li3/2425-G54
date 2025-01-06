#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <glib.h>

#include "entidades/musics.h"
#include "entidades/users.h"
#include "entidades/artists.h"
#include "entidades/albums.h"
#include "entidades/stats.h"

#include "catalogos/catalogo_musics.h"
#include "catalogos/catalogo_artists.h"
#include "catalogos/catalogo_users.h"
#include "catalogos/catalogo_albums.h"

#include "manager_dados/querier.h"
#include "manager_dados/validation.h"
#include "manager_dados/utils.h"

char *get_error_file_path(int flag)
{
    const char *base_path = "resultados/";
    char *file_path = (char *)malloc(50 * sizeof(char));

    if (flag == 1)
    {
        strcpy(file_path, base_path);
        strcat(file_path, "artists_errors.csv");
    }
    else if (flag == 2)
    {
        strcpy(file_path, base_path);
        strcat(file_path, "albums_errors.csv");
    }
    else if (flag == 3)
    {
        strcpy(file_path, base_path);
        strcat(file_path, "musics_errors.csv");
    }
    else if (flag == 4)
    {
        strcpy(file_path, base_path);
        strcat(file_path, "users_errors.csv");
    }
    else if (flag == 5)
    {
        strcpy(file_path, base_path);
        strcat(file_path, "history_errors.csv");
    }
    else
    {
        free(file_path);
        return NULL;
    }

    return file_path;
}

FILE *get_file_by_flag(int flag, FILE *artists_file, FILE *albums_file, FILE *musics_file, FILE *users_file, FILE *history_file)
{
    if (flag == 1)
    {
        return artists_file;
    }
    else if (flag == 2)
    {
        return albums_file;
    }
    else if (flag == 3)
    {
        return musics_file;
    }
    else if (flag == 4)
    {
        return users_file;
    }
    else if (flag == 5)
    {
        return history_file;
    }
    else
    {
        return NULL;
    }
}

void insert_catalogo(int flag, GArray *parameters_array, ARTISTS_CATALOG artists, ALBUMS_CATALOG albums, MUSICS_CATALOG musics, USERS_CATALOG users, STATS *stats)
{
    if (flag == 1)
    {
        inserir_artist_catalogo(parameters_array, artists, stats);
    }
    else if (flag == 2)
    {
        inserir_album_catalogo(parameters_array, albums, artists);
    }
    else if (flag == 3)
    {
        inserir_musica_catalogo(parameters_array, musics, artists);
    }
    else if (flag == 4)
    {
        inserir_user_catalogo(parameters_array, users, musics, stats);
    }
    else if (flag == 5)
    {
        update_info_with_history(parameters_array,musics,artists,users,stats);
    }
    else
    {
        return;
    }
}

void parser(ARTISTS_CATALOG artists, MUSICS_CATALOG musics, USERS_CATALOG users, ALBUMS_CATALOG albums, STATS *stats, FILE *artists_file, FILE *musics_file, FILE *users_file, FILE *history_file, FILE *albums_file)
{

    for (int i = 1; i <= 5; i++)
    {
        char *file_errors_path = get_error_file_path(i);
        char *errors = create_errors(file_errors_path);
        FILE *file_errors = create_file(errors);

        char *line = NULL;
        size_t len = 0;

        FILE *info_file = get_file_by_flag(i, artists_file, albums_file, musics_file, users_file, history_file);

        while (getline(&line, &len, info_file) != -1)
        {
            GString *copy_of_line = g_string_new(line);

            GArray *parameters_array = g_array_new(FALSE, FALSE, sizeof(char *));

            gchar **tokens = g_strsplit(copy_of_line->str, ";", -1);
            for (int i = 0; tokens[i] != NULL; i++)
            {
                char *token_copy = tokens[i];
                removeQuotes(token_copy);
                remove_newline(token_copy);
                g_array_append_val(parameters_array, token_copy);
            }
            g_string_free(copy_of_line, TRUE);

            if (valid_entity(i, parameters_array, artists, musics, albums) == 1)
                insert_catalogo(i, parameters_array, artists, albums, musics, users, stats);
            else
                fprintf(file_errors, "%s", line);

            g_strfreev(tokens);

            g_array_free(parameters_array, TRUE);
        }

        free(line);
        free(file_errors_path);
        free(errors);
        fclose(file_errors);
    }

}

#include <stdio.h>
#include <string.h>
#include <glib.h>
#include <stdlib.h>

#include "entidades/users.h"
#include "entidades/user_statistics.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct user {
    int username;
    char *email;
    char *first_name;
    char *last_name;
    int age; 
    char *country;
    GArray *liked_musics;
};

// FUNCTION TO CREATE AN EMPTY USER //////////////////////////////

USER criar_user(void)
{
    USER novo_user = malloc(sizeof(struct user));
    novo_user->username = 0;
    novo_user->email = NULL;
    novo_user->first_name = NULL;
    novo_user->last_name = NULL;
    novo_user->age = 0;
    novo_user->country = NULL;
    novo_user->liked_musics = g_array_new(FALSE, FALSE, sizeof(int));;

    return novo_user;
}

// GETTERS ///////////////////////////////////////////////////////

char* getUsername(USER user) {
    char *formatted_username = malloc(10); // Formato Uxxxxxxx (8 dígitos no máximo)
    if (!formatted_username) {
        perror("Erro ao alocar memória para username");
        return NULL;
    }
    sprintf(formatted_username, "U%07d", user->username);
    return formatted_username;
}

int getAge(USER user) {
    return user->age;
}

char* getEmail(USER user) {
    return strdup(user->email);
}

char* getFirstName(USER user) {
    return strdup(user->first_name);
}

char* getLastName(USER user) {
    return strdup(user->last_name);
}

char* getCountry(USER user) {
    return strdup(user->country);
}

GArray *getLikedMusics(USER user) {
    if (!user->liked_musics || user->liked_musics->len == 0) {
        return g_array_new(FALSE, FALSE, sizeof(char *));
    }

    GArray *liked_musics_array = g_array_new(FALSE, FALSE, sizeof(char *));

    for (guint i = 0; i < user->liked_musics->len; i++) {
        int music_id = g_array_index(user->liked_musics, int, i);
        char *formatted_music_id = malloc(10);
        sprintf(formatted_music_id, "S%07d", music_id); 
        g_array_append_val(liked_musics_array, formatted_music_id);
    }

    return liked_musics_array; 
}

// SETTERS ///////////////////////////////////////////////////////

void setUsername(USER user, char *username) {
    if (username && username[0] == 'U') {
        user->username = atoi(username + 1);
    } else {
        fprintf(stderr, "Formato inválido para username: %s\n", username);
    }
}

void setAge(USER user, char *birth_date) {
    user->age = calculate_age(birth_date);
}

void setEmail(USER user, char *email) {
    free(user->email);
    user->email = strdup(email);
}

void setFirstName(USER user, char *first_name) {
    free(user->first_name);
    user->first_name = strdup(first_name);
}

void setLastName(USER user, char *last_name) {
    free(user->last_name);
    user->last_name = strdup(last_name);
}

void setCountry(USER user, char *country) {
    free(user->country);
    user->country = strdup(country);
}

void setLikedMusics(USER user, char *liked_musics) {
    g_array_set_size(user->liked_musics, 0); 

    char *liked_musics_copy = strdup(liked_musics);
    format_string(liked_musics_copy);

    GString *copy_of_liked_musics = g_string_new(liked_musics_copy);
    gchar **tokens = g_strsplit(copy_of_liked_musics->str, ",", -1);

    for (int i = 0; tokens[i] != NULL; i++) {
        int artist_id = atoi(tokens[i] + 1); 
        g_array_append_val(user->liked_musics, artist_id);
    }

    g_string_free(copy_of_liked_musics, TRUE);
    g_strfreev(tokens);
    free(liked_musics_copy);
}

// FUNCTION TO DESTROY A USER ////////////////////////////////////

void destroi_users(gpointer data) {
    USER user = (USER)data;

    free(user->email);
    free(user->first_name);
    free(user->last_name);
    free(user->country);
    g_array_free(user->liked_musics,TRUE);

    free(user);
}

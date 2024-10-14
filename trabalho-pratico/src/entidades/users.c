#include <stdio.h>
#include <string.h>
#include <glib.h>
#include <stdlib.h>

#include "entidades/users.h"

struct user {
    char *username;
    char *email;
    char *first_name;
    char *last_name;
    char *birth_date;
    char *country;
    char *subscription_type;
    char *liked_musics;
};

// FUNCTION TO CREATE AN EMPTY USER //////////////////////////////

USER criar_user(void)
{
    USER novo_user = malloc(sizeof(struct user));
    novo_user->username = NULL;
    novo_user->email = NULL;
    novo_user->first_name = NULL;
    novo_user->last_name = NULL;
    novo_user->birth_date = NULL;
    novo_user->country = NULL;
    novo_user->subscription_type = NULL;
    novo_user->liked_musics = NULL;

    return novo_user;
}

// GETTERS ///////////////////////////////////////////////////////

char* getUsername(USER user) {
    return strdup(user->username);
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

char* getBirthDate(USER user) {
    return strdup(user->birth_date);
}

char* getCountry(USER user) {
    return strdup(user->country);
}

char* getSubscriptionType(USER user) {
    return strdup(user->subscription_type);
}

char* getLikedMusics(USER user) {
    return strdup(user->liked_musics);
}

// SETTERS ///////////////////////////////////////////////////////

void setUsername(USER user, char *username) {
    free(user->username);
    user->username = strdup(username);
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

void setBirthDate(USER user, char *birth_date) {
    free(user->birth_date);
    user->birth_date = strdup(birth_date);
}

void setCountry(USER user, char *country) {
    free(user->country);
    user->country = strdup(country);
}

void setSubscriptionType(USER user, char *subscription_type) {
    free(user->subscription_type);
    user->subscription_type = strdup(subscription_type);
}

void setLikedMusics(USER user, char *liked_musics) {
    free(user->liked_musics);
    user->liked_musics = strdup(liked_musics);
}

void destroi_users(gpointer data) {
    USER user = (USER)data;

    free(user->username);
    free(user->email);
    free(user->first_name);
    free(user->last_name);
    free(user->birth_date);
    free(user->country);
    free(user->subscription_type);
    free(user->liked_musics);
    
    free(user);
}
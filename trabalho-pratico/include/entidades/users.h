#ifndef USERS_H
#define USERS_H

#include <stdio.h>
#include <string.h>
#include <glib.h>
#include <stdlib.h>

typedef struct user *USER; 

USER criar_user(void);

char* getUsername(USER user);
char* getEmail(USER user);
char* getFirstName(USER user);
char* getLastName(USER user);
char* getBirthDate(USER user);
char* getCountry(USER user);
char* getSubscriptionType(USER user);
char* getLikedMusics(USER user);

void setUsername(USER user, char *username);
void setEmail(USER user, char *email);
void setFirstName(USER user, char *first_name);
void setLastName(USER user, char *last_name);
void setBirthDate(USER user, char *birth_date);
void setCountry(USER user, char *country);
void setSubscriptionType(USER user, char *subscription_type);
void setLikedMusics(USER user, char* liked_musics);

void destroi_users(gpointer data);

#endif
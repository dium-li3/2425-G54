#ifndef USERS_H
#define USERS_H

#include <stdio.h>
#include <string.h>
#include <glib.h>
#include <stdlib.h>
#include <entidades/user_statistics.h>

typedef struct user *USER; 
typedef struct user_statistics *USER_STATISTICS;

USER criar_user(void);

char* getUsername(USER user);
char* getEmail(USER user);
char* getFirstName(USER user);
char* getLastName(USER user);
int getAge(USER user);
char* getCountry(USER user);
char* getLikedMusics(USER user);
//GHashTable* getYearlyStatistics(USER user);
//USER_STATISTICS get_user_statistics_by_year(USER user, int year);

void setUsername(USER user, char *username);
void setEmail(USER user, char *email);
void setFirstName(USER user, char *first_name);
void setLastName(USER user, char *last_name);
void setAge(USER user, char *birth_date);
void setCountry(USER user, char *country);
void setLikedMusics(USER user, char* liked_musics);
//void addYearlyStatistic(USER user, int year, USER_STATISTICS stat);

void destroi_users(gpointer data);

#endif
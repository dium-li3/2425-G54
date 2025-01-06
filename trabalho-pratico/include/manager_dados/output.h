#ifndef OUTPUT_H
#define OUTPUT_H

#include <glib.h>
#include <stdio.h>

void write_null(int numlinha);

void write_query1_user_output(int numlinha, int output_flag, char *email, char *first_name, char *last_name, int age, char *country);

void write_query1_artist_output(int numlinha, int output_flag, char *name, char *type, char *country, int individual_albuns, double recipe);

void write_query2_output(int numlinha,int output_flag,char *artistName,char *artistType,char *duration,char *artistCountry);

void write_query3_output(int numlinha,int output_flag,char *nomeGenero, int likesGenero);

//void write_query4_output(int numlinha, int output_flag, char *name, char *type, int count_top_10);

//void write_query6_output(int numlinha, int output_flag, char *duration, int unique_musics, char* fav_artist, char* date, char* genre, char* album, char* hour, GArray *top_artists);

#endif

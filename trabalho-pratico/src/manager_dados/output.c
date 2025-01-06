#include "manager_dados/output.h"
#include <stdlib.h>
#include <string.h>

// Open a file for the query output
static FILE* open_output_file(int numlinha) {
    char output_path[60];
    snprintf(output_path, sizeof(output_path), "resultados/command%d_output.txt", numlinha);

    FILE *file = fopen(output_path, "a");
    if (!file) {
        perror("Failed to open output file");
        return NULL;
    }
    return file;
}

void write_null(int numlinha){
    FILE *output = open_output_file(numlinha);
    if (!output) return;

    fprintf(output,"\n");

    fclose(output);
}

void write_query1_user_output(int numlinha, int output_flag, char *email, char *first_name, char *last_name, int age, char *country) {
    FILE *output = open_output_file(numlinha);
    if (!output) return;

        if(output_flag == 1)
            fprintf(output, "%s;%s;%s;%d;%s\n", email, first_name, last_name, age, country);
        else
            fprintf(output, "%s=%s=%s=%d=%s\n", email, first_name, last_name, age, country);
        

    fclose(output);
}

void write_query1_artist_output(int numlinha, int output_flag, char *name, char *type, char *country, int individual_albuns, double recipe) {
    FILE *output = open_output_file(numlinha);
    if (!output) return;

        if(output_flag == 1)
            fprintf(output, "%s;%s;%s;%d;%.2f\n", name, type, country, individual_albuns, recipe);
        else
            fprintf(output, "%s=%s=%s=%d=%.2f\n", name, type, country, individual_albuns, recipe);

    fclose(output);
}

void write_query2_output(int numlinha,int output_flag,char *artistName,char *artistType,char *duration,char *artistCountry) {
    FILE *output = open_output_file(numlinha);
    if (!output) return;

        if(output_flag == 1)
            fprintf(output, "%s;%s;%s;%s\n", artistName, artistType, duration, artistCountry);
        else 
            fprintf(output, "%s=%s=%s=%s\n", artistName, artistType, duration, artistCountry);

    fclose(output);
}

void write_query3_output(int numlinha,int output_flag,char *nomeGenero, int likesGenero) {
    FILE *output = open_output_file(numlinha);
    if (!output) return;

        if(output_flag == 1)
            fprintf(output, "%s;%d\n",nomeGenero,likesGenero);
        else
            fprintf(output, "%s=%d\n",nomeGenero,likesGenero);

    fclose(output);
}
/*
void write_query4_output(int numlinha, int output_flag, char *name, char *type, int count_top_10) {
    FILE *output = open_output_file(numlinha);
    if (!output) return;

    if (output_flag == 1) {
        fprintf(output, "%s;%s;%d\n", name, type, count_top_10);
    } else {
        fprintf(output, "%s=%s=%d\n", name, type, count_top_10);
    }

    fclose(output);
}

void write_query6_output(int numlinha, int output_flag, char *duration, int unique_musics, char* fav_artist, char* date, char* genre, char* album, char* hour, GArray *top_artists) {
    FILE *output = open_output_file(numlinha);
    if (!output) return;

    if (output_flag == 1) {
        fprintf(output, "%s;%d;%s;%s;%s;%s;%s\n", duration, unique_musics, fav_artist, date, genre, album, hour);

    } else {
        fprintf(output, "%s=%d=%s=%s=%s=%s=%s\n", duration, unique_musics, fav_artist, date, genre, album, hour);
    }

    if (top_artists && top_artists->len > 0) {
        for (guint i = 0; i < top_artists->len; i++) {
            char *artist_entry = g_array_index(top_artists, char*, i);
                fprintf(output, "%s\n", artist_entry);
        }
    }

    fclose(output);
}
*/

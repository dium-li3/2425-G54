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
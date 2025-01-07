#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include <sys/resource.h>

#include "entidades/musics.h"   
#include "entidades/users.h"
#include "entidades/artists.h"
#include "entidades/albums.h"
#include "entidades/stats.h"

#include "catalogos/catalogo_musics.h"
#include "catalogos/catalogo_artists.h"
#include "catalogos/catalogo_users.h"
#include "catalogos/catalogo_albums.h"

#include "manager_dados/parser.h"
#include "manager_dados/querier.h"
#include "manager_dados/validation.h"
#include "manager_dados/utils.h"

#include "queries/query1.h"
#include "queries/query2.h"
#include "queries/query3.h"

#include "testes/query_results.h"

#define MAX_QUERIES 3

FILE *open_csv_file_tests(const char *path, const char *filename, char **full_path){
    size_t size = strlen(path) + strlen(filename) + 2;
    *full_path = malloc(size);
    if (*full_path == NULL) {
        perror("Failed to allocate memory for file path");
        return NULL;
    }
    
    sprintf(*full_path, "%s/%s", path, filename);
    FILE *file = fopen(*full_path, "r");
    if (file == NULL) {
        perror("Failed to open file");
        free(*full_path);
        *full_path = NULL;
    }
    
    return file;
}

void compare_results(char *expected_outputs, int count, int *correct, int *missing_line, int *missing_query){

    char query_path[60];
    char numero[10];
    sprintf(numero, "%d", count);
    strcpy(query_path, "resultados/command");
    strcat(query_path, numero);
    strcat(query_path, "_output.txt");

    char test_query_path[60];
    char numero_2[10];
    sprintf(numero_2, "%d", count);
    strcpy(test_query_path, "command");
    strcat(test_query_path, numero_2);
    strcat(test_query_path, "_output.txt");

    size_t length = strlen(expected_outputs) + strlen(test_query_path) + 2;
    char *path = malloc((length) * sizeof(char));
    if (path == NULL)
    {
        printf("Memory allocation failed for file: users.csv\n");
        return;
    }
    snprintf(path, length, "%s/%s", expected_outputs, test_query_path);

    FILE *expected_output = fopen(path, "r");
    if (expected_output == NULL)
        perror("Error opening file: expected output");
    free(path);

    FILE *output = fopen(query_path, "r");
    if (output == NULL)
        perror("Error opening file: output"); 

    char query_result[1024], query_expect_result[1024];
    int line = 0;

    if (feof(output) && feof(expected_output)) printf("Error:empty.\n");
    
    do
    {
        char *result_line = fgets(query_result, sizeof(query_result), output);
        char *expected_line = fgets(query_expect_result, sizeof(query_expect_result), expected_output);

        if (result_line) query_result[strcspn(query_result, "\n")] = '\0';
        if (expected_line) query_expect_result[strcspn(query_expect_result, "\n")] = '\0';

        if (feof(output) && feof(expected_output)) break;
        else if (feof(output) || feof(expected_output))
        {
            *correct = 0;
            *missing_line = -1;
            *missing_query = count;
            return;
        }

        line++;

        if (strcmp(query_result, query_expect_result) != 0)
        {
            *correct = 0;
            *missing_line = line;
            *missing_query = count;
            return;
        }
    } while (!feof(output) || !feof(expected_output));

    fclose(expected_output);
    fclose(output);
}

void exec_test_line(ARTISTS_CATALOG artists, MUSICS_CATALOG musics, USERS_CATALOG users, ALBUMS_CATALOG albums, STATS *stats, char *linha, int count, char *expected_outputs, QUERYRESULTS queries_results[]){
        linha[strcspn(linha, "\n")] = '\0';
        char *query, *args;
        query = strsep(&linha, " ");
        args = (linha != NULL) ? linha : "";

        clock_t start; 
        clock_t end;

        int number = atoi(query);

        if(strcmp(query, "1") == 0)
        {
            start = clock();
            execute_query1(count, args, 1, users, artists);
            end = clock();
        }
        else if(strcmp(query, "1S") == 0)
        {
            start = clock();
            execute_query1(count, args, 2, users, artists);
            end = clock();
        }
        else if(strcmp(query, "2") == 0)
        {
            start = clock();
            execute_query2(count, 1, args, stats);
            end = clock();
        }
        else if(strcmp(query, "2S") == 0)
        {
            start = clock();
            execute_query2(count, 2, args, stats);
            end = clock();
        }
        else if(strcmp(query, "3") == 0)
        {
            start = clock();
            execute_query3(count, 1, args, stats);
            end = clock();
        }
        else if(strcmp(query, "3S") == 0)
        {
            start = clock();
            execute_query3(count, 2, args, stats);
            end = clock();
        }
        else{
            return;
        }

        int correct = 1, missing_line = -2, missing_query = 0;
        compare_results(expected_outputs, count, &correct, &missing_line, &missing_query);

        double total_time = ((double)(end - start)) / CLOCKS_PER_SEC;
        set_query_time(queries_results[number-1], total_time);
        set_number_of_queries(queries_results[number-1], 1);
        if (correct) set_total_correct_queries(queries_results[number-1], 1);
        else set_failed_queries(queries_results[number-1], missing_query, missing_line);
        
}

void test_querier(ARTISTS_CATALOG artists, MUSICS_CATALOG musics, USERS_CATALOG users, ALBUMS_CATALOG albums, STATS *stats, FILE *input, char *expected_outputs, QUERYRESULTS queries_results[]){
    int count = 1;
    char linha[1024];

    while (fgets(linha, sizeof(linha), input) != NULL) 
    {
        exec_test_line(artists, musics, users, albums, stats, linha, count, expected_outputs, queries_results);
        count++;
    }
}

int main(int argc, char **argv)
{
    if (argc != 4)
        return 1;

    ARTISTS_CATALOG artists_hashtable = create_artists_catalog();
    MUSICS_CATALOG musics_hashtable = create_musics_catalog(); 
    USERS_CATALOG users_hashtable = create_users_catalog();
    ALBUMS_CATALOG album_hashtable = create_albums_catalog();
    STATS *stats = create_statistics();

    char *artists_path, *albums_path, *musics_path, *users_path, *history_path;
    FILE *artists_file = open_csv_file_tests(argv[1], "artists.csv", &artists_path);
    FILE *albums_file = open_csv_file_tests(argv[1], "albums.csv", &albums_path);
    FILE *musics_file = open_csv_file_tests(argv[1], "musics.csv", &musics_path);
    FILE *users_file = open_csv_file_tests(argv[1], "users.csv", &users_path);
    FILE *history_file = open_csv_file_tests(argv[1], "history.csv", &history_path);

    if (!artists_file || !albums_file || !musics_file || !users_file || !history_file) {
        free(artists_path);
        free(albums_path);
        free(musics_path);
        free(users_path);
        free(history_path);
        free_artists_catalog(artists_hashtable);
        free_albums_catalog(album_hashtable);
        free_musics_catalog(musics_hashtable);
        free_user_catalog(users_hashtable);
        free_statistics(stats);
        return 0;
    }

    FILE *qs = fopen(argv[2], "r");
    if (qs == NULL) {
        perror("Failed to open commands file");
        fclose(artists_file);
        fclose(albums_file);
        fclose(musics_file);
        fclose(users_file);
        fclose(history_file);
        free(artists_path);
        free(albums_path);
        free(musics_path);
        free(users_path);
        free(history_path);
        free_artists_catalog(artists_hashtable);
        free_albums_catalog(album_hashtable);
        free_musics_catalog(musics_hashtable);
        free_user_catalog(users_hashtable);
        free_statistics(stats);
        return 0;
    }

    QUERYRESULTS queries_results[MAX_QUERIES];
    for (int i = 0; i < MAX_QUERIES; i++)
        queries_results[i] = create_query_results();
    
    double parser_time;
    double queries_time;
    double total_time;

    struct rusage r_usage;
    clock_t init_program, finit_program;

    init_program = clock();

        clock_t init_parser, finit_parser;
        clock_t init_queries, finit_queries;
        double time;

        init_parser = clock();
        
        parser(artists_hashtable, musics_hashtable, users_hashtable, album_hashtable, stats, artists_file, musics_file, users_file, history_file, albums_file);

        finit_parser = clock();
        
        time = ((double)(finit_parser - init_parser)) / CLOCKS_PER_SEC;
        parser_time = time;

        init_queries = clock();

        test_querier(artists_hashtable,musics_hashtable,users_hashtable,album_hashtable,stats, qs, argv[3], queries_results);

        finit_queries = clock();
        time = ((double)(finit_queries - init_queries)) / CLOCKS_PER_SEC;
        queries_time = time;

        fclose(artists_file);
        fclose(musics_file);
        fclose(users_file);
        fclose(qs);

        free(artists_path);
        free(musics_path);
        free(users_path);

        free_artists_catalog(artists_hashtable);
        free_musics_catalog(musics_hashtable);
        free_user_catalog(users_hashtable);
        free_albums_catalog(album_hashtable);
        free_statistics(stats);

    finit_program = clock();

    total_time = ((double)(finit_program - init_program)) / CLOCKS_PER_SEC;

    //PRINT RESULTS///////////////////////////////////////////////////////////////////////////////////////

    getrusage(RUSAGE_SELF, &r_usage);
    printf("\033[1;33mMEMORY TEST\033[0m\n");
    printf("-----------------------------------------------------------\n");
    printf("\033[0;32m%ld KB\033[0m\n", r_usage.ru_maxrss);
    printf("-----------------------------------------------------------\n\n");

    printf("\033[1;33mDIFFERENT TIME TESTS\033[0m\n");
    printf("-----------------------------------------------------------\n");
    printf("\033[0;32mParser: %f seconds\033[0m\n", parser_time);
    printf("\033[0;32mQueries: %f seconds\033[0m\n", queries_time);
    printf("\033[0;32mTotal time: %f seconds\033[0m\n", total_time);
    printf("-----------------------------------------------------------\n\n");

    for (int i = 0; i < MAX_QUERIES; i++) {
        GArray *failed_queries = get_failed_queries(queries_results[i]);
        int number_of_queries = get_number_of_queries(queries_results[i]);
        int total_correct_queries = get_total_correct_queries(queries_results[i]);
        double found_time = get_query_time(queries_results[i]);
        double average_time = found_time / number_of_queries;
        double correct_percentage = (double)total_correct_queries / number_of_queries * 100;

        printf("\033[1;33mQUERY %d TESTS\033[0m\n", i+1);
        printf("-----------------------------------------------------------\n");
        printf("\033[0;32mTotal Time: %f seconds\033[0m\n", found_time);
        printf("\033[0;32mAverage Time Per Query: %f seconds\033[0m\n", average_time);
        printf("\033[0;32mPercentage of Correct Queries: %f%% // %d/%d\033[0m\n", correct_percentage, total_correct_queries, number_of_queries);
        printf("-----------------------------------------------------------\n\n");

        if (total_correct_queries != number_of_queries) {
            printf("\033[0;31mINVALID TESTS\033[0m\n");
            for (int j = 0; j < failed_queries->len; j += 2) {
                int missing_query = g_array_index(failed_queries, int, j);
                int missing_line = g_array_index(failed_queries, int, j + 1);

                printf("\033[0;31m- Input: %d\033[0m", missing_query);
                if (missing_line == -1) {
                    printf(" | \033[0;31mError in Size\033[0m\n");
                } else {
                    printf(" | \033[0;31mError in Line: %d\033[0m\n", missing_line);
                }
            }
            printf("\n");
        }
        g_array_free(failed_queries, TRUE);
    }

    /////////////////////////////////////////////////////////////////////////////////////

    return 0;
}
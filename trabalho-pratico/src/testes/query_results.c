#include "testes/query_results.h"

struct queryresults
{
    double time;
    int number_of_queries;
    int total_correct_queries;
    GArray *failed_queries;
};

QUERYRESULTS create_query_results(void){
    QUERYRESULTS new_query_results = malloc(sizeof(struct queryresults));

    new_query_results->time = 0.0;
    new_query_results->number_of_queries = 0;
    new_query_results->total_correct_queries = 0;
    new_query_results->failed_queries = g_array_new(FALSE, FALSE, sizeof(int));

    return new_query_results;
}

double get_query_time(QUERYRESULTS query_results){
    return query_results->time;
}

int get_number_of_queries(QUERYRESULTS query_results){
    return query_results->number_of_queries;
}

int get_total_correct_queries(QUERYRESULTS query_results){
    return query_results->total_correct_queries;
}

GArray *get_failed_queries(QUERYRESULTS query_results){
    return g_array_copy(query_results->failed_queries);
}

void set_query_time(QUERYRESULTS query_results, double time){
    query_results->time += time;
}

void set_number_of_queries(QUERYRESULTS query_results, int number_of_queries){
    query_results->number_of_queries += number_of_queries;
}

void set_total_correct_queries(QUERYRESULTS query_results, int total_correct_queries){
    query_results->total_correct_queries += total_correct_queries;
}

void set_failed_queries(QUERYRESULTS query_results, int failed_query, int line_failed){
    g_array_append_val(query_results->failed_queries, failed_query);
    g_array_append_val(query_results->failed_queries, line_failed);
}

void query_destroy_function(gpointer data){
    QUERYRESULTS query_results = (QUERYRESULTS)data;

    g_array_free(query_results->failed_queries, TRUE);

    free(query_results);
}
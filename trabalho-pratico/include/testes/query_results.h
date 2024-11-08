#ifndef QUERYRESULTS_H
#define QUERYRESULTS_H

#include <glib.h>

typedef struct queryresults *QUERYRESULTS;

QUERYRESULTS create_query_results(void);

double get_query_time(QUERYRESULTS query_results);

int get_number_of_queries(QUERYRESULTS query_results);

int get_total_correct_queries(QUERYRESULTS query_results);

GArray *get_failed_queries(QUERYRESULTS query_results);

void set_query_time(QUERYRESULTS query_results, double time);

void set_number_of_queries(QUERYRESULTS query_results, int number_of_queries);

void set_total_correct_queries(QUERYRESULTS query_results, int total_correct_queries);

void set_failed_queries(QUERYRESULTS query_results, int failed_query, int line_failed);

void query_destroy_function(gpointer data);

#endif
#include <stdio.h>
#include <string.h>
#include <glib.h>
#include <stdlib.h>

#include "entidades/musics.h"   
#include "entidades/users.h"
#include "entidades/artists.h"
#include "entidades/stats.h"
#include "entidades/genero_musical.h"

#include "catalogos/catalogo_musics.h"
#include "catalogos/catalogo_artists.h"
#include "catalogos/catalogo_users.h"

#include "manager_dados/utils.h"
#include "manager_dados/output.h"

#include "queries/query3.h"

void execute_query3(int numlinha, int flag, char *arg, STATS *stats)
{
    //---------------------BUSCA DE ARGUMENTOS------------------
    char *min_age, *max_age;
    min_age = strsep(&arg, " ");
    max_age = (arg != NULL) ? arg : "";

    int min_age_number = atoi(min_age);
    int max_age_number = atoi(max_age);
    //----------------------------------------------------------

    GHashTable *genre_age_table = get_genre_age_table(stats);
    if (!genre_age_table) {
        printf("No data in genre_age_table.\n");
        return;
    }

    GArray *generos_musicais_array = g_array_new(FALSE, FALSE, sizeof(GENERO_MUSICAL));

    GHashTableIter genre_iter;
    gpointer genre_key, age_table_value;
    
    g_hash_table_iter_init(&genre_iter, genre_age_table);
    while (g_hash_table_iter_next(&genre_iter, &genre_key, &age_table_value)) {
        char *genre = (char *)genre_key;
        GHashTable *age_table = (GHashTable *)age_table_value;

        int total_likes = 0;

        for (int age = min_age_number; age <= max_age_number; age++) {
            int *likes = g_hash_table_lookup(age_table, &age);
            if (likes) {
                total_likes += *likes;
            }
        }

        if (total_likes > 0) {
            GENERO_MUSICAL genero = criar_genero_musical();
            setGeneroNome(genero,genre);
            setGeneroLikes(genero,total_likes);
            g_array_append_val(generos_musicais_array, genero);
        }
    }

    g_array_sort(generos_musicais_array, sort_GeneroMusical);

    if (generos_musicais_array->len == 0) {
        write_null(numlinha);
    }

    for (int i = 0; i < generos_musicais_array->len; i++)
        {
            GENERO_MUSICAL genero = g_array_index(generos_musicais_array, GENERO_MUSICAL, i);

            char *nomeGenero = getGeneroNome(genero);
            int likesGenero = getGeneroLikes(genero);

            write_query3_output(numlinha,flag,nomeGenero,likesGenero);

            free(nomeGenero);
        }

    for (guint i = 0; i < generos_musicais_array->len; i++) {
        GENERO_MUSICAL genero = g_array_index(generos_musicais_array, GENERO_MUSICAL, i);
        free_genero_musical(genero); 
    }

    g_array_free(generos_musicais_array, TRUE);
}
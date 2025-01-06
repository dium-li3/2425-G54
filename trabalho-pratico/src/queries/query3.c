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

void execute_query3(int numlinha, int flag, char *arg, STATS *stats) {
    //---------------------BUSCA DE ARGUMENTOS------------------
    char *min_age, *max_age;
    min_age = strsep(&arg, " ");
    max_age = (arg != NULL) ? arg : "";

    int min_age_number = atoi(min_age);
    int max_age_number = atoi(max_age);
    //----------------------------------------------------------

    GArray *generos_musicais_array = get_genres_by_age_range(stats, min_age_number, max_age_number);

    g_array_sort(generos_musicais_array, sort_GeneroMusical);

    if (generos_musicais_array->len == 0) {
        write_null(numlinha);
    }

    for (int i = 0; i < generos_musicais_array->len; i++) {
        GENERO_MUSICAL genero = g_array_index(generos_musicais_array, GENERO_MUSICAL, i);

        char *nomeGenero = getGeneroNome(genero);
        int likesGenero = getGeneroLikes(genero);

        write_query3_output(numlinha, flag, nomeGenero, likesGenero);

        free(nomeGenero);
    }

    for (guint i = 0; i < generos_musicais_array->len; i++) {
        GENERO_MUSICAL genero = g_array_index(generos_musicais_array, GENERO_MUSICAL, i);
        free_genero_musical(genero);
    }

    g_array_free(generos_musicais_array, TRUE);
}

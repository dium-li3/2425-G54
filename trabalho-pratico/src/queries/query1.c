#include <stdio.h>
#include <string.h>
#include <glib.h>
#include <stdlib.h>

#include "entidades/musics.h"   
#include "entidades/users.h"
#include "entidades/artists.h"
#include "entidades/stats.h"

#include "catalogos/catalogo_musics.h"
#include "catalogos/catalogo_artists.h"
#include "catalogos/catalogo_users.h"

#include "manager_dados/utils.h"

#include "queries/query1.h"

void execute_query1(int numlinha, char *arg, USERS_CATALOG users)
{
    //---------------------ESCREVER FICHEIRO---------------------
    char query1_path[60];
    char numero[10];
    sprintf(numero, "%d", numlinha);
    strcpy(query1_path, "resultados/command");
    strcat(query1_path, numero);
    strcat(query1_path, "_output.txt");

    char *query1_ficheiro = strdup(query1_path);
    FILE *ficheiro = fopen(query1_ficheiro, "w");
    if (ficheiro == NULL)
    {
        perror("Erro ao abrir o arquivo de erros");
        free(query1_ficheiro);
    }
    //----------------------------------------------------------

    USER user = get_user_by_key(users, arg);

    if (user){

    char *email = getEmail(user);
    char *first_name = getFirstName(user);
    char *last_name = getLastName(user);
    int age = calculate_age(getBirthDate(user));
    char *country = getCountry(user);

    fprintf(ficheiro, "%s;%s;%s;%d;%s", email, first_name, last_name, age, country);
    fprintf(ficheiro, "\n");

    free(email);
    free(first_name);
    free(last_name);
    free(country);

    }
    
    fclose(ficheiro);  
    free(query1_ficheiro);
}
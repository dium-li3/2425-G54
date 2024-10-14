#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include <sys/resource.h>

#include "entidades/musics.h"   
#include "entidades/users.h"
#include "entidades/artists.h"
#include "entidades/stats.h"

#include "catalogos/catalogo_musics.h"
#include "catalogos/catalogo_artists.h"
#include "catalogos/catalogo_users.h"

#include "manager_dados/parser.h"
#include "manager_dados/querier.h"
#include "manager_dados/validation.h"
#include "manager_dados/utils.h"

#include "modos_execucao/programa-principal.h"

int main(int argc, char **argv)
{
       if (argc==1) {}//exec_interactive_mode(argv[1]);
       else
       {
           if (argc==3) exec_programa_principal(argv[1],argv[2]);
           else
           {
               printf("Argumentos insuficientes(ou excessivos)");
               return 1;
           }
       }
    
    return 0;
}
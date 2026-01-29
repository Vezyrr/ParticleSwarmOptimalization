#include "map.h"
#include "pso.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void get_params(int argc, char** av, int* ile_cz, int* ile_iter, char** plik_konf, int* co_ile_zapis)
{
    for(int i = 2; i < argc - 1; i += 2)
    {
        if(!strcmp(av[i], "-p"))
        {
            *ile_cz = atoi(av[i + 1]);
            printf("%d\n", *ile_cz);
        }
        else if(!strcmp(av[i], "-i"))
        {
            *ile_iter = atoi(av[i + 1]);
            printf("%d\n", *ile_iter);
        }
        else if(!strcmp(av[i], "-c"))
        {
            *plik_konf = av[i + 1];
            printf("%s\n", *plik_konf);
        }
        else if(!strcmp(av[i], "-n"))
        {
            *co_ile_zapis = atoi(av[i + 1]);
            printf("%d\n", *co_ile_zapis);
        }
        //printf("\n");
    }
}

int main(int argc, char** argv)
{

    Map* mapa = load_map_from_file(argv[1]);
    //int ile_cz = argv();

    int ile_cz = 30;
    int ile_iter = 100;
    char* plik_konf = NULL;
    int co_ile_zapis = 0;

    char** av = argv;
    get_params(
        argc,
        av,
        &ile_cz,
        &ile_iter,
        &plik_konf,
        &co_ile_zapis);

    printf("\n\ntest\n");
    return 0;
}
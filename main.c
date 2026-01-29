#include "map.h"
#include "pso.h"
#include "logger.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void get_params(int argc, char** av, int* ile_cz, int* ile_iter, char** plik_konf, int* co_ile_zapis)
{
    int czy_test = 0;
    for(int i = 2; i < argc - 1; i += 2)
    {
        if(!strcmp(av[i], "-p"))
        {
            *ile_cz = atoi(av[i + 1]);
            if(czy_test)printf("%d\n", *ile_cz);
        }
        else if(!strcmp(av[i], "-i"))
        {
            *ile_iter = atoi(av[i + 1]);
            if(czy_test)printf("%d\n", *ile_iter);
        }
        else if(!strcmp(av[i], "-c"))
        {
            *plik_konf = av[i + 1];
            if(czy_test)printf("%s\n", *plik_konf);
        }
        else if(!strcmp(av[i], "-n"))
        {
            *co_ile_zapis = atoi(av[i + 1]);
            if(czy_test)printf("%d\n", *co_ile_zapis);
        }
        //printf("\n");
    }
}

void main_loop(PSOParams* pso_parametry ,Swarm* roj, Map* mapa, int ile_cz, int ile_iter, char* plik_konf, int co_ile_zapis)
{
    for(int i = 0; i < ile_iter; i++)
    {
        update_swarm(roj, mapa, *pso_parametry);
    }
}

void get_pso_params(char* filename, PSOParams* docelowa_zmienna_parametrow)
{
    int czy_test = 0;

    FILE* konf = fopen(filename, "r");
    if(konf == NULL)
    {
        printf("nie mozna otworzyc pliku z konfiguracja\n");
        docelowa_zmienna_parametrow->c1 = 0.2; 
        docelowa_zmienna_parametrow->c2 = 0.3;
        docelowa_zmienna_parametrow->w = 0.4;
        return;
    }
    else
    {
        char klucz[10];
        double wartosc;
        while(fscanf(konf, "%s %lf", klucz, &wartosc) == 2)
        {
            if(czy_test)printf("%s: %lf\n", klucz, wartosc);
            if(strcmp(klucz, "c_1") == 0)
            {
                docelowa_zmienna_parametrow->c1 = wartosc;
            }
            else if(strcmp(klucz, "c_2") == 0)
            {
                docelowa_zmienna_parametrow->c2 = wartosc;
            }
            else if(strcmp(klucz, "w") == 0)
            {
                docelowa_zmienna_parametrow->w = wartosc;
            }
        }
    }

    fclose(konf);
}

int main(int argc, char** argv)
{

    Map mapa = *load_map_from_file(argv[1]);
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
        &co_ile_zapis
    );

    PSOParams pso_parametry;
    get_pso_params(plik_konf, &pso_parametry);

    Swarm roj = *initialize_swarm(ile_cz, &mapa);
    main_loop(
        &pso_parametry,
        &roj,
        &mapa,
        ile_cz,
        ile_iter,
        plik_konf,
        co_ile_zapis
    );

    printf("\n\ntest\n");
    return 0;
}
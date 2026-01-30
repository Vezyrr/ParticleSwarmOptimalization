#include "map.h"
#include "pso.h"
#include "logger.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

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
    FILE* plik_logger = fopen("zapisane_stany.csv", "w");
    add_header(plik_logger);

    for(int i = 0; i < ile_iter; i++)
    {
        update_swarm(roj, mapa, *pso_parametry);
        if(i%co_ile_zapis == 0)
        {
            write_state_to_file(*roj, plik_logger, i);
        }
    }
}

void get_pso_params(char* filename, PSOParams* docelowa_zmienna_parametrow)
{
    int czy_test = 0;

    FILE* konf = fopen(filename, "r");
    if(konf == NULL)
    {
        printf("nie mozna otworzyc pliku z konfiguracja\n");
        docelowa_zmienna_parametrow->c1 = 1.5; 
        docelowa_zmienna_parametrow->c2 = 1.5;
        docelowa_zmienna_parametrow->w = 0.7;
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

void wyswietl_finalna_pozycje(Swarm roj)
{
    double suma_x = 0;
    double suma_y = 0;
    for(int i = 0; i < roj.particle_count; i++)
    {
        //printf("x: %lf   y: %lf\n", swarm.particles[i].x, swarm.particles[i].y);
        //fprintf(plik_logger, "Czasteczka nr. %d, %lf, %lf\n", i + 1, swarm.particles[i].x, swarm.particles[i].y);
        suma_x += roj.particles[i].x;
        suma_y += roj.particles[i].y;
    }
    double srednia_x = suma_x/roj.particle_count;
    double srednia_y = suma_y/roj.particle_count;
    
    printf("finalne wspolrzedne to: x: %d, y: %d\n", (int)(round(srednia_x)), (int)(round(srednia_y)));
    //printf("finalne wspolrzedne to: x: %lf, y: %lf\n", srednia_x, srednia_y);
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

    wyswietl_finalna_pozycje(roj);

    printf("\nwykonano w pelni\n");
    return 0;
}
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "logger.h"

void add_header(FILE* plik_logger)
{
    fprintf(plik_logger, "ID_CZASTECZKI, CORD_X, CORD_Y\n");
}

void write_state_to_file(Swarm swarm, FILE* plik_logger, int tura)
{
    
    fprintf(plik_logger, "STAN Z TURY: %d, , \n", tura);
    for(int i = 0; i < swarm.particle_count; i++)
    {
        printf("x: %lf   y: %lf\n", swarm.particles[i].x, swarm.particles[i].y);
        fprintf(plik_logger, "Czasteczka nr. %d, %lf, %lf\n", i + 1, swarm.particles[i].x, swarm.particles[i].y);
    }
    printf("\n\n");
    fprintf(plik_logger, "\n");

}
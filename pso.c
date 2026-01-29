#include <stdio.h>
#include <stdlib.h>
#include <float.h> // Dla DBL_MAX lub bardzo małych wartości
#include "pso.h"

// Pomocnicza funkcja zwracająca losową liczbę double [0, 1]
// (Wymagane do czynników r1 i r2 we wzorze)
double random_01() {
    return (double)rand() / (double)RAND_MAX;
}

// Pomocnicza funkcja losująca pozycję w zakresie [0, max]
double random_range(double max) {
    return random_01() * max;
}

Swarm* initialize_swarm(int particle_count, Map *map) {
    Swarm *swarm = (Swarm*)malloc(sizeof(Swarm));
    if (!swarm) return NULL;

    swarm->particle_count = particle_count;
    
    // Alokacja dynamiczna tablicy cząstek
    swarm->particles = (Particle*)malloc(particle_count * sizeof(Particle));
    if (!swarm->particles) {
        free(swarm);
        return NULL;
    }

    // Inicjalizacja gBest wartością bardzo małą, aby każdy punkt na mapie był lepszy
    swarm->gBest_val = -DBL_MAX; 
    swarm->gBest_x = 0;
    swarm->gBest_y = 0;

    for (int i = 0; i < particle_count; i++) {
        // Losowa pozycja startowa na mapie
        swarm->particles[i].x = random_range(map->width);
        swarm->particles[i].y = random_range(map->height);

        // Losowa prędkość początkowa (można dobrać mały zakres, np. od -1 do 1)
        swarm->particles[i].vx = (random_01() - 0.5) * 2.0; 
        swarm->particles[i].vy = (random_01() - 0.5) * 2.0;

        // Na początku pBest to aktualna pozycja
        swarm->particles[i].pBest_x = swarm->particles[i].x;
        swarm->particles[i].pBest_y = swarm->particles[i].y;
        
        // Pobranie wartości fitness z mapy
        double current_fitness = get_map_value(map, swarm->particles[i].x, swarm->particles[i].y);
        swarm->particles[i].pBest_val = current_fitness;

        // Aktualizacja gBest, jeśli ta cząstka znalazła coś lepszego niż dotychczasowe gBest
        if (current_fitness > swarm->gBest_val) {
            swarm->gBest_val = current_fitness;
            swarm->gBest_x = swarm->particles[i].x;
            swarm->gBest_y = swarm->particles[i].y;
        }
    }

    return swarm;
}

void update_swarm(Swarm *swarm, Map *map, PSOParams params) {
    for (int i = 0; i < swarm->particle_count; i++) {
        Particle *p = &swarm->particles[i];

        //Aktualizacja prędkości
        // v(t+1) = w*v(t) + c1*r1*(pBest - x) + c2*r2*(gBest - x)
        
        double r1_x = random_01(); // r1 dla osi X
        double r1_y = random_01(); // r1 dla osi Y
        double r2_x = random_01(); // r2 dla osi X
        double r2_y = random_01(); // r2 dla osi Y

        // Składowa inercji
        double inertia_x = params.w * p->vx;
        double inertia_y = params.w * p->vy;

        // Składowa kognitywna (pamięć cząstki)
        double cognitive_x = params.c1 * r1_x * (p->pBest_x - p->x);
        double cognitive_y = params.c1 * r1_y * (p->pBest_y - p->y);

        // Składowa socjalna (wiedza roju)
        double social_x = params.c2 * r2_x * (swarm->gBest_x - p->x);
        double social_y = params.c2 * r2_y * (swarm->gBest_y - p->y);

        // Nowa prędkość
        p->vx = inertia_x + cognitive_x + social_x;
        p->vy = inertia_y + cognitive_y + social_y;

        // Aktualizacja pozycji
        // x(t+1) = x(t) + v(t+1)
        p->x = p->x + p->vx;
        p->y = p->y + p->vy;

        // Ocena nowej pozycji (Fitness)
        double current_fitness = get_map_value(map, p->x, p->y);

        // Czy to nowe pBest dla tej cząstki?
        if (current_fitness > p->pBest_val) {
            p->pBest_val = current_fitness;
            p->pBest_x = p->x;
            p->pBest_y = p->y;

            // Czy to nowe gBest dla całego roju?
            if (current_fitness > swarm->gBest_val) {
                swarm->gBest_val = current_fitness;
                swarm->gBest_x = p->x;
                swarm->gBest_y = p->y;
            }
        }
    }
}

void free_swarm(Swarm *swarm) {
    if (swarm) {
        if (swarm->particles) {
            free(swarm->particles);
        }
        free(swarm);
    }
}
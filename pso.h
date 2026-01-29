#ifndef PSO_H
#define PSO_H

#include "map.h"

// Struktura parametrów algorytmu
typedef struct {
    double w;  // Waga bezwładności 
    double c1; // pamięć własna
    double c2; // wiedza roju
} PSOParams;

// Struktura pojedynczej cząstki
typedef struct {
    double x, y;          // Aktualna pozycja
    double vx, vy;        // Aktualna prędkość
    
    double pBest_x, pBest_y; // Najlepsza znana pozycja tej cząstki
    double pBest_val;        // Wartość funkcji celu (fitness) w pBest
} Particle;

// Struktura roju
typedef struct {
    Particle *particles;  // Dynamiczna tablica cząstek
    int particle_count;   // Liczba cząstek
    
    double gBest_x, gBest_y; // Najlepsza pozycja znana całemu rojowi
    double gBest_val;        // Wartość fitness w gBest
} Swarm;

/**
 * Inicjalizuje rój cząstek.
 * Alokuje pamięć i rozrzuca cząstki losowo po mapie.
 */
Swarm* initialize_swarm(int particle_count, Map *map);

/**
 * Wykonuje jedną iterację algorytmu PSO.
 * Aktualizuje prędkości, pozycje oraz pBest i gBest.
 */
void update_swarm(Swarm *swarm, Map *map, PSOParams params);

/**
 * Zwalnia pamięć roju.
 */
void free_swarm(Swarm *swarm);

#endif
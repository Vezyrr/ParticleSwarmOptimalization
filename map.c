
#include <stdio.h>
#include <stdlib.h>
#include "map.h"
#include <math.h>

// Stała kary za wylot poza mapę 
#define OUT_OF_BOUNDS_PENALTY -10000.0

Map* load_map_from_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Błąd: Nie można otworzyć pliku mapy: %s\n", filename);
        return NULL;
    }

    int w, h;
    // Wczytanie wymiarów mapy
    if (fscanf(file, "%d %d", &w, &h) != 2) {
        fprintf(stderr, "Błąd: Nieprawidłowy format nagłówka mapy.\n");
        fclose(file);
        return NULL;
    }

    // Alokacja struktury Map 
    Map *map = (Map*)malloc(sizeof(Map));
    if (!map) {
        perror("Błąd alokacji pamięci dla struktury mapy");
        fclose(file);
        return NULL;
    }

    map->width = w;
    map->height = h;

    // Dynamiczna alokacja tablicy wartości
    // Używamy tablicy 1D o rozmiarze W*H
    map->cells = (double*)malloc(w * h * sizeof(double));
    if (!map->cells) {
        perror("Błąd alokacji pamięci dla komórek mapy");
        free(map);
        fclose(file);
        return NULL;
    }

    // Wczytywanie wartości do tablicy
    for (int i = 0; i < w * h; i++) {
        if (fscanf(file, "%lf", &map->cells[i]) != 1) {
            fprintf(stderr, "Błąd: Za mało danych w pliku mapy.\n");
            free_map(map); 
            fclose(file);
            return NULL;
        }
    }

    fclose(file);
    return map;
}

void free_map(Map *map) {
    if (map) {
        if (map->cells) {
            free(map->cells);
        }
        free(map); 
    }
}

double get_map_value(const Map *map, double x, double y) {
    if (!map) return OUT_OF_BOUNDS_PENALTY;

    // Rzutowanie pozycji x, y na indeksy tablicy 
    int col = (int)floor(x);
    int row = (int)floor(y);

    // Obsługa wyjścia poza zakres mapy 
    if (col < 0 || col >= map->width || row < 0 || row >= map->height) {
        return OUT_OF_BOUNDS_PENALTY;
    }

    // Pobranie wartości z tablicy 1D: index = row * width + col
    return map->cells[row * map->width + col];
}


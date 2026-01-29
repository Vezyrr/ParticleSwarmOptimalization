#ifndef MAP_H
#define MAP_H


typedef struct {
    int width;          
    int height;         
    double *cells;      // Tablica 1D przechowująca wartości sygnału (spłaszczona 2D)
} Map;


 // Format pliku:
 // W H
// v1 v2 v3 

Map* load_map_from_file(const char *filename);

void free_map(Map *map);

/**
 * Pobiera wartość z mapy dla danych współrzędnych (double).
 * Realizuje rzutowanie na int i obsługę granic.
 */
double get_map_value(const Map *map, double x, double y);

#endif 
#ifndef GRID_H
#define GRID_H

#include <stddef.h>

// Forward declaration (opaque type)
typedef struct RGrid RGrid;

// Constructor / destructor
RGrid* create_rgrid(int grid_type, int weight_type, double rmax);
void destroy_rgrid(RGrid* grid);

#endif


#ifndef GRID_H
#define GRID_H

#include "../input/input.h"
#include <stddef.h>

// Forward declaration (opaque type)
typedef struct RGrid RGrid;

// Constructor / destructor
RGrid *create_rgrid(Input *input);
void destroy_rgrid(RGrid *in_grid);

#endif

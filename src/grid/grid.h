#ifndef GRID_H
#define GRID_H

#include "../input/input.h"
#include <stddef.h>

typedef struct RGrid RGrid;

struct RGrid {
  int grid_type;   // 1=evenly spaced radial grid
  int weight_type; // 1=trapezoidal rule.
  int nr;          // number of grid points.
  double rmax;
  double *grid_r; // radial grid is here.
  double *grid_w; // integration weights are here.
};

// Constructor / destructor
RGrid *create_rgrid(Input *input);
void destroy_rgrid(RGrid *in_grid);

#endif

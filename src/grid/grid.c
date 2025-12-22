#include "grid.h"
#include <stdio.h>
#include <stdlib.h>

struct RGrid {
  int grid_type;   // 1=evenly spaced radial grid
  int weight_type; // 1=trapezoidal rule.
  int nr;          // number of grid points.
  double rmax;
  double *grid_r; // radial grid is here.
  double *grid_w; // integration weights are here.
};

RGrid *create_rgrid(Input *input) {
  // FOR NOW ASSUME THAT THE grid_type AND weight_type IS ALL 1:
  double step = input->step;
  double rmax = input->r_max;
  int grid_type = input->grid_type;
  int weight_type = input->weight_type;

  int i, j, nr;
  double tmp_r, sum;
  double *int_test;

  // Calculate the nr based on step and rmax:
  tmp_r = step;
  nr = 1;
  while (tmp_r < rmax) {
    tmp_r = tmp_r + step;
    nr++;
  }

  // RGrid* RGrid = malloc(sizeof(RGrid) + 2*nr*sizeof(double));
  RGrid *r_grid = malloc(sizeof(RGrid));
  r_grid->grid_r = malloc(nr * sizeof(double));
  r_grid->grid_w = malloc(nr * sizeof(double));
  r_grid->grid_type = grid_type;
  r_grid->weight_type = weight_type;
  r_grid->nr = nr;
  r_grid->rmax = rmax;

  // Make the grid first:
  for (i = 0; i < nr; i++) {
    r_grid->grid_r[i] = (double)(i + 1) * step;
  }

  // Make the weights next:
  r_grid->grid_w[0] = 0.5 * (r_grid->grid_r[1] - r_grid->grid_r[0]);
  r_grid->grid_w[nr - 1] =
      0.5 * (r_grid->grid_r[nr - 1] - r_grid->grid_r[nr - 2]);
  for (i = 1; i < nr - 1; i++) {
    r_grid->grid_w[i] = 0.5 * (r_grid->grid_r[i + 1] - r_grid->grid_r[i - 1]);
  }

  // Test the radial grid by doing an integral test:
  // int_test = malloc(nr * sizeof(double));
  // for (i = 0; i < nr; i++) {
  //   int_test[i] = sin(r_grid->grid_r[i]);
  // }
  // for (i = 0; i < nr; i++) {
  //   sum += int_test[i] * r_grid->grid_w[i];
  // }
  // free(int_test);

  return r_grid;
}

void destroy_rgrid(RGrid *in_grid) {
  free(in_grid->grid_r);
  free(in_grid->grid_w);
  free(in_grid);
}

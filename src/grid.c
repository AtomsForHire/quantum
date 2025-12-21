#include "grid.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct RGrid {
  int grid_type; //1=evenly spaced radial grid
  int weight_type; //1=trapezoidal rule.
  int nr; //number of grid points.
  double rmax;
  double grid_r[]; //radial grid is here.
  double grid_w[]; //integration weights are here.
};

RGrid* create_rgrid(int grid_type, int weight_type, double rmax) {
  // FOR NOW ASSUME THAT THE grid_type AND weight_type IS ALL 1:
  double step=0.01; //hard code the step for now, later take from input structure.
  int i, j, nr;
  double temp_r, sum;
  double int_test[];

  //Calculate the nr based on step and rmax:
  tmp_r=step;
  nr=1;
  while (tmp_r < rmax) {
    tmp_r=tmp_r + step;
    nr++;
  }

  RGrid* RGrid = malloc(sizeof(RGrid) + 2*nr*sizeof(double));
  RGrid->grid_type = grid_type;
  RGrid->weight_type = weight_type;
  RGrid->nr=nr;
  RGrid->rmax=rmax;
  
  //Make the grid first:
  for (i = 0; i < nr; i++) {
    RGrid->grid_r[i] =  (double)(i + 1) * step;
  }
  
  //Make the weights next:
  RGrid->grid_w[0] = 0.5 * (RGrid->grid_r[1] - RGrid->grid_r[0]);
  RGrid->grid_w[nr - 1] = 0.5 * (RGrid->grid_r[nr - 1] - RGrid->grid_r[nr - 2]);
  for (i = 1; i < nr-1; i++) {
     RGrid->grid_w[i] = 0.5 * (RGrid->grid_r[i + 1] - RGrid->grid_r[i - 1]);
  }

  //Test the radial grid by doing an integral test:
  int_test = malloc(nr * sizeof(double));
  for (i = 0; i < nr; i++) {
    int_test[i] =  sin(RGrid->grid_r[i]);
  }
  for (i = 0; i < nr; i++) {
    sum += int_testf[i] * RGrid->grid_w[i];
  }
  free(int_test);

  printf("INT_TEST: %f, %f", sum, cos(0)-cos(rmax))
  
  return RGrid;
}

void destroy_rgrid(RGrid* inGrid) {
    free(inGrid);
}

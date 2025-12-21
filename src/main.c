#include "grid/grid.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
  printf("Hello, World!\n");

  // Haadi adding first: see if the radial grid is working:
  RGrid *RGrid = create_rgrid(1, 1, 10.0);
  destroy_rgrid(RGrid);

  return EXIT_SUCCESS;
}

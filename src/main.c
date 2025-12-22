#include "basis/basis.h"
#include "grid/grid.h"
#include "input/input.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  int status = 0;
  if (argc != 2) {
    fprintf(stderr, "Usage: ccc <setting toml file>\n");
    return EXIT_FAILURE;
  }

  Input *input;
  input = input_read_input_file(argv[1], &status);
  printf("Settings: %d %f\n", input->basis_type, input->alpha);

  // Haadi adding first: see if the radial grid is working:
  RGrid *RGrid = create_rgrid(1, 1, 10.0);
  destroy_rgrid(RGrid);

  if (input)
    free(input);

  return EXIT_SUCCESS;
}

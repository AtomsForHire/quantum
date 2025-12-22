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

  // Handle input
  Input *input;
  input = input_read_input_file(argv[1], &status);
  if (status != 0) {
    fprintf(stderr, "ERROR: Something went wrong in reading the input file\n");
    return EXIT_FAILURE;
  }

  input_pretty_print(input);

  RGrid *r_grid = create_rgrid(input);

  destroy_rgrid(r_grid);
  if (input)
    free(input);

  return EXIT_SUCCESS;
}

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

  // Test laguerre
  if (input->debug) {
    int nr = r_grid->nr;
    int n_basis = input->n_basis;
    double (*temp)[n_basis] = malloc(nr * sizeof(*temp));

    for (int k = 0; k < input->n_basis; k++) {
      double *temp2 =
          basis_gen_indiv_lag(k, input->alpha, r_grid->nr, r_grid->grid_r);
      for (int i = 0; i < nr; i++) {
        temp[i][k] = temp2[i];
      }
      free(temp2);
    }

    FILE *fptr = fopen("lag.txt", "w");
    for (int i = 0; i < nr; i++) {
      for (int k = 0; k < input->n_basis; k++) {
        fprintf(fptr, "%f ", temp[i][k]);
      }
      fprintf(fptr, "\n");
    }

    fclose(fptr);
    free(temp);
  }

  destroy_rgrid(r_grid);
  if (input)
    free(input);

  return EXIT_SUCCESS;
}

#include "input.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Input {
  // Basis parameters
  int basis_type;
  int l_max;
  int n_basis;
  double alpha;

  // Grid params
  int grid_type;
  int weight_type;
  double r_max;
  double step;
};

int get_int_or_fail(toml_table_t *tbl, const char *key, int *target) {
  toml_value_t d = toml_table_int(tbl, key);
  if (!d.ok) {
    fprintf(stderr, "ERROR: Config key '%s' is missing or not an integer\n",
            key);
    return -1; // Failure
  }
  *target = (int)d.u.i;
  return 0; // Success
}

int get_double_or_fail(toml_table_t *tbl, const char *key, double *target) {
  toml_value_t d = toml_table_double(tbl, key);
  if (!d.ok) {
    fprintf(stderr, "ERROR: Config key '%s' is missing or not an integer\n",
            key);
    return -1; // Failure
  }
  *target = (int)d.u.d;
  return 0; // Success
}

Input *input_read_input_file(char *filename, int *status) {
  Input *input = malloc(sizeof(Input));

  char errbuf[200];
  FILE *fptr = fopen(filename, "r");

  // Error handling
  if (fptr == NULL) {
    fprintf(stderr, "ERROR: Unable to read in settings file %s\n", filename);
    *status = 1;
    goto cleanup;
  }

  toml_table_t *tbl = toml_parse_file(fptr, errbuf, sizeof(errbuf));
  if (!tbl) {
    fprintf(stderr, "ERROR: Unable to parse toml - %s\n", errbuf);
    *status = 1;
    goto cleanup;
  }

  // Get grid table
  toml_table_t *grid_tbl = toml_table_table(tbl, "grid");
  if (grid_tbl) {
    if (get_int_or_fail(tbl, "basis_type", &input->basis_type) != 0)
      goto cleanup;
    if (get_int_or_fail(tbl, "l_max", &input->l_max) != 0)
      goto cleanup;
    if (get_int_or_fail(tbl, "n_basis", &input->n_basis) != 0)
      goto cleanup;
    if (get_double_or_fail(tbl, "alpha", &input->alpha) != 0)
      goto cleanup;
  } else {
    fprintf(stderr, "ERROR: something is wrong with the 'grid' table\n");
    *status = 1;
    goto cleanup;
  }

  toml_table_t *basis_tbl = toml_table_table(tbl, "basis");
  if (basis_tbl) {
    if (get_int_or_fail(tbl, "grid_type", &input->grid_type) != 0)
      goto cleanup;
    if (get_int_or_fail(tbl, "weight_type", &input->weight_type) != 0)
      goto cleanup;
    if (get_double_or_fail(tbl, "r_max", &input->r_max) != 0)
      goto cleanup;
    if (get_double_or_fail(tbl, "step", &input->step) != 0)
      goto cleanup;
  } else {
    fprintf(stderr, "ERROR: Something is wrong with the 'basis' table\n");
    *status = 1;
    goto cleanup;
  }

  // Success
  fclose(fptr);
  toml_free(tbl);
  return input;

// Error
cleanup:
  if (tbl)
    toml_free(tbl);
  if (fptr)
    fclose(fptr);
  if (input)
    free(input);

  return NULL;
}

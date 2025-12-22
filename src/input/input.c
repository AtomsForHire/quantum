#include "input.h"
#include "toml.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int get_int_or_fail(toml_datum_t tbl, const char *key, int *target) {
  toml_datum_t d = toml_seek(tbl, key);
  if (d.type != TOML_INT64) {
    fprintf(stderr, "ERROR: Config key '%s' is missing or not an integer\n",
            key);
    return -1; // Failure
  }
  *target = d.u.int64;
  return 0; // Success
}

int get_double_or_fail(toml_datum_t tbl, const char *key, double *target) {
  toml_datum_t d = toml_seek(tbl, key);
  if (d.type != TOML_FP64) {
    fprintf(stderr,
            "ERROR: Config key '%s' is missing or not a floating point\n", key);
    return -1; // Failure
  }
  *target = d.u.fp64;
  return 0; // Success
}

Input *input_read_input_file(char *filename, int *status) {
  Input *input = malloc(sizeof(Input));

  FILE *fptr = fopen(filename, "r");

  // Error handling
  if (fptr == NULL) {
    fprintf(stderr, "ERROR: Unable to read in settings file %s\n", filename);
    *status = 1;
    goto cleanup;
  }

  toml_result_t tbl = toml_parse_file(fptr);
  if (!tbl.ok) {
    fprintf(stderr, "ERROR: Unable to parse toml - %s\n", tbl.errmsg);
    *status = 1;
    goto cleanup;
  }

  // Get grid table
  // toml_table_t *grid_tbl = toml_table_table(tbl, "grid");
  if (get_int_or_fail(tbl.toptab, "basis.basis_type", &input->basis_type) != 0)
    goto cleanup;
  if (get_int_or_fail(tbl.toptab, "basis.l_max", &input->l_max) != 0)
    goto cleanup;
  if (get_int_or_fail(tbl.toptab, "basis.n_basis", &input->n_basis) != 0)
    goto cleanup;
  if (get_double_or_fail(tbl.toptab, "basis.alpha", &input->alpha) != 0)
    goto cleanup;

  if (get_int_or_fail(tbl.toptab, "grid.grid_type", &input->grid_type) != 0)
    goto cleanup;
  if (get_int_or_fail(tbl.toptab, "grid.weight_type", &input->weight_type) != 0)
    goto cleanup;
  if (get_double_or_fail(tbl.toptab, "grid.r_max", &input->r_max) != 0)
    goto cleanup;
  if (get_double_or_fail(tbl.toptab, "grid.step", &input->step) != 0)
    goto cleanup;

  // Success
  fclose(fptr);
  toml_free(tbl);
  return input;

// Error
cleanup:
  *status = 1;
  if (tbl.ok)
    toml_free(tbl);
  if (fptr)
    fclose(fptr);
  if (input)
    free(input);

  return NULL;
}

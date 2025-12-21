#include "input.h"
#include "toml.h"
#include <stdio.h>
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
    // Loop over all keys in a table.
    int l = toml_table_len(grid_tbl);
    for (int i = 0; i < l; i++) {
      int keylen;
      const char *key = toml_table_key(grid_tbl, i, &keylen);
      printf("key #%d: %s\n", i, key);
      // TODO: this should return toml_key_t or something, which also
      // includes the type. This actually requires a bit of frobbing with
      // the lexer, as that just sets the type of everything to STRING.
      //
      // Then we can also get rid of toml_table_{string,int,...} and just
      // parse it automatically.
    }
  } else {
    fprintf(stderr, "ERROR: something is wrong with the 'grid' table\n");
    *status = 1;
    goto cleanup;
  }

  toml_table_t *basis_tbl = toml_table_table(tbl, "basis");
  if (basis_tbl) {
    // Loop over all keys in a table.
    int l = toml_table_len(grid_tbl);
    for (int i = 0; i < l; i++) {
      int keylen;
      const char *key = toml_table_key(grid_tbl, i, &keylen);
      printf("key #%d: %s\n", i, key);
      // TODO: this should return toml_key_t or something, which also
      // includes the type. This actually requires a bit of frobbing with
      // the lexer, as that just sets the type of everything to STRING.
      //
      // Then we can also get rid of toml_table_{string,int,...} and just
      // parse it automatically.
    }
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

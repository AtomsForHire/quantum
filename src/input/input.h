#ifndef INPUT_H
#define INPUT_H
#include "toml.h"

typedef struct Input Input;

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

int get_int_or_fail(toml_datum_t tbl, const char *key, int *target);
int get_double_or_fail(toml_datum_t tbl, const char *key, double *target);
Input *input_read_input_file(char *filename, int *status);

#endif // !INPUT_H

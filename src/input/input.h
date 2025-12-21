#ifndef INPUT_H
#define INPUT_H
#include "toml.h"

typedef struct Input Input;

int get_int_or_fail(toml_table_t *tbl, const char *key, int *target);
int get_double_or_fail(toml_table_t *tbl, const char *key, double *target);
Input *input_read_input_file(char *filename, int *status);

#endif // !INPUT_H

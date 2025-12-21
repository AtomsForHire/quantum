#include "input.h"
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

Input read_input_file(char *filename, int *status) {
  Input input = {0};

  FILE *file = fopen(filename, "r");
  char line[1024];

  if (file == NULL) {
    fprintf(stderr, "ERROR: Unable to open file: %s\n", filename);
    *status = 1;
  }

  // Read the first data line
  if (fgets(line, sizeof(line), file)) {
    // Use strtok to split the string by commas
    char *token = strtok(line, ",");
    if (token)
      data.id = atoi(token);

    token = strtok(NULL, ",");
    if (token)
      data.threshold = atof(token);

    token = strtok(NULL, ",");
    if (token) {
      // Remove newline character if it exists at the end of the string
      token[strcspn(token, "\r\n")] = 0;
      strncpy(data.name, token, sizeof(data.name) - 1);
    }
  }

  return input;
}

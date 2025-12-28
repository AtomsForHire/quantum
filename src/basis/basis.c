#include "basis.h"
#include <stdio.h>
#include <stdlib.h>

double *basis_gen_indiv_lag(int k_max, int alpha, int len, double *grid) {
  double *lag = (double *)malloc(len * sizeof(double));

  double *temp_n = (double *)malloc(len * sizeof(double));
  double *temp_n_1 = (double *)malloc(len * sizeof(double));

  // Initialise
  for (int i = 0; i < len; i++) {
    temp_n[i] = 1.0;
  }

  for (int i = 0; i < len; i++) {
    temp_n_1[i] = 1 + (double)alpha - grid[i];
  }

  if (k_max == 0) {
    for (int i = 0; i < len; i++) {
      lag[i] = temp_n[i];
    }
  } else if (k_max == 1) {
    for (int i = 0; i < len; i++) {
      lag[i] = temp_n_1[i];
    }
  } else {
    // Loop over k's
    for (int k = 2; k <= k_max; k++) {
      double k_d = (double)k;
      // Loop over grid
      for (int j = 0; j < len; j++) {
        double a_d = (double)alpha;
        lag[j] = ((2.0 * (k_d - 1.0 + a_d - grid[j])) * temp_n_1[j] -
                  (k_d - 1.0 + a_d) * temp_n[j]) /
                 (k_d + 1.0);
      }

      // Update temp arrays
      for (int i = 0; i < len; i++) {
        temp_n[i] = temp_n_1[i];
        temp_n_1[i] = lag[i];
      }
    }
  }

  free(temp_n_1);
  free(temp_n);
  return lag;
}

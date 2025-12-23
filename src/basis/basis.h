#ifndef BASIS_H
#define BASIS_H
#include "../input/input.h"

typedef struct BasisFn BasisFn;
typedef struct Basis Basis;

struct BasisFn {
  int k;        // index of the basis function.
  int l;        // orbital angular momentum of the basis function.
  double alpha; // the exponential falloff functions.
  double f[];   // radial function for the basis function.
};

struct Basis {
  int basis_type; // 1=Sturmian Type.
  int N;          // size of basis.
  BasisFn *funs;  // the basis functions themselves.
};

// k goes up to n_basis
double *basis_gen_indiv_lag(int k, int alpha, int len_grid, double *grid);

#endif // BASIS_H

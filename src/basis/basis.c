#include <stdio.h>
#include <stdlib.h>

struct Basis {
  int basis_type; //1=Sturmian Type.
  int N; //size of basis.
  SturmBasisFn funs[]; //the basis functions themselves.
};

struct SturmBasisFn {
  int k; //index of the basis function.
  int l; //orbital angular momentum of the basis function.
  double alpha; //the exponential falloff functions.
  double f[]; //radial function for the basis function.
}

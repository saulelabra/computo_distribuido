#include <iostream>
#include "matrix.h"

using namespace std;

int main()
{
  matrix A(2, 3);
  matrix B(3, 4);

  A.populate(time(NULL), 10);
  A.printMatrix();

  B.populate(time(NULL), 10);
  B.printMatrix();

  matrix resultado = A.mult(B);
  resultado.printMatrix();
  return 0;
}

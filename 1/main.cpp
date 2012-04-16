
#include "IntersectionTest.h"

int main( void ) {

  IntersectionTest * p = new IntersectionTest("strecken/Strecken_Test.dat");
  p->parse();

  p->calculateIntersections();

  p->printResults();

  return 0;
}

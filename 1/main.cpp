

using namespace std;

#include "Line.h"
#include "IntersectionTest.h"

#define DEBUG 1

int main( void ) {

  IntersectionTest * p = new IntersectionTest("strecken/Strecken_test.dat");
  p->parse();

  vector<Line *> * lines = p->getLines();

  p->calculateIntersections();

  p->printResults();

  return 0;
}

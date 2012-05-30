#include "IntersectionTest.h"
#include "Cli.h"

int main( int argc, char *argv[] ) {

  Cli * cli = new Cli( argc, argv );

  IntersectionTest * p = new IntersectionTest( cli->getFilename() );

  p->parse();

  p->calculateIntersections();

  p->printResults();

  return 0;
}

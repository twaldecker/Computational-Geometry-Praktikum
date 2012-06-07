#include "SLIntersectionTest.h"
#include "Cli.h"

int main( int argc, char *argv[] ) {

  Cli * cli = new Cli( argc, argv );

  SLIntersectionTest * p = new SLIntersectionTest( cli->getFilename() );

  p->parse();

  p->calculateIntersections();

  p->printResults();

  return 0;
}

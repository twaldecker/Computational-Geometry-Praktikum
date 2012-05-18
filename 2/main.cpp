#include "PolygonTest.h"
#include "Cli.h"

int main( int argc, char *argv[] ) {

  Cli * cli = new Cli( argc, argv );

  PolygonTest * p = new PolygonTest( cli->getFilename() );
  p->parse();

  p->printResults();

  p->calculateAreas();

  return 0;
}

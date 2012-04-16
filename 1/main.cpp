#include <cstdlib>
#include "IntersectionTest.h"

void help() {
  cout << "strecken - a program to calculate intersections of lines.\n"
       << "usage:\n" << " strecken [-h] filename\n"
       << " -h displays this help message\n";
}


int main( int argc, char *argv[] ) {

  char opt;
  while( ( opt = getopt( argc, argv, "h" ) ) != -1 ) {
    switch( opt ) {
    case 'h':
      help();
      exit(0);
      break;
    }
  }

  if(optind+1 != argc) {
    cerr << "Wrong number of options\n";
    help();
    exit(1);
  }

  IntersectionTest * p = new IntersectionTest( argv[optind] );
  p->parse();

  p->calculateIntersections();

  p->printResults();

  return 0;
}

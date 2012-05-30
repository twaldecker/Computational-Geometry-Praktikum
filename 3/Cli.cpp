#include "Cli.h"

Cli::Cli( int argc, char* argv[] ) {

  /* see: http://www.gnu.org/savannah-checkouts/gnu/libc/manual/html_node/Getopt.html#Getopt */
  char opt;
  while( ( opt = getopt( argc, argv, "h" ) ) != -1 ) {
    switch( opt ) {
    case 'h':
      help(); /* just display the help message and exit */
      exit( 0 );
      break;
    }
  }

  /* if there is no option left,
   * the filename is missing!
   * check for exact match,
   * only one filename possible for now */
  if( optind + 1 != argc ) {
    cerr << argv[0] << ": invalid number of options" << endl;
    help();
    exit( 1 );
  }
  filename = argv[optind];
}

void Cli::help() {
  cout
    << "linesweep - a program to calculate intersections of lines." << endl
    << " Usage:" << endl
    << "  linesweep [-h] filename" << endl
    << "  -h displays this help message" << endl << endl
    << " File layout:" << endl
    << "  1.100 1.50001 1.3 1.5" << endl
    << "  which are the values of x and y of the startpoint and of the endpoint." << endl
    << "  Lines are separated by a newline."<< endl << endl
    << " Output:" << endl
    << "  The statistics are printed on stderr, the intersected lines on stdout."<< endl;
}

Cli::~Cli() {
  // TODO Auto-generated destructor stub
}

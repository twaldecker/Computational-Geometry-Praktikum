#include "Cli.h"

Cli::Cli( int argc, char* argv[] ) {

  /* see: http://www.gnu.org/savannah-checkouts/gnu/libc/manual/html_node/Getopt.html#Getopt */
  char opt;
    while( ( opt = getopt( argc, argv, "h" ) ) != -1 ) {
      switch( opt ) {
      case 'h':
        help(); /* just display the help message and exit */
        exit(0);
        break;
      }
    }

    /* if there is no option left,
     * the filename is missing!
     * check for exact match,
     * only one filename possible for now */
    if(optind+1 != argc) {
      cerr << "Wrong number of options" << endl;
      help();
      exit(1);
    }
    filename = argv[optind];
}

void Cli::help(){
  cout << "strecken - a program to calculate intersections of lines." << endl
       << "usage:" << endl
       << " strecken [-h] filename" << endl
       << " -h displays this help message" << endl;
}

Cli::~Cli() {
  // TODO Auto-generated destructor stub
}

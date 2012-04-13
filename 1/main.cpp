#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
using namespace std;

#include "Line.h"
#include "ElTest.h"

#define DEBUG 0

int main( void ) {

  string strline;
  ifstream myfile( "strecken/Strecken_10000.dat" );
  vector<Line *> lines;
  float a[4];
  ElTest tester;
  long counter = 0;
  clock_t start, stop;

  /* open file */
  if( myfile.is_open() ) {
    while( myfile.good() ) {
      /* parse line of file */
      getline( myfile, strline );
      sscanf( strline.c_str(), "%f %f %f %f", &a[0], &a[1], &a[2], &a[3] );
      /* store values in vector */
      Line* tmpin = new Line( a[0], a[1], a[2], a[3] );
      lines.push_back( tmpin );

      /* debug output */
#if DEBUG
      cout << "Input:  " << a[0] << " " << a[1] << " " << a[2] << " " << a[3]
      << endl;
      Line* tmpout = lines.back();
      cout << "Vector: " << tmpout->getA().getX() << " "
      << tmpout->getA().getY() << " " << tmpout->getB().getX() << " "
      << tmpout->getB().getY() << " " << endl;
#endif /* DEBUG */

    }
    myfile.close();
    /* start time */
    start = clock();
    /* intersection calculation with two iterator-loops */
    for( vector<Line *>::iterator outerit = lines.begin();
        outerit != lines.end(); outerit++ ) {
      for( vector<Line *>::iterator innerit = lines.begin();
          innerit != lines.end(); innerit++ ) {
        if( tester.intersect( *outerit, *innerit ) )
          counter++;
      }
    }
    /* stop time */
    stop = clock();
    /* output result */
    cout << counter - lines.size() << " intersections calculated in "
        << double( stop - start ) / CLOCKS_PER_SEC << " seconds"; /* counter - 1000 ?! */
  }
  /* error */
  else
    cout << "Unable to open file";

  return 0;
}

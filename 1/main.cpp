#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
using namespace std;

#include "Line.h"
#include "ElTest.h"

#define DEBUG 0

int main( void ) {

  vector<Line *> testlines; /* a vector containing pointer to Lines */
  long counter = 0;
  clock_t start, stop;

  /* open file and scream if I can not open it */
  ifstream datafile( "strecken/Strecken_10000.dat" );
  if( !datafile.is_open() ) {
    cout << "File not found";
    return 1;
  }

  /* process the file line by line */
  while( datafile.good() ) {
    /* read line, parse float values and store in temporary array */
    float a[4]; /* a temporary array to store the values */
    string strline; /* one line of the file */

    getline( datafile, strline );
    sscanf( strline.c_str(), "%f %f %f %f", &a[0], &a[1], &a[2], &a[3] );

    /* create a new Line object and store it in the vector */
    Line* tmpin = new Line( a[0], a[1], a[2], a[3] );
    testlines.push_back( tmpin );

#if DEBUG /* output */
    cout << "Input:  " << a[0] << " " << a[1] << " " << a[2] << " " << a[3]
    << endl;
    Line* tmpout = testlines.back();
    cout << "Vector: " << tmpout->getA().getX() << " "
    << tmpout->getA().getY() << " " << tmpout->getB().getX() << " "
    << tmpout->getB().getY() << " " << endl;
#endif /* DEBUG */

  }
  datafile.close();

  /* the file is now processed, the values are in the vector. Now its time to calculate and start the clock */
  start = clock();
  /* intersection calculation with two iterator-loops */
  for( vector<Line *>::iterator outerit = testlines.begin(); outerit != testlines.end();
      outerit++ ) {
    for( vector<Line *>::iterator innerit = testlines.begin();
        innerit != testlines.end(); innerit++ ) {
      if( (*outerit)->intersect(*innerit) )
        counter++;
    }
  }
  /* stop time */
  stop = clock();

  /* output result */
  cout << counter - testlines.size() << " intersections calculated in "
      << double( stop - start ) / CLOCKS_PER_SEC << " seconds"; /* counter - 1000 ?! */

  return 0;
}

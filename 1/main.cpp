#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#include "line.h"

#define DEBUG 1

int main( void ) {

  vector<Line *> lines;
  string strline;
  float a[4];
  ifstream myfile( "strecken/Strecken_1000.dat" );

  if( myfile.is_open() ) {
    while( myfile.good() ) {
      getline( myfile, strline );
      /* parse line of file */
      sscanf( strline.c_str(), "%f %f %f %f", &a[0], &a[1], &a[2], &a[3] );
      /* store values in vector */
      Line* tmpin = new Line( a[0], a[1], a[2], a[3] );
      lines.push_back( tmpin );

#ifdef DEBUG
      /* debug output */
      cout << "Input:  " << a[0] << " " << a[1] << " " << a[2] << " " << a[3]
          << endl;
      Line* tmpout = lines.back();
      cout << "Vector: " << tmpout->getA().getX() << " "
          << tmpout->getA().getY() << " " << tmpout->getB().getX() << " "
          << tmpout->getB().getY() << " " << endl;
#endif /* DEBUG */
    }
    myfile.close();
  }
  else
    cout << "Unable to open file";

  return 0;
}

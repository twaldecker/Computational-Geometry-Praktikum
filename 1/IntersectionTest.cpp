/*
 * FileParser.cpp
 *
 *  Created on: Apr 14, 2012
 *      Author: thomas
 */

#include "IntersectionTest.h"

IntersectionTest::IntersectionTest( string filename ) :
    filename( filename ) {
}

/**
 *  open file and scream if I can not open it
 */
int IntersectionTest::open() {
  file.open( filename.c_str() );
  if( !file.is_open() ) {
    cerr << "File not found";
    return 1;
  }
  return 0;
}

/* process the file line by line */
int IntersectionTest::parse() {
  open(); // first open the file, then read
  while( !file.eof() ) {
    /* read line, parse float values and store in temporary array */
    float a[4]; /* a temporary array to store the values */
    string strline; /* one line of the file */

    getline( file, strline );
    sscanf( strline.c_str(), "%f %f %f %f", &a[0], &a[1], &a[2], &a[3] );

    /* create a new Line object and store it in the vector */
    Line* tmpin = new Line( a[0], a[1], a[2], a[3] );
    lines.push_back( tmpin );

#if DEBUG /* output */
    cout << "Input:  " << a[0] << " " << a[1] << " " << a[2] << " " << a[3]
    << endl;
    Line* tmpout = lines.back();
    cout << "Vector: " << tmpout->getA().getX() << " "
    << tmpout->getA().getY() << " " << tmpout->getB().getX() << " "
    << tmpout->getB().getY() << " " << endl;
#endif /* DEBUG */

  }
  return 0;
}

IntersectionTest::~IntersectionTest() {
  file.close();
  // TODO Auto-generated destructor stub
}


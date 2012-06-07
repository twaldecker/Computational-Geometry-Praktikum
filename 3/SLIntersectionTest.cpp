#include "SLIntersectionTest.h"

SLIntersectionTest::SLIntersectionTest( string filename ) :
    filename( filename ), lineCount( 0 ), intersectionCount( 0 ) {
}

/**
 *  open file and kill me if i cant open it.
 */
void SLIntersectionTest::open() {

  file.open( filename.c_str(), ios::in );

  if( !file.is_open() ) {
    cerr << "File " << filename << " not found" << endl;
    exit( 1 );
  }
}

void SLIntersectionTest::handleEvent( const SLEvent& e ) {

  switch( e.getType() ) {
  case BEGIN:
    cout << "handle begin of line" << endl;
    break;
  case END:
    cout << "handle end of line" << endl;
    break;
  case INTERSECTION:
    cout << "handle intersection" << endl;
    break;
  }

}

void SLIntersectionTest::calculateIntersections() {

  map<float, SLEvent *>::const_iterator it;
  start = clock();

  while( !xStruct.empty() ) {
    it = xStruct.begin();
    SLIntersectionTest::handleEvent( *( *it ).second );
    xStruct.erase( xStruct.begin() );
  }

  stop = clock();
}

void SLIntersectionTest::printResults() {
  cerr << "Number of Lines: " << lineCount << endl << intersectionCount
      << " intersections" << endl << "calculated in " << getTime() << " seconds"
      << endl;

}

/* process the file line by line */
void SLIntersectionTest::parse() {
  float coords[4]; /* a temporary array to store the values */
  string strline; /* one line of the file */
  open(); // first open the file, then read
  while( getline( file, strline ) ) {
    /* read line, parse float values and store in temporary array */
    sscanf( strline.c_str(), "%f %f %f %f", coords, coords + 1, coords + 2,
        coords + 3 );
    /* create new Point2d/Line objects and store them */

    SLEvent * slb = new SLEvent( BEGIN, Point2d( coords[0], coords[1] ) );
    SLEvent * sle = new SLEvent( END, Point2d( coords[2], coords[3] ) );

    xStruct.insert( pair<float, SLEvent *>( coords[0], slb ) );
    xStruct.insert( pair<float, SLEvent *>( coords[2], sle ) );

    lineCount++;

  }
}

SLIntersectionTest::~SLIntersectionTest() {
  file.close();
  // TODO Auto-generated destructor stub
}

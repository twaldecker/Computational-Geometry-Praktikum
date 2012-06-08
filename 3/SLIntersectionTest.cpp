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

  multimap<float, Line *>::iterator it;
  multimap<float, Line *>::iterator lastelement;

  switch( e.getType() ) {
  case BEGIN:
    /* store line in yStruct */
    it = yStruct.insert(
        pair<float, Line *>( e.getCoords().getY(), e.getLines()[0] ) );
    /* check intersection with the two neighbors if they exist */
    if( it != yStruct.begin() ) {
      if( it->second->intersect( ( it-- )->second ) )
        intersectionCount++;
    }
    lastelement = yStruct.end();
    lastelement--;/* .end() is an iterator referring to the past-the-end element !!! */
    if( it != lastelement ) {
      if( it->second->intersect( ( it++ )->second ) )
        intersectionCount++;
    }
    break;

  case END:
    /* TODO: find method maybe not enough to identify the correct object */
    it = yStruct.find( e.getLines().front()->getA().getY() );
    if( it == yStruct.end() )
      break;
    /* check intersection between the two neighbors if they exist */
    lastelement = yStruct.end();
    lastelement--;/* .end() is an iterator referring to the past-the-end element !!! */
    if( ( it != yStruct.begin() ) && ( it != lastelement ) ) {
      if( ( it-- )->second->intersect( ( it++ )->second ) )
        intersectionCount++;
      yStruct.erase( it );
    }
    break;

  case INTERSECTION:
    cout << "handle intersection" << endl;
    break;
  }

}

void SLIntersectionTest::calculateIntersections() {

  map<float, SLEvent *>::iterator it;

  start = clock();

  //cout << "iterating over " << xStruct.size() << " events" << endl;

  while( !xStruct.empty() ) {
    it = xStruct.begin();
    SLIntersectionTest::handleEvent( *it->second );
    /*if( it != xStruct.end() ) {
     cout << it->second->getCoords().getX() << ", "
     << it->second->getCoords().getY() << endl;
     }*/
    xStruct.erase( it );

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
    /* create new Line/SLEvent objects and store them */
    vector<Line *> lines;
    Line * line = new Line( coords[0], coords[1], coords[2], coords[3] );
    lines.push_back( line );
    SLEvent * slb = new SLEvent( BEGIN, Point2d( coords[0], coords[1] ),
        lines );
    SLEvent * sle = new SLEvent( END, Point2d( coords[2], coords[3] ), lines );
    /* use the x-coordinate as key */
    xStruct.insert( pair<float, SLEvent *>( coords[0], slb ) );
    xStruct.insert( pair<float, SLEvent *>( coords[2], sle ) );
    /* line counter */
    lineCount++;
  }
}

SLIntersectionTest::~SLIntersectionTest() {
  file.close();
  // TODO Auto-generated destructor stub
}

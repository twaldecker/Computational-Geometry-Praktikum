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
    /* store line in yStruct: use y-coordinate of first point as key */
    it = yStruct.insert(
        pair<float, Line *>( e.getCoords().getY(), e.getLines()[0] ) );
    /* check intersection with the two neighbors if they exist */
    if( it != yStruct.begin() ) {
      if( it->second->intersect( ( it-- )->second ) )
        intersectionCount++; /* TODO: calculate coordinates store them and generate SLEvent */
    }
    lastelement = yStruct.end();
    lastelement--; /* .end() is an iterator referring to the past-the-end element !!! */
    if( it != lastelement ) {
      if( it->second->intersect( ( it++ )->second ) )
        intersectionCount++; /* TODO: calculate coordinates store them and generate SLEvent */
    }
    break;

  case END:
    /* identify the correct object not only by key but also by the line */
    do {
      it = yStruct.find( e.getLines()[0]->getA().getY() );
    } while( it->second != e.getLines()[0] );
    /* check intersection between the two neighbors if they exist */
    lastelement = yStruct.end();
    lastelement--; /* .end() is an iterator referring to the past-the-end element !!! */
    if( ( it != yStruct.begin() ) && ( it != lastelement ) ) {
      if( ( it-- )->second->intersect( ( it++ )->second ) )
        intersectionCount++;
    }
    /* remove line object */
    yStruct.erase( it );
    break;

  case INTERSECTION:
    /* TODO: handler for intersection events */
    break;
  }

}

void SLIntersectionTest::calculateIntersections() {

  map<float, SLEvent *>::iterator it;

  start = clock();
  while( !xStruct.empty() ) {
    it = xStruct.begin();
    SLIntersectionTest::handleEvent( *it->second );
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

  open(); /* first open the file, then read */
  while( getline( file, strline ) ) {
    /* read line, parse float values and store them in the temporary array */
    sscanf( strline.c_str(), "%f %f %f %f", coords, coords + 1, coords + 2,
        coords + 3 );
    /* create new Lines/SLEvents and store them */

    /* BEGIN/END depends on the order of the x-coordinates */
    if( coords[0] <= coords[2] ) {
      vector<Line *> lines;
      Line * line = new Line( coords[0], coords[1], coords[2], coords[3] );
      lines.push_back( line );
      SLEvent * slb = new SLEvent( BEGIN, Point2d( coords[0], coords[1] ),
          lines );
      SLEvent * sle = new SLEvent( END, Point2d( coords[2], coords[3] ),
          lines );
      /* use the x-coordinate as key */
      xStruct.insert( pair<float, SLEvent *>( coords[0], slb ) );
      xStruct.insert( pair<float, SLEvent *>( coords[2], sle ) );
    }
    else {
      vector<Line *> lines;
      Line * line = new Line( coords[2], coords[3], coords[0], coords[1] );
      lines.push_back( line );
      SLEvent * slb = new SLEvent( BEGIN, Point2d( coords[2], coords[3] ),
          lines );
      SLEvent * sle = new SLEvent( END, Point2d( coords[0], coords[1] ),
          lines );
      /* use the x-coordinate as key */
      xStruct.insert( pair<float, SLEvent *>( coords[2], slb ) );
      xStruct.insert( pair<float, SLEvent *>( coords[0], sle ) );
    }
    /* line counter */
    lineCount++;
  }
}

SLIntersectionTest::~SLIntersectionTest() {
  file.close();
// TODO Auto-generated destructor stub
}

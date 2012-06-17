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

  list<Line *>::iterator it = yStruct.begin();
  list<Line *>::iterator it2;
  list<Line *>::iterator next;
  list<Line *>::iterator prev;
  Point2d intersection; /* the intersection point returned from intersect */

  switch( e.getType() ) {
  case BEGIN:
    /* at the Beginning of a line insert it in the yStruct and
     * check if it intersects with the upper or lower line y-wise
     * if it is not the only line in yStruct check it with the lower and higher lines.
     */

    //move the iterator to the position of the line with lower y
    while( e.getLines()[0]->getA().getY() < ( *it )->getA().getY() ) //ERROR HERE?
      it++;
    it++;

    //insert the line.
    it = yStruct.insert( it, e.getLines()[0] );

    next = prev = it;
    next++;
    prev--;

    //test intersection with top and bottom line
    if( ( *it )->intersect( *prev, intersection ) ) {
      xStruct.insert(
          pair<float, SLEvent *>( intersection.getX(),
              new SLEvent( INTERSECTION, intersection, **it, **prev ) ) );
      intersections.insert( &intersection );
    }

    if( ( *it )->intersect( *next, intersection ) ) {
      xStruct.insert(
          pair<float, SLEvent *>( intersection.getX(),
              new SLEvent( INTERSECTION, intersection, **it, **next ) ) );
      intersections.insert( &intersection );
    }

    break;

  case END:
    /* at the end of a line check if the new lower and upper line intersect each other. */

    while( *it != e.getLines()[0] )
      it++;

    next = prev = it;
    next++;
    prev--;

    yStruct.erase( it );

    if( ( *next )->intersect( *prev, intersection ) ) {
      xStruct.insert(
          pair<float, SLEvent *>( intersection.getX(),
              new SLEvent( INTERSECTION, intersection, **prev, **next ) ) );
      intersections.insert( &intersection );
    }

    break;

  case INTERSECTION:
    /* at the intersection swap the two intersecting lines and check it with the new neighbors.*/


    /*do {
     it = yStruct.find( e.getLines()[0]->getA().getY() );
     } while( it->second != e.getLines()[0] );
     */

    /* now check the upper line with the line over the two lines */

    /* check teh under line with the line below the two lines */

    break;
  }

}

void SLIntersectionTest::calculateIntersections() {

  multimap<float, SLEvent *>::iterator it;

  start = clock();
  while( !xStruct.empty() ) {
    it = xStruct.begin();
    SLIntersectionTest::handleEvent( *it->second );
    xStruct.erase( it );
  }
  stop = clock();
}

void SLIntersectionTest::printResults() {

  cerr << "Number of Lines: " << lineCount << endl << intersections.size()
      << " intersections" << endl << "calculated in " << getTime() << " seconds"
      << endl;

}

/* process the file line by line */
void SLIntersectionTest::parse() {

  Line * line;
  float coords[4]; /* a temporary array to store the values */
  string strline; /* one line of the file */
  float ymax = 0, ymin = 0;
  bool first = 1;

  open(); /* first open the file, then read */
  while( getline( file, strline ) ) {
    /* read line, parse float values and store them in the temporary array */
    sscanf( strline.c_str(), "%f %f %f %f", coords, coords + 1, coords + 2,
        coords + 3 );

    /* compare the x-coordinates of the points. if the second point is lower swap the points. */
    if( coords[2] <= coords[0] ) {
      swap( coords[2], coords[0] );
      swap( coords[1], coords[3] );
    } /* line begins now at smaller x-value */

    /*
     * store the max and min values of the coordinates.
     * first is only in the first loop 1.
     **/
    if( ( coords[1] < ymin ) || first )
      ymin = coords[1];
    if( ( coords[1] > ymax ) || first )
      ymax = coords[1];

    first = 0;

    if( ( coords[3] < ymin ) )
      ymin = coords[3];
    if( ( coords[3] > ymax ) )
      ymax = coords[3];

    /* create a line vector, add the line and store it in the Events*/
    line = new Line( coords[0], coords[1], coords[2], coords[3] );

    /* create new SLEvents and store them */
    SLEvent * slb = new SLEvent( BEGIN, Point2d( coords[0], coords[1] ),
        *line );
    SLEvent * sle = new SLEvent( END, Point2d( coords[2], coords[3] ), *line );

    /* use the x-coordinate as key */
    xStruct.insert( pair<float, SLEvent *>( coords[0], slb ) );
    xStruct.insert( pair<float, SLEvent *>( coords[2], sle ) );

    /* line counter */
    lineCount++;
  }

  /* Now create dummy lines with the highest / lowest yValue */
  line = new Line( 0, ymin - 1, 1, ymin - 1 );
  yStruct.push_front( line );
  line = new Line( 0, ymax + 1, 1, ymax + 1 );
  yStruct.push_back( line );

}

SLIntersectionTest::~SLIntersectionTest() {
  file.close();
// TODO Auto-generated destructor stub
}

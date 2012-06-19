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
    while( ( e.getLines()[0]->getA().getY() ) > ( ( *it )->getA().getY() ) )
      it++;

    //insert the line.
    it = yStruct.insert( it, e.getLines()[0] );

    next = prev = it;
    next++;
    prev--;

    //test intersection with top and bottom line
    intersects( *prev, *it );
    intersects( *it, *next );

    break;

  case END:
    /* at the end of a line check if the new lower and upper line intersect each other. */

    while( *it != e.getLines()[0] )
      it++;

    next = prev = it;
    next++;
    prev--;

    yStruct.erase( it );

    intersects( *prev, *next );

    break;

  case INTERSECTION:
    /* at the intersection swap the two intersecting lines and check it with the new neighbors.
     * note that before the intersection in e.lines[0] is the lower line and e.lines[1] is the upper line.
     **/
    it2 = it;
    while( *it != e.getLines()[0] )
      it++;
    while( *it2 != e.getLines()[1] )
      it2++;

    //swap lines: store line from it2, remove it and insert it before it.
    Line * l = *it2;
    yStruct.erase( it2 );
    it2 = yStruct.insert( it, l );

    next = it;
    next++;
    prev = it2;
    prev--;

    //test intersection with top and bottom line
    intersects( *prev, *it );
    intersects( *it2, *next );

    break;
  }

}

/**
 * This is a helper function which calls the Line->intersect method and adds a new Event.
 */
bool SLIntersectionTest::intersects( Line * a, Line * b ) {
  Point2d * intersection = new Point2d;

  if( ( a )->intersect( b, *intersection ) ) {
    xStruct.insert(
        pair<float, SLEvent *>( intersection->getX(),
            new SLEvent( INTERSECTION, *intersection, *a, *b ) ) );
    intersections.insert( intersection );
    return true;
  }
  return false;
}

void SLIntersectionTest::calculateIntersections() {

  multimap<float, SLEvent *>::iterator it = xStruct.begin();

  start = clock();
  while( it != xStruct.end() ) {
    SLIntersectionTest::handleEvent( *it->second );
    it++;
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
  float xmax = 0, xmin = 0; /* for debug purposes */
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
    if( ( coords[0] < xmin ) || first )
      xmin = coords[0];
    if( ( coords[0] > xmax ) || first )
      xmax = coords[0];

    first = 0;

    if( ( coords[3] < ymin ) )
      ymin = coords[3];
    if( ( coords[3] > ymax ) )
      ymax = coords[3];
    if( ( coords[2] < xmin ) )
      xmin = coords[2];
    if( ( coords[2] > xmax ) )
      xmax = coords[2];

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
  line = new Line( 0, ymin - 1, 1, ymin - 1 ); // break here and inspect xmin, xmax, ymin, ymax
  yStruct.push_front( line );
  line = new Line( 0, ymax + 1, 1, ymax + 1 );
  yStruct.push_back( line );

}

SLIntersectionTest::~SLIntersectionTest() {
  file.close();
// TODO Auto-generated destructor stub
}

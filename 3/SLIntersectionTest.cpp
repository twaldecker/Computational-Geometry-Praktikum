#include "SLIntersectionTest.h"

SLIntersectionTest::SLIntersectionTest( string filename ) :
    filename( filename ), lineCount( 0 ) {
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

/**
 * find the line associated by key in the multimap.
 */
bool SLIntersectionTest::yFind(const float key, const Line * line, multimap<float, Line *>::iterator * it) {
  pair<multimap<float, Line *>::iterator,multimap<float, Line *>::iterator> range; // a pair of iterators. the return value of multimap.equal_range

  range = yStruct.equal_range(key);


  for (*it = range.first; *it != range.second; ++(*it)) {
    if( (*it)->second == line)
      return true;
  }

  return false;
}


void SLIntersectionTest::handleEvent( const SLEvent& e ) {

  multimap<float, Line *>::iterator it = yStruct.begin();
  multimap<float, Line *>::iterator it2;
  multimap<float, Line *>::iterator next;
  multimap<float, Line *>::iterator prev;
  Point2d intersection; /* the intersection point returned from intersect */

  float key1, key2;
  if( e.getLine()->getYkey() != 0 )
    key1 = e.getLine()->getYkey();
  else
    key1 = e.getLine()->getA().getY();

  switch( e.getType() ) {
  case BEGIN:
    /* at the Beginning of a line insert it in the yStruct and
     * check if it intersects with the upper or lower line y-wise
     * if it is not the only line in yStruct check it with the lower and higher lines.
     */

    //insert a line
    it = yStruct.insert( pair<float, Line*>( key1, e.getLine() ) );

    next = prev = it;
    next++;
    prev--;

    //test intersection with top and bottom line
    intersects( prev->second, it->second );
    intersects( it->second, next->second );

    break;

  case END:
    /* at the end of a line check if the new lower and upper line intersect each other. */

    yFind(key1, e.getLine(), &it);

    next = prev = it;
    next++;
    prev--;

    yStruct.erase( it );

    intersects( prev->second, next->second );

    break;

  case INTERSECTION:
    /* at the intersection swap the two intersecting lines and check it with the new neighbors.
     * note that before the intersection in e.lines[0] is the lower line and e.lines[1] is the upper line.
     **/
    it2 = it;
    if( e.getLines()[1]->getYkey() != 0 )
      key2 = e.getLines()[1]->getYkey();
    else
      key2 = e.getLines()[1]->getA().getY();

    yFind(key1, e.getLine(), &it);
    yFind(key2, e.getLines()[1], &it2);

    //swap lines
    Line * l2 = it2->second;
    Line *l = it->second;

    yStruct.erase( it2 );
    yStruct.erase( it );

    l2->setYkey( l->getA().getY() );
    l->setYkey( l2->getA().getY() );

    it = yStruct.insert( pair<float, Line*>( l->getYkey(), l ) );
    it2 = yStruct.insert( pair<float, Line*>( l2->getYkey(), l2 ) );

    next = it;
    next++;
    prev = it2;
    prev--;

    //test intersection with top and bottom line
    intersects( it->second, next->second );
    intersects( prev->second, it2->second );

    break;
  }

}

/**
 * This is a helper function which calls the Line->intersect method and adds a new Event.
 */
bool SLIntersectionTest::intersects( Line * a, Line * b ) {
  Point2d * intersection = new Point2d;
  pair<multimap<float, SLEvent *>::iterator,multimap<float, SLEvent *>::iterator> range; // a pair of iterators. the return value of multimap.equal_range
  multimap<float, SLEvent *>::iterator it;

  if( ( a )->intersect( b, *intersection ) ) {

    //search if intersection already exists in xstruct.
    range = xStruct.equal_range(intersection->getX());

    for (it = range.first; it != range.second; it++) {
      if(
          (it->second->getType() == INTERSECTION)
          &&
          (it->second->getCoords() == *intersection)
          &&
          ((it->second->getLines()[0] == a) || (it->second->getLines()[0] == b))
          &&
          ((it->second->getLines()[1] == a) || (it->second->getLines()[1] == b))
        ) {
        return false;
      }
    }


    xStruct.insert(
        pair<float, SLEvent *>( intersection->getX(),
            new SLEvent( INTERSECTION, *intersection, *a, *b ) ) );
    //intersections.insert( *intersection );
    return true;
  }
  return false;
}


/**
 * This method iterates over the xStruct. If the event was not a intersection event, then it is removed from the map.
 */
void SLIntersectionTest::calculateIntersections() {

  multimap<float, SLEvent *>::iterator it = xStruct.begin();

  start = clock();
  while( it != xStruct.end() ) {
    SLIntersectionTest::handleEvent( *it->second );
    if(it->second->getType() != INTERSECTION) {
      multimap<float, SLEvent *>::iterator next = it;
      next++;
      xStruct.erase(it);
      it = next;
    }
    else {
      it++;
    }
  }
  stop = clock();
}

void SLIntersectionTest::printResults() {

  cerr << "Number of Lines: " << lineCount << endl << xStruct.size()
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
  yStruct.insert( pair<float, Line *>( line->getA().getY(), line ));
  line = new Line( 0, ymax + 1, 1, ymax + 1 );
  yStruct.insert( pair<float, Line *>( line->getA().getY(), line ));

}

SLIntersectionTest::~SLIntersectionTest() {
  file.close();
// TODO Auto-generated destructor stub
}

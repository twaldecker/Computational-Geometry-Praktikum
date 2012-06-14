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
  multimap<float, Line *>::iterator back;
  multimap<float, Line *>::iterator next;
  multimap<float, Line *>::iterator lastelement;
  vector<Line *> lines;
  Point2d * ip;

  switch( e.getType() ) {
  case BEGIN:
    /* at the Beginning of a line check if it intersects with the upper or lower line y-wise */
    /* store line in yStruct: use y-coordinate of first point as key */
    it = yStruct.insert(
        pair<float, Line *>( e.getCoords().getY(), e.getLines()[0] ) );
    /* check intersection with the two neighbors if they exist */
    if( it != yStruct.begin() ) {
      back = --it;
      it++;
      if( it->second->intersect( back->second, ip ) ) {
        /* generate new event and store it */
        lines.push_back( it->second );
        lines.push_back( back->second );
        SLEvent * sli = new SLEvent( INTERSECTION, *ip, lines );
        /* use the x-coordinate as key */
        xStruct.insert( pair<float, SLEvent *>( ip->getX(), sli ) );
        /* insert intersection in map */
        intersections.insert( ip );
      }
    }
    lastelement = yStruct.end();
    lastelement--; /* .end() is an iterator referring to the past-the-end element !!! */
    if( it != lastelement ) {
      next = ++it;
      it--;
      if( it->second->intersect( next->second, ip ) ) {
        /* generate new event and store it */
        lines.push_back( it->second );
        lines.push_back( next->second );
        SLEvent * sli = new SLEvent( INTERSECTION, *ip, lines );
        /* use the x-coordinate as key */
        xStruct.insert( pair<float, SLEvent *>( ip->getX(), sli ) );
        /* insert intersection in map */
        intersections.insert( ip );
      }
    }
    break;

  case END:
    /* at the end of a line check if the new lower and upper line intersect each other. */
    /* identify the correct object not only by key but also by the line */
    do {
      it = yStruct.find( e.getLines()[0]->getA().getY() );
    } while( it->second != e.getLines()[0] );
    /* check intersection between the two neighbors if they exist */
    lastelement = yStruct.end();
    lastelement--; /* .end() is an iterator referring to the past-the-end element !!! */
    if( ( it != yStruct.begin() ) && ( it != lastelement ) ) {
      back = --it;
      it++;
      next = ++it;
      it--;
      if( back->second->intersect( next->second, ip ) ) {
        /* generate new event and store it */
        lines.push_back( back->second );
        lines.push_back( next->second );
        SLEvent * sli = new SLEvent( INTERSECTION, *ip, lines );
        /* use the x-coordinate as key */
        xStruct.insert( pair<float, SLEvent *>( ip->getX(), sli ) );
        /* insert intersection in map */
        intersections.insert( ip );
      }
    }
    /* remove line object */
    yStruct.erase( it );
    break;

  case INTERSECTION:
    /* TODO: check code */
    /* at the intersection swap the two intersecting lines and check it with the new neighbors. */
    /* swap the lines in the yStruct */
    /*find the line in the point in the y-struct.*/
    do {
      it = yStruct.find( e.getLines()[0]->getA().getY() );
    } while( it->second != e.getLines()[0] );




    /* now check the upper line with the line over the two lines */

    /* check teh under line with the line below the two lines */

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

  cerr << "Number of Lines: " << lineCount << endl << intersections.size()
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

    /* compare the x-coordinates of the points. if the second point is lower swap the points. */
    if( coords[2] <= coords[0] ) {
      swap( coords[2], coords[0] );
      swap( coords[1], coords[3] );
    } /* line begins now at smaller x-value */

    /* create a line vector, add the line and store it in the Events*/
    vector<Line *> lines;
    Line * line = new Line( coords[0], coords[1], coords[2], coords[3] );
    lines.push_back( line );

    /* create new SLEvents and store them */
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

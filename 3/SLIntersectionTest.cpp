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

  multimap<float, Line *>::iterator it, prev, next, lastelement;

  float key; /* debug variable */

  switch( e.getType() ) {
  case BEGIN:
    /* store line in yStruct: use y-coordinate of first point as key */
    it = yStruct.insert(
        pair<float, Line *>( e.getLines()[0]->getA().getY(),
            e.getLines()[0] ) );
    /* check intersection with the two neighbors if they exist */
    if( it != yStruct.begin() ) {
      prev = it;
      prev--;
      intersect( it->second, prev->second );
    }
    lastelement = yStruct.end();
    lastelement--; /* .end() is an iterator referring to the past-the-end element !!! */
    if( it != lastelement ) {
      next = it;
      next++;
      intersect( it->second, next->second );
    }
    break;

  case END:
    /* identify the correct object not only by key but also by the line */
    key = e.getLines()[0]->getA().getY();
    it = yStruct.find( key );
    if( it == yStruct.end() )
      break;
    /* check intersection between the two neighbors if they exist */
    lastelement = yStruct.end();
    lastelement--; /* .end() is an iterator referring to the past-the-end element !!! */
    if( ( it != yStruct.begin() ) && ( it != lastelement ) ) {
      prev = it;
      prev--;
      next = it;
      next++;
      intersect( prev->second, next->second );
    }
    /* remove line object */
    yStruct.erase( it );
    break;

  case INTERSECTION:
    multimap<float, Line *>::iterator it2, prev2, next2;
    /* identify the correct objects */
    key = e.getLines()[0]->getA().getY();
    it = yStruct.find( key );
    if( it == yStruct.end() )
      break;

    key = e.getLines()[1]->getA().getY();
    it2 = yStruct.find( key );
    if( it2 == yStruct.end() )
      break;

    /* intersect with new neighbors if they exist */
    lastelement = yStruct.end();
    lastelement--; /* .end() is an iterator referring to the past-the-end element !!! */

    if( it != yStruct.begin() ) {
      prev = it;
      prev--;
      intersect( it2->second, prev->second );
    }
    if( it != lastelement ) {
      next = it;
      next++;
      intersect( it2->second, next->second );
    }
    if( it2 != yStruct.begin() ) {
      prev2 = it2;
      prev2--;
      intersect( it->second, prev2->second );
    }
    if( it2 != lastelement ) {
      next2 = it2;
      next2++;
      intersect( it->second, next2->second );
    }

    /* remove objects */
    yStruct.erase( it );
    yStruct.erase( it2 );
    /* and store them with the new key */
    yStruct.insert(
        pair<float, Line *>( e.getLines()[0]->getA().getY(),
            e.getLines()[1] ) );
    yStruct.insert(
        pair<float, Line *>( e.getLines()[1]->getA().getY(),
            e.getLines()[0] ) );
    break;
  }
}

void SLIntersectionTest::intersect( Line * a, Line * b ) {

  Point2d * ip;
  vector<Line *> lines;

  if( a->intersect( b, ip ) ) {
    if( intersections.find( ip ) == intersections.end() ) {
      /* generate new event and store it */
      lines.push_back( a );
      lines.push_back( b );
      SLEvent * sli = new SLEvent( INTERSECTION, *ip, lines );
      /* use the x-coordinate as key */
      xStruct.insert( pair<float, SLEvent *>( ip->getX(), sli ) );
      /* insert intersection in map */
      intersections.insert( ip );
    }
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

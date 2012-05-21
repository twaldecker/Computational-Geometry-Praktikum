#include "Polygon.h"

Polygon::Polygon() {
  // TODO Auto-generated constructor stub
}

Polygon::~Polygon() {
  // TODO Auto-generated destructor stub
}

void Polygon::addPoint( const float x, const float y ) {
  Point2d * p = new Point2d( x, y );
  points.push_back( p );
}

/**
 * This method implements the calculation of the area of the polygon
 * */
float Polygon::area() const {
  float area = 0;

  //Gaußsche Dreiecksformel
  //iterate over points
  for( vector<Point2d *>::const_iterator it = points.begin(); it != points.end();
      it++ ) {
    /*to implement the module I used the (if)?then:else construct. Ugly but works. */
    area +=
        ( *it )->getY()
            * ( ( *( it == points.begin() ? points.end() - 1 : it - 1 ) )->getX()
                - ( *( it + 1 == points.end() ? points.begin() : it + 1 ) )->getX() );
  }
  area = abs( area / 2 );

  return area;
}

bool Polygon::pip() const {
  //bestimme einen Punkt der Außerhalb des Polygons liegt.
  //Nehme die maximalen werte in x- und y- richtung und addiere (1,1)
  Point2d * add = new Point2d(1,1);
  Point2d a = Polygon::max() + Point2d(1,1);
  cout << a;



  return true;
}

Point2d& Polygon::max() const {
  //initialize with 0,0
  float maxX = 0, maxY = 0;

  //run through all points and find the max coordinates.
  for( vector<Point2d *>::const_iterator it = points.begin(); it != points.end();
      it++ ) {

    if( maxX < ( *it )->getX() )
      maxX = ( *it )->getX();

    if( maxY < ( *it )->getY() )
      maxY = ( *it )->getY();
  }

  Point2d * max = new Point2d( maxX, maxY );

  return *max;
}

Point2d& Polygon::min() const {
  //initialize with 0,0
    float minX = 0, minY = 0;

    //run through all points and find the max coordinates.
    for( vector<Point2d *>::const_iterator it = points.begin(); it != points.end();
        it++ ) {

      if( minX > ( *it )->getX() )
        minX = ( *it )->getX();

      if( minY > ( *it )->getY() )
        minY = ( *it )->getY();
    }

    Point2d * min = new Point2d( minX, minY );

    return *min;
}


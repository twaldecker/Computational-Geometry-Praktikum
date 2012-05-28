#include "Polygon.h"

Polygon::Polygon():inner(0) {
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
  for( vector<Point2d *>::const_iterator it = points.begin();
      it != points.end(); it++ ) {
    /*to implement the module I used the (if)?then:else construct. Ugly but works. */
    area +=
        ( *it )->getY()
            * ( ( *( it == points.begin() ? points.end() - 1 : it - 1 ) )->getX()
                - ( *( it + 1 == points.end() ? points.begin() : it + 1 ) )->getX() );
  }
  area = abs( area / 2 );

  if(this->isInner()){
    area *= -1;
  }

  return area;
}

int Polygon::pip( Point2d& q ) const {
  //bestimme einen Punkt der Außerhalb des Polygons liegt.
  //Nehme die maximalen werte in x- und y- richtung und addiere (1,1)
  Point2d a = this->max() + Point2d( 10, 10 ); //p~ ausm skript

  //suche einen eckpunkt der nicht auf p-q~ liegt.
  vector<Point2d *>::const_iterator pit = points.begin();
  while( a.ccw( q, **pit ) == 0 ) {
    if( ++pit == points.end() ) {
      cerr << "Komisches polygon." << endl;
      //exit(34);
    }
  }
  //pit enthält nun pointer auf ecke.

  int s = 0; //s enthält die anzahl der Schnitte.
  float x = a.ccw( q, **pit ); //ccw-wert
  float lr = (x > 0) - (x < 0);
  //float lr = copysign( 1.0, a.ccw( q, **pit ) ); //erstes Vorzeichen von ccw

  for( vector<Point2d *>::const_iterator jit = pit + 1; jit != points.end();
      jit++ ) {
    x = a.ccw( q, **jit );
    float lrnew = (x > 0) - (x < 0);
    //float lrnew = copysign( 1.0, a.ccw( q, **jit ) );
    if( abs( lrnew - lr ) == 2 ) {
      lr = lrnew;
      if( ( ( *( jit - 1 ) )->ccw( **jit, a )
          * ( *( jit - 1 ) )->ccw( **jit, q ) ) <= 0 )
        s++;
    }
  }
  //long expression:
  if((s % 2) == 0) {
    return 0;
  } else {
    if(isInner())
      return -1;
    else
      return 1;
  }

  //short
  //return !( s % 2 == 0 );
}

Point2d& Polygon::max() const {
  //initialize with 0,0
  float maxX = 0, maxY = 0;

  //run through all points and find the max coordinates.
  for( vector<Point2d *>::const_iterator it = points.begin();
      it != points.end(); it++ ) {

    if( maxX < ( *it )->getX() )
      maxX = ( *it )->getX();

    if( maxY < ( *it )->getY() )
      maxY = ( *it )->getY();
  }

  Point2d * max = new Point2d( maxX, maxY );

  return *max;
}

Point2d& Polygon::min() const {
  //initialize with max values!
  Point2d h = this->max();
  float minX = h.getX(), minY = h.getY();

  //run through all points and find the max coordinates.
  for( vector<Point2d *>::const_iterator it = points.begin();
      it != points.end(); it++ ) {

    if( minX > ( *it )->getX() )
      minX = ( *it )->getX();

    if( minY > ( *it )->getY() )
      minY = ( *it )->getY();
  }

  Point2d * min = new Point2d( minX, minY );

  return *min;
}

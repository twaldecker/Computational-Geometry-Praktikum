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
float Polygon::area() {
  float area = 0;

  //Gaußsche Dreiecksformel
  //iterate over points
  for( vector<Point2d *>::iterator it = points.begin()+1;
      it != points.end(); it++ ) {
    area += (*it)->getY() * ( (*(it-1))->getX() - (*(it+1 == points.end() ? points.begin(): it+1))->getX() );
  }
  area = area / 2;
  return area;
}

bool Polygon::pip() const {
  return true;
}

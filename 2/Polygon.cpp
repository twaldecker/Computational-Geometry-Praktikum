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

float Polygon::area() const {
  return 0;
}

bool Polygon::pip() const {
  return true;
}

#include "ElTest.h"

ElTest::ElTest() {
  // TODO Auto-generated constructor stub

}

ElTest::~ElTest() {
  // TODO Auto-generated destructor stub
}

float ElTest::ccw( const Point2d p, const Point2d q, const Point2d r ) {
  return ( ( p.getX() * q.getY() - p.getY() * q.getX() )
      + ( q.getX() * r.getY() - q.getY() * r.getX() ) + ( p.getY() * r.getX() ) );
}

bool ElTest::intersect( const Line* l1, const Line* l2 ) {
  if( ( ccw( l1->getA(), l1->getB(), l2->getA() )
      * ccw( l1->getA(), l1->getB(), l2->getB() ) ) <= 0
      && ( ccw( l2->getA(), l2->getB(), l1->getA() )
          * ccw( l2->getA(), l2->getB(), l1->getB() ) ) <= 0 )
    return true;
  else
    return false;
}

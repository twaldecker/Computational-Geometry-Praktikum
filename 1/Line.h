#ifndef LINE_H_
#define LINE_H_

#include "Point2d.h"

class Line {
private:
  Point2d a, b;

public:
  Line( const Point2d a, const Point2d b );
  Line( const float ax, const float ay, const float bx, const float by );
  virtual ~Line();

  /**
   * get the first point
   */
  Point2d getA() const {
    return a;
  }

  /**
   * get the second point
   */
  Point2d getB() const {
    return b;
  }

  /**
   * calculate the ccw of this line and one other point
   */
  float ccw( const Point2d r ) const {
    return this->getA().ccw( this->getB(), r );
  }

  /**
   * calculate if this line intersects with the provided Line l
   */
  bool intersect( const Line* l ) const {
    if( ( this->ccw(l->getA()) * this->ccw(l->getB()) <= 0 )
        && ( l->ccw(this->getA()) * l->ccw(this->getB()) <= 0 ) )
      return true;
    else
      return false;
  }
};

#endif /* LINE_H_ */
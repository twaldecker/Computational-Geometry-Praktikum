#ifndef LINE_H_
#define LINE_H_

#include "Point2d.h"
#include <cfloat>
#include <iostream>

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
   * calculate the length of this line
   */
  float length() const {
    Point2d len = this->getA() - this->getB();
    return ( len.length() );
  }

  /**
   * calculate if this line intersects with the provided Line l
   */
  bool intersect( const Line* ) const;

  bool operator==( const Line& l ) {
    return ( ( this->getA() == l.getA() ) && ( this->getB() == l.getB() ) );
  }

  friend std::ostream& operator<<( std::ostream& out, const Line& l ) {
    out << l.getA() << " " << l.getB();
    return out;
  }

};

#endif /* LINE_H_ */

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
   * calculate the length of this line
   */
  float length() const {
    Point2d len = this->getA() - this->getB();
    return ( len.length() );
  }

  /**
   * calculate if this line intersects with the provided Line l
   */
  bool intersect( const Line* l ) const {

    float ccwta = this->ccw( l->getA() );
    float ccwtb = this->ccw( l->getB() );
    float ccwat = l->ccw( this->getA() );
    float ccwbt = l->ccw( this->getB() );

    /* check collinearity of the two lines */
    if( ccwta == 0 && ccwtb == 0 ) {
      const Line* p, *q;

      /* check for four identical points */
      if( this->length() == 0 && l->length() == 0 )
        return ( this->getA() == l->getA() );

      /* compare length of lines and assign pointers */
      if( this->length() < l->length() ) {
        p = l;
        q = this;
      }
      else {
        p = this;
        q = l;
      }
      /* lines are collinear -> calculate the lambda from parametric form */
      Point2d lambda1 = ( q->getA() - p->getA() ) / ( p->getB() - p->getA() );
      Point2d lambda2 = ( q->getB() - p->getA() ) / ( p->getB() - p->getA() );






      /* the two elements of lambda are identical because of collinearity */
      if( ( lambda1.getX() >= 0 && lambda1.getX() <= 1 )
          || ( lambda1.getY() >= 0 && lambda1.getY() <= 1 )
          || ( lambda2.getX() >= 0 && lambda2.getX() <= 1 )
          || ( lambda2.getY() >= 0 && lambda2.getY() <= 1 ) )
        return true;
      else
        return false;
    }

    /* lines are not collinear -> check for intersection and(!) contact */
    if( ( ( ccwta * ccwtb ) <= 0 ) && ( ( ccwat * ccwbt ) <= 0 ) )
      return true;
    return false;
  }
};

#endif /* LINE_H_ */

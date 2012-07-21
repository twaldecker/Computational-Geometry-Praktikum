#include "Line.h"

Line::Line( const Point2d a, const Point2d b ) :
    a( a ), b( b ), ykey( 0 ) {

}

Line::Line( const float ax, const float ay, const float bx, const float by ) :
    a( ax, ay ), b( bx, by ), ykey( 0 ) {

}

Line::~Line() {
  // TODO Auto-generated destructor stub
}

/**
 * calculate if this line intersects with the provided Line l
 * Point2d * intersection output of the intersection point
 */
bool Line::intersect( const Line* l, Point2d & intersection ) {
  const Line* p, *q;
  /* compare length of lines and assign pointers */
  if( this->length() < l->length() ) {
    p = l;
    q = this;
  }
  else {
    p = this;
    q = l;
  } /* p is now the line longer or the same length then q */

  float ccwpa = p->ccw( q->getA() );
  float ccwpb = p->ccw( q->getB() );
  float ccwqa = q->ccw( p->getA() );
  float ccwqb = q->ccw( p->getB() );

  /* check collinearity of the two lines */
  if( fabs( ccwpa ) <= FLT_EPSILON && fabs( ccwpb ) <= FLT_EPSILON ) { /* lines are collinear */
    return false; /* if they are collinear, just return false. */
  }

  /* lines are not collinear -> check for intersection or(!) contact */
  if( ( ( ccwpa * ccwpb ) <= FLT_EPSILON )
      && ( ( ccwqa * ccwqb ) <= FLT_EPSILON ) ) {

    //calculate the point
    float den = ( p->getA().getX() - p->getB().getX() )
        * ( q->getA().getY() - q->getB().getY() )
        - ( p->getA().getY() - p->getB().getY() )
            * ( q->getA().getX() - q->getB().getX() );

    if( fabs( den ) <= FLT_EPSILON )
      return false;

    float x = ( ( p->getA().getX() * p->getB().getY()
        - p->getA().getY() * p->getB().getX() )
        * ( q->getA().getX() - q->getB().getX() )
        - ( p->getA().getX() - p->getB().getX() )
            * ( q->getA().getX() * q->getB().getY()
                - q->getA().getY() * q->getB().getX() ) ) / den;

    float y = ( ( p->getA().getX() * p->getB().getY()
        - p->getA().getY() * p->getB().getX() )
        * ( q->getA().getY() - q->getB().getY() )
        - ( p->getA().getY() - p->getB().getY() )
            * ( q->getA().getX() * q->getB().getY()
                - q->getA().getY() * q->getB().getX() ) ) / den;
    intersection.set( x, y );

    return true;
  }

  return false;
}

#include "Line.h"


Line::Line( const Point2d a, const Point2d b ) :
    a( a ), b( b ) {

}

Line::Line( const float ax, const float ay, const float bx, const float by ) :
    a( ax, ay ), b( bx, by ) {

}

Line::~Line() {
  // TODO Auto-generated destructor stub
}

/**
 * calculate if this line intersects with the provided Line l
 * Point2d * intersection output of the intersection point
 */
bool Line::intersect( const Line* l, Point2d * intersection ) const {

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

  float ccwta = p->ccw( q->getA() );
  float ccwtb = p->ccw( q->getB() );
  float ccwat = q->ccw( p->getA() );
  float ccwbt = q->ccw( p->getB() );

  /* check collinearity of the two lines */
  if( fabs( ccwta ) <= FLT_EPSILON && fabs( ccwtb ) <= FLT_EPSILON ) { /* lines are collinear */
    return false; /* if they are collinear, just return false. */
  }

  /* lines are not collinear -> check for intersection or(!) contact */
  if( ( ( ccwta * ccwtb ) <= FLT_EPSILON ) && ( ( ccwat * ccwbt ) <= FLT_EPSILON ) )
  {
    //now calculate the lambda:
    Point2d lambda1 = ( q->getA() - p->getA() ) / ( p->getB() - p->getA() );

    //calculate the point from lambda:
    intersection = new Point2d ( ((p->getA().getX() * p->getB().getY() - p->getA().getY() *  p->getB().getX())*(q->getA().getX() - q->getB().getX())-(p->getA().getX() - p->getB().getX()) * (q->getA().getX() * q->getB().getY() - q->getA().getY() * q->getB().getX()) / (p->getA().getX() - p->getB().getX())*(q->getA().getY() - q->getB().getY()) - (p->getA().getY() - p->getB().getY()) * (q->getA().getX() - q->getB().getX()))
      ,
        ((p->getA().getX() * p->getB().getY() - p->getA().getY() * p->getB().getX()) * (q->getA().getY() - q->getB().getY()) - (p->getA().getY() - p->getB().getY()) * (q->getA().getX() * q->getB().getY() - q->getA().getY() * q->getB().getX()) / (p->getA().getX() - p->getB().getX()) * (q->getA().getY() - q->getB().getY()) - (p->getA().getY() - p->getB().getY()) * (q->getA().getX() - q->getB().getX()))
    );

    return true;
  }

  return false;
}

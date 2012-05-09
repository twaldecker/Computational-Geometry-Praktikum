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
 */
bool Line::intersect( const Line* l ) const {

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
  if( fabs(ccwta) <= FLT_EPSILON && fabs(ccwtb) <= FLT_EPSILON ) { /* lines are collinear */


    /* check for four identical points */
    if( p->length() == 0 && q->length() == 0 )
      return ( p->getA() == q->getA() );


    /* now we test if the start or endpoint from q is in p */
    Point2d lambda1 = ( q->getA() - p->getA() ) / ( p->getB() - p->getA() );
    Point2d lambda2 = ( q->getB() - p->getA() ) / ( p->getB() - p->getA() );

    /* we have to test both elements of lambda.
     * Maybe we divided through zero if the line was horizontal or vertical.
     * If one of the elements is between [0,1] of both lambdas we have a intersection.
     */
    if( ( lambda1.getX() >= 0 && lambda1.getX() <= 1 )
        || ( lambda1.getY() >= 0 && lambda1.getY() <= 1 )
        || ( lambda2.getX() >= 0 && lambda2.getX() <= 1 )
        || ( lambda2.getY() >= 0 && lambda2.getY() <= 1 ) )
      return true;
    else
      return false;
  }

  /* lines are not collinear -> check for intersection or(!) contact */
  if( ( ( ccwta * ccwtb ) <= FLT_EPSILON ) && ( ( ccwat * ccwbt ) <= FLT_EPSILON ) )
    return true;
  return false;
}

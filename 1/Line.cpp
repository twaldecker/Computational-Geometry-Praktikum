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


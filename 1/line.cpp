#include "line.h"

Line::Line( Point2d a, Point2d b ) :
    a( a ), b( b ) {

}

Line::Line( float ax, float ay, float bx, float by ) :
    a( ax, ay ), b( bx, by ) {

}

Line::~Line() {
  // TODO Auto-generated destructor stub
}


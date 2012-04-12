#ifndef LINE_H_
#define LINE_H_

#include "point2d.h"

class Line {
private:
  Point2d a, b;

public:
  Line( Point2d a, Point2d b );
  Line( float ax, float ay, float bx, float by );
  virtual ~Line();

  Point2d getA() const {
    return a;
  }
  Point2d getB() const {
    return b;
  }
};

#endif /* LINE_H_ */

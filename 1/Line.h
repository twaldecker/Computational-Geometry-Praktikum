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

  Point2d getA() const {
    return a;
  }
  Point2d getB() const {
    return b;
  }
};

#endif /* LINE_H_ */

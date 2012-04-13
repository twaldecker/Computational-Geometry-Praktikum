#ifndef ELTEST_H_
#define ELTEST_H_

#include "Point2d.h"
#include "Line.h"

class ElTest {
public:
  ElTest();
  virtual ~ElTest();

  float ccw( const Point2d p, const Point2d q, const Point2d r );
  bool intersect( const Line* l1, const Line* l2 );
};

#endif /* ELTEST_H_ */

#ifndef POLYGON_H_
#define POLYGON_H_

#include <vector>
#include "Point2d.h"

using namespace std;

class Polygon {

private:

  vector<Point2d *> points;

public:

  Polygon();
  virtual ~Polygon();

  vector<Point2d *> * getPoints() {
    return &points;
  }

  /**
   * add point to polygon
   */
  void addPoint( const float x, const float y );

  /**
   * calculate area of polygon
   */
  float area();

  /**
   * calculate area of polygon
   */
  bool pip() const;

  /**
   * Returns a Point2d containing the maximum of the
   * first coordinate and the max of the second coordinates
   */
  Point2d * max();

  /**
   * Returns a Point2d containing the miniumum of the
   * first coordinate and the minimum of the second coordinates.
   */
  Point2d * min();
};

#endif /* POLYGON_H_ */

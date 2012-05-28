#ifndef POLYGON_H_
#define POLYGON_H_

#include <vector>
#include <cmath>
#include "Point2d.h"

using namespace std;

class Polygon {

private:

  vector<Point2d *> points;
  bool inner; /*if set, polygon is inner polygon*/

public:

  Polygon();
  virtual ~Polygon();

  vector<Point2d *> * getPoints() {
    return &points;
  }

  void setInner() {
    this->inner = 1;
  }

  bool isInner() const {
    return inner;
  }


  /**
   * add point to polygon
   */
  void addPoint( const float x, const float y );

  /**
   * calculate area of polygon
   */
  float area() const;

  /**
   * calculate area of polygon
   * returns 0 if point is not in polygon,
   * returns 1 if point is in polygon and type is not inner
   * returns -1 if point is in polygon and type is inner
   */
  int pip(Point2d &) const;

  /**
   * Returns a Point2d containing the maximum of the
   * first coordinate and the max of the second coordinates
   */
  Point2d& max() const;

  /**
   * Returns a Point2d containing the miniumum of the
   * first coordinate and the minimum of the second coordinates.
   */
  Point2d& min() const;
};

#endif /* POLYGON_H_ */

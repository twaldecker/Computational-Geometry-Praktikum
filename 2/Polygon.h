#ifndef POLYGON_H_
#define POLYGON_H_

#include <string>
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
  float area() const;

  /**
   * calculate area of polygon
   */
  bool pip() const;
};

#endif /* POLYGON_H_ */

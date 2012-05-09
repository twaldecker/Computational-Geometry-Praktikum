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

  /**
   * calculate area of polynom
   */
  float area() const;

  /**
   * calculate area of polynom
   */
  bool pip() const;
};

#endif /* POLYGON_H_ */

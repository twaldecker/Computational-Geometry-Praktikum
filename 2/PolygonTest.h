#ifndef POLYGONTEST_H_
#define POLYGONTEST_H_

#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <string>
#include "Polygon.h"
#include "Point2d.h"

using namespace std;

class PolygonTest {

private:

  ifstream file;
  string filename;
  clock_t start, stop; /* timestamps */
  vector<Polygon *> polygons; /* a vector containing pointer to polygons */
  vector<Point2d *> points; /* a vector containing pointer to points2d */

  int open();

public:

  PolygonTest( string );
  virtual ~PolygonTest();

  void calculateAreas();
  void calculatePiP();
  void printResults();
  int parse();

};

#endif /* POLYGONTEST_H_ */

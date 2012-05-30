#ifndef FILEPARSER_H_
#define FILEPARSER_H_

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <ctime>
#include <cstdlib>
#include "Point2d.h"
#include "Line.h"

using namespace std;

class IntersectionTest {

private:

  ifstream file;
  string filename;
  clock_t start, stop; /* timestamps */
  long intersectionCount; /* count the intersections */
  vector<Line *> lines; /* a vector containing pointer to Lines */
  multimap<float, Point2d> xStruct; /* xStruct to Store events depending on x-coordinates */
  multimap<float, Line> yStruct; /* yStruct to Store Lines depending on y-coordinates */

  int open();

public:

  IntersectionTest( string );
  virtual ~IntersectionTest();

  void calculateIntersections();
  void printResults();
  int parse();

  vector<Line *> * getLines() {
    return &lines;
  }
  ;
  float getTime() {
    return (float) ( stop - start ) / CLOCKS_PER_SEC;
  }
  ;
};

#endif /* FILEPARSER_H_ */

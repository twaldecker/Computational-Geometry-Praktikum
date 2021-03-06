#ifndef SLINTERSECTIONTEST_H_
#define SLINTERSECTIONTEST_H_

#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <list>
#include <ctime>
#include <cstdlib>
#include "Point2d.h"
#include "Line.h"
#include "SLEvent.h"

using namespace std;

class SLIntersectionTest {

private:

  ifstream file;
  string filename;
  clock_t start, stop; /* timestamps */
  long lineCount; /* count the lines and intersections */
  multimap<float, SLEvent *> xStruct; /* xStruct to Store events depending on x-coordinates */
  multimap<float, Line *> yStruct; /* yStruct to Store Lines depending on y-coordinates */
  set<Point2d> intersections;

  void open();
  void handleEvent( const SLEvent& );
  bool intersects( Line *, Line *);
  bool yFind(const float, const Line * , multimap<float, Line *>::iterator * );
  multimap<float, Line*>::iterator  insert(const float, Line * );
  void fixNeighborsInYStruct(multimap<float, Line *>::iterator, Point2d, float, const SLEvent& );


public:

  SLIntersectionTest( string );
  virtual ~SLIntersectionTest();

  void calculateIntersections();
  void printResults();
  void parse();

  float getTime() const {
    return (float) ( stop - start ) / CLOCKS_PER_SEC;
  }
  ;
};

#endif /* SLINTERSECTIONTEST_H_ */

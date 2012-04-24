#ifndef FILEPARSER_H_
#define FILEPARSER_H_

#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include "Line.h"

using namespace std;

class IntersectionTest {

private:

  ifstream file;
  string filename;
  clock_t start, stop; /* timestamps */
  long intersectionCount; /* count the intersections */
  vector<Line *> lines; /* a vector containing pointer to Lines */

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

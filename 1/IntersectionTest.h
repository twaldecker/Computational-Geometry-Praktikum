/*
 * FileParser.h
 *
 *  Created on: Apr 14, 2012
 *      Author: thomas
 */

#ifndef FILEPARSER_H_
#define FILEPARSER_H_

#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include "Line.h"

using namespace std;

class IntersectionTest {

private:
  ifstream file;
  string filename;
  vector<Line *> lines; /* a vector containing pointer to Lines */
  long intersectionCount; /* count the intersections */
  clock_t start, stop;

  int open();

public:
  IntersectionTest(string);
  virtual ~IntersectionTest();

  void calculateIntersections();
  vector<Line *> * getLines() { return &lines; };
  int parse();

  void printResults() {
    cout << "Number of Lines: " << lines.size() << "\n"
         << intersectionCount << " intersections\n calculated in "
         << getTime() << " seconds";

  };

  float getTime(){
    return stop-start / CLOCKS_PER_SEC;
  };
};

#endif /* FILEPARSER_H_ */

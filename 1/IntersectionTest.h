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
#include "Line.h"

using namespace std;

class IntersectionTest {

private:
  ifstream file;
  string filename;
  vector<Line *> lines; /* a vector containing pointer to Lines */
  int open();

public:
  IntersectionTest(string);
  virtual ~IntersectionTest();
  vector<Line *> * getLines() { return &lines; };
  int parse();
};

#endif /* FILEPARSER_H_ */

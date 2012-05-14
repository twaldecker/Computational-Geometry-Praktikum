#ifndef POLYGONTEST_H_
#define POLYGONTEST_H_

#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <string>
#include "State.h"
#include "City.h"

using namespace std;

class PolygonTest {

private:

  ifstream file;
  string filename;
  clock_t start, stop; /* timestamps */
  vector<State *> states; /* a vector containing pointer to States */
  vector<City *> cities; /* a vecotr containing pointer to Cities */

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

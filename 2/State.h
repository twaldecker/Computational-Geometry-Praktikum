#ifndef STATE_H_
#define STATE_H_

#include <string>
#include <vector>
#include <iostream>
#include "Polygon.h"
#include "City.h"

using namespace std;

class State {

private:

  string id;
  vector<Polygon *> polygons;

public:

  State( string id );
  virtual ~State();

  string getID() const {
    return id;
  }

  vector<Polygon *> * getPolygons() {
    return &polygons;
  }

  float area() const;

  bool cityInside( City * ) const;

  /**
   * add polygon to state
   */
  void addPolygon( Polygon * const poly );

  friend ostream& operator<<( ostream& out, const State& s ) {
    out << s.getID();
    return out;
  }

};

#endif /* STATE_H_ */

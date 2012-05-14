#ifndef STATE_H_
#define STATE_H_

#include <string>
#include "Polygon.h"

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

  /**
   * add polygon to state
   */
  void addPolygon( Polygon * const poly );

};

#endif /* STATE_H_ */

#ifndef STATE_H_
#define STATE_H_

#include "Polygon.h"

class State {

private:

  string id;
  vector<Polygon *> polygons;

public:

  State();
  virtual ~State();

  void setID( const string id ) {
    this->id = id;
  }

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

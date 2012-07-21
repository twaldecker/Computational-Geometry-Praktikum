#ifndef SLEVENT_H_
#define SLEVENT_H_

#include <vector>
#include "Point2d.h"
#include "Line.h"

using namespace std;

#define TYPE int
#define BEGIN 1
#define END 2
#define INTERSECTION 3

class SLEvent {

private:

  TYPE type;
  Point2d coords;

  vector<Line *> lines;

public:

  SLEvent( const TYPE&, const Point2d&, const vector<Line *>& );
  SLEvent( const TYPE&, const Point2d&, Line&, Line& );
  SLEvent( const TYPE&, const Point2d&, Line& );

  virtual ~SLEvent();

  TYPE getType() const {
    return type;
  }

  /**
   * returns the coordinates of the SLEvent.
   */
  Point2d getCoords() const {
    return coords;
  }

  /**
   * Returns the Vector of the (intersecting-)Lines
   */
  vector<Line *> getLines() const {
    return lines;
  }

  /**
   * returns a pointer to the first Line.
   */
  Line * getLine() const {
    return lines[0];
  }

};

#endif /* SLEVENT_H_ */

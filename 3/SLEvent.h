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
  Point2d coord;
  vector<Line *> lines;

public:

  SLEvent( const TYPE, const Point2d& );
  virtual ~SLEvent();

  TYPE getType() const {
    return type;
  }
  ;

};

#endif /* SLEVENT_H_ */

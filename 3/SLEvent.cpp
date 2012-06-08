#include "SLEvent.h"

SLEvent::SLEvent( const TYPE& type, const Point2d& coords,
    const vector<Line *>& lines ) :
    type( type ), coords( coords ), lines( lines ) {

}

SLEvent::~SLEvent() {
  // TODO Auto-generated destructor stub
}


#include "SLEvent.h"

SLEvent::SLEvent( const TYPE& type, const Point2d& coords,
    const vector<Line *>& lines ) :
    type( type ), coords( coords ), lines( lines ) {

}

SLEvent::SLEvent( const int& t, const Point2d& p,  Line& l ): type(t), coords(p) {
  lines.push_back( &l );
}

SLEvent::SLEvent( const int& t, const Point2d& p,  Line& l1, Line& l2): type(t), coords(p) {
  lines.push_back( &l1 );
  lines.push_back( &l2 );
}

SLEvent::~SLEvent() {
  // TODO Auto-generated destructor stub
}


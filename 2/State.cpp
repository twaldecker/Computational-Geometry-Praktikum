#include "State.h"

State::State() {
  // TODO Auto-generated constructor stub

}

State::~State() {
  // TODO Auto-generated destructor stub
}

void State::addPolygon(  Polygon * const poly ) {
  polygons.push_back( poly );
}

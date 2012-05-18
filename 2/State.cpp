#include "State.h"

State::State( string id ) :
    id( id ) {
  // TODO Auto-generated constructor stub

}

State::~State() {
  // TODO Auto-generated destructor stub
}

float State::area() {
  float area = 0;
  for( vector<Polygon *>::iterator polyit = polygons.begin();
          polyit != this->polygons.end(); polyit++ ) {

        area += ( *polyit )->area();
  }
  cout << "Staat: " << id << " Area: " << area << endl;
  return area;
}

bool State::pip() const {
  return true;
}

void State::addPolygon( Polygon * const poly ) {
  polygons.push_back( poly );
}

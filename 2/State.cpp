#include "State.h"

State::State( string id ) :
    id( id ) {
  // TODO Auto-generated constructor stub

}

State::~State() {
  // TODO Auto-generated destructor stub
}

float State::area() const {
  float area = 0;
  for( vector<Polygon *>::const_iterator polyit = polygons.begin();
      polyit != this->polygons.end(); polyit++ ) {

    area += ( *polyit )->area();
  }
  cout << "Staat: " << id << " Area: " << area << endl;
  return area;
}

bool State::cityInside(City * c) const {
  for( vector<Polygon *>::const_iterator polyit = polygons.begin();
      polyit != this->polygons.end(); polyit++ ) {

    if( ( *polyit )->pip() ) /* return true if point is in one polygon */
      return true;
  }
  return false; /*point is in no polygon of the state*/
}

void State::addPolygon( Polygon * const poly ) {
  polygons.push_back( poly );
}

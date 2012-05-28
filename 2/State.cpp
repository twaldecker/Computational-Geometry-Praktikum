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
      polyit != polygons.end(); polyit++ ) {

    area += ( *polyit )->area();
  }
  /* area multiplicated with a scale-factor */
  cout << "Staat: " << id << " Area: " << area * 1.17531998474 << endl;
  return area;
}

int State::cityInside(City * c) const {
  int count = 0;
  for( vector<Polygon *>::const_iterator polyit = polygons.begin();
      polyit != polygons.end(); polyit++ ) {

    count += ( *polyit )->pip(c->getCoord()); //need to check all polygons of state. see Polygon::pip for more info.
  }


  return count; /*point is in no polygon of the state*/
}

void State::addPolygon( Polygon * const poly ) {
  polygons.push_back( poly );
}

#include "PolygonTest.h"

PolygonTest::PolygonTest( string filename ) :
    filename( filename ) {
}

PolygonTest::~PolygonTest() {
  file.close();
}

int PolygonTest::open() {

  file.open( filename.c_str(), ios::in );

  if( !file.is_open() ) {
    cerr << "File " << filename << " not found" << endl;
    exit( 1 );
  }
  return 0;
}

void PolygonTest::calculateAreas() {

}

void PolygonTest::calculatePiP() {

}

void PolygonTest::printResults() {

}

int PolygonTest::parse() {

  string strline; /* one line of the file */
  string id;
  float abs[2];
  float unk[2];
  open(); // first open the file, then read
  while( getline( file, strline ) ) {
    /* search for path */
    if( strline.find( "path" ) != string::npos ) {
      Polygon * tmpin = new Polygon();
      /* get id */
      size_t pos1 = strline.find( "id" );
      if( pos1 != string::npos ) {
        size_t pos2 = strline.find( " ", pos1 + 1 );
        id = strline.substr( pos1 + 4, pos2 - ( pos1 + 4 ) - 1 );
        tmpin->setID( id );
        cout << "Polygon \"" << tmpin->getID() << "\" with ";
      } /* else part to check further lines for id */
      while( getline( file, strline ) ) {
        if( strline.find( "/>" ) != string::npos ) {
          polygons.push_back( tmpin );
          cout << tmpin->getPoints()->size() << " points created" << endl;
          break;
        }
        else {
          string ctype = strline.substr( 0, 1 );
          const char * type = ctype.c_str();
          string cval = strline.substr( 1 );
          const char * val = cval.c_str();
          sscanf( val, "%f,%f", &unk[0], &unk[1] );
          switch( *type ) {
          case ( 'Z' ):
          case ( 'z' ):
            break;
          case ( 'M' ):
          case ( 'L' ):
            abs[0] = unk[0];
            abs[1] = unk[1];
            tmpin->addPoint( abs[0], abs[1] );
            break;
          case ( 'm' ):
          case ( 'l' ):
            abs[0] += unk[0];
            abs[1] += unk[1];
            tmpin->addPoint( abs[0], abs[1] );
            break;
          default:
            break;
          }
        }
      }
    }
  }
  return 0;
}

#include "IntersectionTest.h"

IntersectionTest::IntersectionTest( string filename ) :
    filename( filename ), intersectionCount(0) {
}

/**
 *  open file and scream if I can not open it
 */
int IntersectionTest::open() {

  file.open( filename.c_str(), ios::in );

  if( !file.is_open() ) {
    cerr << "File " << filename << " not found\n";
    exit(1);
  }
  return 0;
}

void IntersectionTest::calculateIntersections() {
  /* the file is now processed, the values are in the vector. Now its time to calculate and start the clock */
  /* Note: the outer loop loops over all entries in the vector.
   * The inner loop loops over outerit+1.
   * So we do test two lines only one time with each other and not with itself.
   */
  start = clock();
  /* intersection calculation with two iterator-loops */
  for( vector<Line *>::iterator outerit = lines.begin(); outerit != lines.end();
      outerit++ ) {
    for( vector<Line *>::iterator innerit = outerit + 1;
        innerit != lines.end(); innerit++ ) {
      if( (*outerit)->intersect(*innerit) )
        intersectionCount++;
    }
  }
  /* stop time */
  stop = clock();
}

void IntersectionTest::printResults() {
  cout << "Number of Lines: " << lines.size() << "\n"
       << intersectionCount << " intersections\n calculated in "
       << getTime() << " seconds";

};

/* process the file line by line */
int IntersectionTest::parse() {
  open(); // first open the file, then read
  while( !file.eof() ) {
    /* read line, parse float values and store in temporary array */
    float a[4]; /* a temporary array to store the values */
    string strline; /* one line of the file */

    getline( file, strline );
    sscanf( strline.c_str(), "%f %f %f %f", &a[0], &a[1], &a[2], &a[3] );

    /* create a new Line object and store it in the vector */
    Line* tmpin = new Line( a[0], a[1], a[2], a[3] );
    lines.push_back( tmpin );

#if DEBUG /* output */
    cout << "Input:  " << a[0] << " " << a[1] << " " << a[2] << " " << a[3]
    << endl;
    Line* tmpout = lines.back();
    cout << "Vector: " << tmpout->getA().getX() << " "
    << tmpout->getA().getY() << " " << tmpout->getB().getX() << " "
    << tmpout->getB().getY() << " " << endl;
#endif /* DEBUG */

  }
  return 0;
}

IntersectionTest::~IntersectionTest() {
  file.close();
  // TODO Auto-generated destructor stub
}


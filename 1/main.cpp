
#include <ctime>
using namespace std;

#include "Line.h"
#include "FileParser.h"

#define DEBUG 1

int main( void ) {

  FileParser * p = new FileParser("strecken/Strecken_Test.dat");
  p->parse();
  vector<Line *> * lines = p->getLines();


  long counter = 0;
  clock_t start, stop;

  /* the file is now processed, the values are in the vector. Now its time to calculate and start the clock */
  /* Note: the outer loop loops over all entries in the vector.
   * The inner loop loops over outerit+1.
   * So we do test two lines only one time with each other and not with itself.
   */
  start = clock();
  /* intersection calculation with two iterator-loops */
  for( vector<Line *>::iterator outerit = lines->begin(); outerit != lines->end();
      outerit++ ) {
    for( vector<Line *>::iterator innerit = outerit + 1;
        innerit != lines->end(); innerit++ ) {
      if( (*outerit)->intersect(*innerit) )
        counter++;
    }
  }
  /* stop time */
  stop = clock();

  /* output result */
  cout << counter << " intersections calculated in "
      << double( stop - start ) / CLOCKS_PER_SEC << " seconds"; /* counter - 1000 ?! */

  return 0;
}

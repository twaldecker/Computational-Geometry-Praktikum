#ifndef CLI_H_
#define CLI_H_

#include <cstdlib>
#include <getopt.h>
#include <iostream>

using namespace std;

class Cli {

private:

  string filename;

  void help();

public:

  Cli( int argc, char *argv[] );
  virtual ~Cli();

  string getFilename() {
    return filename;
  }
  ;
};

#endif /* CLI_H_ */

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#include "line.h"

int main(void) {

	vector<line> lines;
	string sline;
	float a[4];
	ifstream myfile("strecken/Strecken_1000.dat");
	if (myfile.is_open()) {
		while (myfile.good()) {
			getline(myfile, sline);

			sscanf(sline.c_str(), "%f %f %f %f", &a[0], &a[1], &a[2], &a[3]);
			line* tmp = new line(a[0], a[1], a[2], a[3]);
			//TODO: aktuellen Wert in Vector schreiben
			lines.push_back(*tmp);
			delete tmp;
			//cout << "zahlen: " << a[0] << a[1] << a[2] << a[3] << endl;

		}
		myfile.close();
	}
	else
		cout << "Unable to open file";

	return 0;
}


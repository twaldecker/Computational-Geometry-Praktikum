#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main(void) {

	vector<float[4]> points;
	string line;
	float a[4];
	ifstream myfile("strecken/Strecken_1000.dat");
	if (myfile.is_open()) {
		while (myfile.good()) {
			getline(myfile, line);

			sscanf(line.c_str(), "%f %f %f %f", &a[0], &a[1], &a[2], &a[3]);

			cout << "zahlen: " << a[0] << a[1] << a[2] << a[3] << endl;

		}
		myfile.close();
	}
	else
		cout << "Unable to open file";

	return 0;
}


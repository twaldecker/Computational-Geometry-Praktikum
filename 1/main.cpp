#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main(void) {

	vector<float[4]> points;
	string line;
	ifstream myfile("strecken/Strecken_1000.dat");
	if (myfile.is_open()) {
		while (myfile.good()) {
			getline(myfile, line);
			cout << line << endl;
		}
		myfile.close();
	}
	else
		cout << "Unable to open file";

	return 0;
}


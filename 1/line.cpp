#include "line.h"

line::line(point2d a, point2d b):a(a), b(b) {

}

line::line(float ax, float ay, float bx, float by):a(ax, ay),b(bx, by) {

}

line::~line() {
	// TODO Auto-generated destructor stub
}


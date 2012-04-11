#ifndef LINE_H_
#define LINE_H_

#include "point2d.h"

class line {
private:
	point2d a,b;

public:
	line(point2d a, point2d b);
	line(float ax, float ay, float bx, float by);
	virtual ~line();
};

#endif /* LINE_H_ */

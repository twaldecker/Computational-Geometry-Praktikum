#ifndef POINT2D_H_
#define POINT2D_H_

class point2d {
private:
	float x;
	float y;
public:
	point2d(float x = 0, float y = 0);
	virtual ~point2d();
	float getX(){return x;}
	float getY(){return y;}
};

#endif /* POINT2D_H_ */

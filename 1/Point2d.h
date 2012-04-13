#ifndef POINT2D_H_
#define POINT2D_H_

class Point2d {
private:
  float x;
  float y;
public:
  Point2d( const float x = 0, const float y = 0 );
  virtual ~Point2d();

  float getX() const {
    return x;
  }
  float getY() const {
    return y;
  }
};

#endif /* POINT2D_H_ */

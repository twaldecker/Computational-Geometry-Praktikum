#ifndef POINT2D_H_
#define POINT2D_H_

class Point2d {
private:
  float x;
  float y;
public:
  Point2d( const float x = 0, const float y = 0 );
  virtual ~Point2d();

  /**
   * get the first coordinate
   */
  float getX() const {
    return x;
  }
  /**
   * get the second coordinate
   */
  float getY() const {
    return y;
  }

  /**
   * calculate the ccw with this point and two more Point2d q and r
   */
  float ccw( const Point2d q, const Point2d r ) {
    return ( ( this->getX() * q.getY() - this->getY() * q.getX() )
        + ( q.getX() * r.getY() - q.getY() * r.getX() )
        + ( this->getY() * r.getX() ) );
  }

};

#endif /* POINT2D_H_ */

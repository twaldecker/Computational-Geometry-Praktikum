#ifndef POINT2D_H_
#define POINT2D_H_

#include <cmath>
#include<iostream>

using namespace std;

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
   * calculate the zero-vector of this point
   */
  float length() {
    return ( sqrt( this->getX() * this->getX() + this->getY() * this->getY() ) );
  }

  /**
   * calculate the ccw with this point and two more Point2d q and r
   */
  float ccw( const Point2d q, const Point2d r ) {
    return ( ( this->getX() * q.getY() - this->getY() * q.getX() )
        + ( q.getX() * r.getY() - q.getY() * r.getX() )
        + ( this->getY() * r.getX() - this->getX() * r.getY() ) );
  }

  Point2d operator-( const Point2d& q ) {
    return Point2d( this->getX() - q.getX(), this->getY() - q.getY() );
  }

  Point2d operator+( const Point2d& q) {
    return Point2d( this->getX() + q.getX(), this->getY() + q.getY() );
  }

  Point2d operator/( const Point2d& q ) {
    return Point2d( this->getX() / q.getX(), this->getY() / q.getY() );
  }

  bool operator==( const Point2d& q ) {
    return ( ( this->getX() == q.getX() ) && ( this->getY() == q.getY() ) );
  }

  friend ostream& operator<<(ostream& out, const Point2d& p)
  {
      out << "(" << p.getX() << ", " << p.getY() << ")";
      return out;
  }

};

#endif /* POINT2D_H_ */

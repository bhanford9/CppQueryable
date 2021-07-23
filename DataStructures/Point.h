#ifndef CPPQUERYABLE_DATASTRUCTURES_POINT_H
#define CPPQUERYABLE_DATASTRUCTURES_POINT_H

class Point
{
public:
  double X;
  double Y;

  Point()
  {
    this->X = 0;
    this->Y = 0;
  }

  Point(double x, double y)
  {
    this->X = x;
    this->Y = y;
  }

  Point & operator+=(const Point & other)
  {
    this->X += other.X;
    this->Y += other.Y;
    return *this;
  }

  bool operator<(const Point & other) const
  {
    return this->X < other.X;
  }
};

#endif

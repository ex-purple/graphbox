#include <grbx/point.h>

GrBx::Point::Point (double _x, double _y)
    : x (_x),
      y (_y)
{
    
}

double GrBx::Point::get_x () const
{
    return x;
}

double GrBx::Point::get_y () const
{
    return y;
}

void GrBx::Point::set_x (double _x)
{
    x = _x;
}

void GrBx::Point::set_y (double _y)
{
    y = _y;
}

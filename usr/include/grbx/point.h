#ifndef _GRBX_POINT_H_
#define _GRBX_POINT_H_

namespace GrBx
{
    class Point
    {
	public:
	Point (double _x = 0, double _y = 0);
	
	public:
	double get_x () const;
	double get_y () const;
	void set_x (double _x);
	void set_y (double _y);
	
	private:
	double x, y;
    };
}

#endif //_GRBX_POINT_H_

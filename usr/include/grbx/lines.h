#ifndef _GRBX_LINES_H_
#define _GRBX_LINES_H_

#include "graph.h"

namespace GrBx
{
    class Lines : public GrBx::Graph
    {
	public:
	virtual ~Lines ();
	
	public:
	static Glib::RefPtr<Lines> create ();
	static Glib::RefPtr<Lines> create (const Glib::ArrayHandle<GrBx::Point> &_points);
	virtual void draw (const Cairo::RefPtr<Cairo::Context> &_cr, double _sx, double _sy);
	
	private:
	Lines ();
	Lines (const GrBx::Points &_points);
    };
}

#endif //_GRBX_LINES_H_

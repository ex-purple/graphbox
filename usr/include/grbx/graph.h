#ifndef _GRBX_GRAPH_H_
#define _GRBX_GRAPH_H_

#include "point.h"

#include <glibmm/object.h>
#include <glibmm/arrayhandle.h>
#include <gdkmm/color.h>
#include <cairomm/context.h>

namespace GrBx
{
    typedef std::vector<GrBx::Point> Points;
    class Graph : public Glib::Object
    {
	public:
	virtual ~Graph () = 0;
	
	public:
	virtual void draw (const Cairo::RefPtr<Cairo::Context> &_cr, double _sx, double _sy) = 0;
	bool get_visible () const;
	const GrBx::Points& get_points () const;
	const Gdk::Color& get_color () const;
	void set_visible (bool _visible);	
	GrBx::Points& get_points ();
	void set_points (const Glib::ArrayHandle<GrBx::Point> &_points);
	void set_color (const Gdk::Color &_color);
	void calculate_bounds (double &_x1, double &_y1, double &_x2, double &_y2);
	sigc::signal<void> signal_visible_changed ();

	protected:
	Graph ();
	Graph (const GrBx::Points &_points);
	
	private:
	bool visible;
	GrBx::Points points;
	Gdk::Color color;
	sigc::signal<void> sig_visible_changed;
    };
}

#endif //_GRBX_GRAPH_H_

#include <grbx/lines.h>

GrBx::Lines::~Lines ()
{

}

Glib::RefPtr<GrBx::Lines> GrBx::Lines::create ()
{
    return Glib::RefPtr<GrBx::Lines> (new GrBx::Lines);
}

Glib::RefPtr<GrBx::Lines> GrBx::Lines::create (const Glib::ArrayHandle<GrBx::Point> &_points)
{
    GrBx::Points points;
    std::copy (_points.begin (), _points.end (), std::back_inserter (points));
    return Glib::RefPtr<GrBx::Lines> (new GrBx::Lines (points));
}

void GrBx::Lines::draw (const Cairo::RefPtr<Cairo::Context> &_cr, double _sx, double _sy)
{
    const GrBx::Points points = get_points ();
    if (points.size () > 1)
    {
	const Gdk::Color color = get_color ();
	_cr->set_source_rgb (color.get_red_p (), color.get_green_p (), color.get_blue_p ());
	_cr->move_to (points [0].get_x () * _sx, points [0].get_y () * _sy);
	for (GrBx::Points::const_iterator itr = points.begin () + 1; itr != points.end (); ++itr) _cr->line_to (itr->get_x () * _sx, itr->get_y () * _sy);
	_cr->stroke ();
    }
}

GrBx::Lines::Lines ()
    : Glib::ObjectBase (typeid (GrBx::Lines))
{

}

GrBx::Lines::Lines (const GrBx::Points &_points)
    : Glib::ObjectBase (typeid (GrBx::Lines)),
      GrBx::Graph (_points)
{

}

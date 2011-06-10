#include <grbx/graph.h>

static bool find_x (const GrBx::Point &_point1, const GrBx::Point &_point2);
static bool find_y (const GrBx::Point &_point1, const GrBx::Point &_point2);

GrBx::Graph::~Graph ()
{

}

GrBx::Graph::Graph ()
    : visible (true)
{

}

GrBx::Graph::Graph (const GrBx::Points &_points)
    : visible (true),
      points (_points)
{

}

bool GrBx::Graph::get_visible () const
{
    return visible;
}

const GrBx::Points& GrBx::Graph::get_points () const
{
    return points;
}

const Gdk::Color& GrBx::Graph::get_color () const
{
    return color;
}

void GrBx::Graph::set_visible (bool _visible)
{
    visible = _visible;
    sig_visible_changed.emit ();
}

GrBx::Points& GrBx::Graph::get_points ()
{
    return points;
}

void GrBx::Graph::set_points (const Glib::ArrayHandle<GrBx::Point> &_points)
{
    points = _points;
}

void GrBx::Graph::set_color (const Gdk::Color &_color)
{
    color = _color;
}

void GrBx::Graph::calculate_bounds (double &_x1, double &_y1, double &_x2, double &_y2)
{
    _x1 = std::min_element (points.begin (), points.end (), find_x)->get_x ();
    _y1 = std::min_element (points.begin (), points.end (), find_y)->get_y ();
    _x2 = std::max_element (points.begin (), points.end (), find_x)->get_x ();
    _y2 = std::max_element (points.begin (), points.end (), find_y)->get_y ();
}

sigc::signal<void> GrBx::Graph::signal_visible_changed ()
{
    return sig_visible_changed;
}

bool find_x (const GrBx::Point &_point1, const GrBx::Point &_point2)
{
    return _point1.get_x () < _point2.get_x ();
}

bool find_y (const GrBx::Point &_point1, const GrBx::Point &_point2)
{
    return _point1.get_y () < _point2.get_y ();
}

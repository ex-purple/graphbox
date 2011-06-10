#include <grbx/vaxis.h>

#include <iomanip>

GrBx::VAxis::VAxis (GrBx::Area &_area)
    : GrBx::Axis (_area, _area.get_vadjustment ())
{

}

GrBx::VAxis::~VAxis ()
{

}

void GrBx::VAxis::on_size_request (Gtk::Requisition *_requisition)
{
    _requisition->width = 40;
    _requisition->height = -1;
}
	
bool GrBx::VAxis::on_expose_event (GdkEventExpose *_expose)
{
    GrBx::Axis::on_expose_event (_expose);
    if (_expose) draw_dial ();
    return true;
}

bool GrBx::VAxis::on_area_motion_notify_event (GdkEventMotion *_motion)
{
    if (_motion) set_cursor_pos (_motion->y);
    return false;
}

void GrBx::VAxis::draw_dial ()
{
    if (window && is_drawable ())
    {
	const Gtk::Adjustment &adjustment = get_adjustment ();
	Cairo::RefPtr<Cairo::Context> cr = window->create_cairo_context ();
	cr->set_font_face (Cairo::ToyFontFace::create("Sans", Cairo::FONT_SLANT_NORMAL, Cairo::FONT_WEIGHT_NORMAL));
	cr->set_font_size (10);
	Cairo::Matrix matrix (-1, 0, 0, -1, get_width (), get_height ());
	cr->transform (matrix);
	    
	for (double i = 0; i < get_height (); i += get_step ())
	{
	    cr->move_to (0, i);
	    cr->line_to (10, i);
	    cr->stroke ();
	
	    std::stringstream ss;
	    ss << std::setprecision (1) << std::fixed << convert_position_to_value (i) + adjustment.get_value () / adjustment.get_step_increment ();
	    cr->move_to (30, i);
	    cr->rotate_degrees (180);
	    cr->show_text (ss.str ());
	}
	update_pixbuf ();
    }
}

void GrBx::VAxis::set_cursor_pos (double _pos)
{
    GrBx::Axis::set_cursor_pos (_pos);
    if (window && pixbuf)
    {
	Gdk::Point points [3] = {Gdk::Point (0, _pos), Gdk::Point (15, _pos + 5), Gdk::Point (15, _pos - 5)};
	Cairo::RefPtr<Cairo::Context> cr = window->create_cairo_context ();
	Cairo::Matrix matrix (-1, 0, 0, 1, get_width (), 0);
	cr->transform (matrix);
	cr->move_to (points [0].get_x (), points [0].get_y ());
	cr->line_to (points [1].get_x (), points [1].get_y ());
	cr->line_to (points [2].get_x (), points [2].get_y ());
	cr->line_to (points [0].get_x (), points [0].get_y ());
	cr->fill ();
    }
}

double GrBx::VAxis::convert_position_to_value (double _pos)
{
    return (_pos * get_adjustment ().get_page_size () / get_height () / get_adjustment ().get_step_increment ());
}

#include <grbx/haxis.h>

#include <iomanip>

GrBx::HAxis::HAxis (GrBx::Area &_area)
    : GrBx::Axis (_area, _area.get_hadjustment ())
{

}

GrBx::HAxis::~HAxis ()
{

}

void GrBx::HAxis::on_size_request (Gtk::Requisition *_requisition)
{
    _requisition->width = -1;
    _requisition->height = 40;
}

bool GrBx::HAxis::on_expose_event (GdkEventExpose *_expose)
{
    GrBx::Axis::on_expose_event (_expose);
    if (_expose) draw_dial ();
    return true;
}

bool GrBx::HAxis::on_area_motion_notify_event (GdkEventMotion *_motion)
{
    if (_motion) set_cursor_pos (_motion->x);
    return false;
}

void GrBx::HAxis::draw_dial ()
{
    if (window && is_drawable ())
    {
	Cairo::RefPtr<Cairo::Context> cr = window->create_cairo_context ();
	cr->set_font_face (Cairo::ToyFontFace::create("Sans", Cairo::FONT_SLANT_NORMAL, Cairo::FONT_WEIGHT_NORMAL));
	cr->set_font_size (10);
	for (double i = 0; i < get_width (); i += get_step ())
	{
	    cr->move_to (i, 0);
	    cr->line_to (i, 10);
	    cr->stroke ();

	    std::stringstream ss;
	    ss << std::setprecision (1) << std::fixed << (convert_position_to_value (i) + get_adjustment ().get_value () / get_adjustment ().get_step_increment ());
	    cr->move_to (i, 15);
	    cr->show_text (ss.str ());
	}
	update_pixbuf ();
    }
}

void GrBx::HAxis::set_cursor_pos (double _pos)
{
    GrBx::Axis::set_cursor_pos (_pos);
    if (window && pixbuf)
    {
	Gdk::Point points [3] = {Gdk::Point (_pos, 0), Gdk::Point (_pos + 5, 15), Gdk::Point (_pos - 5, 15)};
	Cairo::RefPtr<Cairo::Context> cr = window->create_cairo_context ();
	cr->move_to (points [0].get_x (), points [0].get_y ());
	cr->line_to (points [1].get_x (), points [1].get_y ());
	cr->line_to (points [2].get_x (), points [2].get_y ());
	cr->line_to (points [0].get_x (), points [0].get_y ());
	cr->fill ();
    }
}

double GrBx::HAxis::convert_position_to_value (double _pos)
{
    return (_pos * get_adjustment ().get_page_size () / get_width () / get_adjustment ().get_step_increment ());
}

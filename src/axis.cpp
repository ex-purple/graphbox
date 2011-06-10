#include <grbx/axis.h>

GrBx::Axis::Axis (GrBx::Area &_area, Gtk::Adjustment &_adjustment)
    : area (_area),
      adjustment (_adjustment),
      step (1)
{
    area.signal_motion_notify_event ().connect (sigc::mem_fun (*this, &GrBx::Axis::on_area_motion_notify_event));
    adjustment.signal_changed ().connect (sigc::mem_fun (*this, &GrBx::Axis::on_adjustment_changed));
    adjustment.signal_value_changed ().connect (sigc::mem_fun (*this, &GrBx::Axis::on_adjustment_changed));
}

GrBx::Axis::~Axis ()
{

}

const Gtk::Adjustment& GrBx::Axis::get_adjustment () const
{
    return adjustment;
}

double GrBx::Axis::get_step () const
{
    return step;
}

void GrBx::Axis::set_step (double _step)
{
    step = _step;
}

bool GrBx::Axis::on_expose_event (GdkEventExpose *_expose)
{
    bool ret = GrBx::Widget::on_expose_event (_expose);
    if (_expose) draw_frame ();
    return ret;
}

void GrBx::Axis::set_cursor_pos (double _pos)
{
    if (pixbuf && window) window->draw_pixbuf (pixbuf, 0, 0, 0, 0, get_width (), get_height (), Gdk::RGB_DITHER_NONE, 0, 0);
}

void GrBx::Axis::draw_frame ()
{
    if (window && is_drawable ())
    {
	Cairo::RefPtr<Cairo::Context> cr = window->create_cairo_context ();
	cr->rectangle (0, 0, get_width (), get_height ());
	cr->set_line_width (7);
	cr->stroke ();
    }
}

void GrBx::Axis::on_adjustment_changed ()
{
    if (window && window->is_viewable ())
    {
	window->draw_rectangle (get_style ()->get_fg_gc (Gtk::STATE_NORMAL), true, 0, 0, get_width (), get_height ());
	draw_frame ();
	draw_dial ();
    }
}

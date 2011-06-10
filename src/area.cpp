#include <grbx/area.h>

static const double ZOOM_STEP = 0.1;
static const double WIDTH_REQUIRED = 400;
static const double HEIGHT_REQUIRED = 400;

GrBx::Area::Area (Gtk::Adjustment &_hadjustment, Gtk::Adjustment &_vadjustment)
    : hadjustment (_hadjustment),
      vadjustment (_vadjustment),
      sx (1),
      sy (1)
{
    set_has_window (false);
    hadjustment.signal_value_changed ().connect (sigc::mem_fun (*this, &GrBx::Area::on_adjustment_value_changed));
    vadjustment.signal_value_changed ().connect (sigc::mem_fun (*this, &GrBx::Area::on_adjustment_value_changed));
}

GrBx::Area::~Area ()
{

}

const Gtk::Adjustment& GrBx::Area::get_hadjustment () const
{
    return hadjustment;
}

const Gtk::Adjustment& GrBx::Area::get_vadjustment () const
{
    return vadjustment;
}

Gtk::Adjustment& GrBx::Area::get_hadjustment ()
{
    return hadjustment;
}

Gtk::Adjustment& GrBx::Area::get_vadjustment ()
{
    return vadjustment;
}

void GrBx::Area::append_graph (const Glib::RefPtr<GrBx::Graph> &_graph)
{
    Graphs::iterator itr = std::find (graphs.begin (), graphs.end (), _graph);
    if (_graph && itr == graphs.end ())
    {
	graphs.push_back (_graph);
	_graph->signal_visible_changed ().connect (sigc::mem_fun (*this, &GrBx::Area::on_graph_visible_changed));
    }
}

void GrBx::Area::remove_graph (const Glib::RefPtr<GrBx::Graph> &_graph)
{
    std::remove (graphs.begin (), graphs.end (), _graph);
}

int GrBx::Area::find_graph (const Glib::RefPtr<GrBx::Graph> &_graph)
{
    Graphs::iterator itr = std::find (graphs.begin (), graphs.end (), _graph);
    return (itr == graphs.end ()) ? -1 : itr - graphs.begin ();
}

Glib::RefPtr<GrBx::Graph> GrBx::Area::get_graph (unsigned _pos)
{
    return (_pos < graphs.size ()) ? graphs [_pos] : Glib::RefPtr<GrBx::Graph> ();
}

void GrBx::Area::convert_position_to_value (double _x_pos, double _y_pos, double &_x_value, double &_y_value)
{
    _x_value = (_x_pos * hadjustment.get_page_size () / get_width () + hadjustment.get_lower ()) / hadjustment.get_step_increment ();
    _y_value = ((get_height () - _y_pos) * vadjustment.get_page_size () / get_height () + vadjustment.get_lower ()) / vadjustment.get_step_increment ();
}

void GrBx::Area::on_realize ()
{
    GrBx::Widget::on_realize ();
    if (window) window->set_events (window->get_events () | Gdk::POINTER_MOTION_MASK | Gdk::SCROLL_MASK | Gdk::BUTTON_PRESS_MASK);
    alignment_all ();
}

void GrBx::Area::on_unrealize ()
{
    GrBx::Widget::on_unrealize ();
}

void GrBx::Area::on_size_request (Gtk::Requisition *_requisition)
{
    _requisition->width = WIDTH_REQUIRED;
    _requisition->height = HEIGHT_REQUIRED;
}

bool GrBx::Area::on_expose_event (GdkEventExpose *_expose)
{
    bool ret = GrBx::Widget::on_expose_event (_expose);
    if (_expose) draw_graphs ();
    return ret;
}

bool GrBx::Area::on_motion_notify_event (GdkEventMotion *_motion)
{
    bool ret = GrBx::Widget::on_motion_notify_event (_motion);
    if (_motion && window && is_drawable ())
    {
	double width = get_width (), height = get_height ();
	const Glib::RefPtr<Gdk::GC> black_gc = get_style ()->get_black_gc ();
	if (pixbuf) window->draw_pixbuf (pixbuf, 0, 0, 0, 0, width, height, Gdk::RGB_DITHER_NONE, 0, 0);
	window->draw_line (black_gc, _motion->x, 0, _motion->x, height);
	window->draw_line (black_gc, 0, _motion->y, width, _motion->y);
    }
    return ret;
}

bool GrBx::Area::on_scroll_event (GdkEventScroll *_scroll)
{
    bool ret = Gtk::Widget::on_scroll_event (_scroll);
    if (_scroll)
    {
	double prev_sx = sx, prev_sy = sy;
	double x1, y1, x2, y2;
	calculate_bounds (x1, y1, x2, y2);
	switch (_scroll->direction)
	{
	    case GDK_SCROLL_UP:
		sx += ZOOM_STEP;
		sy += ZOOM_STEP;
		break;
		
	    case GDK_SCROLL_DOWN:
		if (sx > ZOOM_STEP && sy > ZOOM_STEP)
		{
		    sx -= ZOOM_STEP;
		    sy -= ZOOM_STEP;
		}
		break;
		
	    default:
		break;
	}
	if (prev_sx != sx) hadjustment.configure (hadjustment.get_value () / prev_sx * sx, x1 * sx, x2 * sx, sx, 10 * sx, hadjustment.get_page_size ());
	if (prev_sy != sy) vadjustment.configure (vadjustment.get_value () / prev_sy * sy, y1 * sy, y2 * sy, sy, 10 * sy, vadjustment.get_page_size ());
	if (prev_sx != sx || prev_sy != sy) draw_graphs ();
    }
    return ret;
}

bool GrBx::Area::on_button_press_event (GdkEventButton *_button)
{
    GrBx::Widget::on_button_press_event (_button);
    if (_button && _button->button == 2)
    {
        alignment_all ();
        draw_graphs ();
    }
    return true;
}

void GrBx::Area::on_adjustment_value_changed ()
{
    draw_graphs ();
}

void GrBx::Area::on_graph_visible_changed ()
{
    alignment_all ();
    draw_graphs ();
}

void GrBx::Area::draw_graphs ()
{
    if (window && is_drawable ())
    {
	window->draw_rectangle (get_style ()->get_fg_gc (Gtk::STATE_NORMAL), true, 0, 0, get_width (), get_height ());

	Cairo::RefPtr<Cairo::Context> cr = window->create_cairo_context ();
	Cairo::Matrix matrix (1, 0, 0, -1, - hadjustment.get_value (), get_height () + vadjustment.get_value ());
	cr->transform (matrix);
	for (Graphs::iterator gitr = graphs.begin (); gitr != graphs.end (); ++gitr)
	    if ((*gitr)->get_visible ()) (*gitr)->draw (cr, sx, sy);

	update_pixbuf ();
    }
}

void GrBx::Area::calculate_bounds (double &_x1, double &_y1, double &_x2, double &_y2)
{
    _x1 = _y1 = INFINITY;
    _x2 = _y2 = 0;
    for (Graphs::iterator itr = graphs.begin (); itr != graphs.end (); ++itr)
	if ((*itr)->get_visible ())
	{
	    double x1, y1, x2, y2;
	    (*itr)->calculate_bounds (x1, y1, x2, y2);
	    if (x1 < _x1) _x1 = x1;
	    if (y1 < _y1) _y1 = y1;
	    if (x2 > _x2) _x2 = x2;
	    if (y2 > _y2) _y2 = y2;
	}
    if (_x1 == INFINITY) _x1 = 0;
    if (_y1 == INFINITY) _y1 = 0;
    if (_x2 == 0) _x2 = 1;
    if (_y2 == 0) _y2 = 1;
}

void GrBx::Area::alignment_all ()
{
    double x1, y1, x2, y2;
    calculate_bounds (x1, y1, x2, y2);
    
    sx = get_width () / (x2 - x1);
    sy = get_height () / (y2 - y1);

    hadjustment.configure (x1 * sx, x1 * sx, x2 * sx, sx, 10 * sx, (x2 - x1) * sx);
    vadjustment.configure (y1 * sy, y1 * sy, y2 * sy, sy, 10 * sy, (y2 - y1) * sy);
}

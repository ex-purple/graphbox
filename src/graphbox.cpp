#include <grbx/graphbox.h>
#include <grbx/haxis.h>
#include <grbx/vaxis.h>

#include <gtkmm/viewport.h>
#include <gtkmm/scrollbar.h>

GrBx::Graphbox::Graphbox (bool _has_haxis, bool _has_vaxis)
    : Gtk::Table (3, 3),
      hadjustment (0, 0, 0),
      vadjustment (0, 0, 0),
      area (hadjustment, vadjustment),
      haxis (_has_haxis ? new GrBx::HAxis (area) : NULL),
      vaxis (_has_vaxis ? new GrBx::VAxis (area) : NULL)
{
    Gtk::HScrollbar *hscrollbar = Gtk::manage (new Gtk::HScrollbar (hadjustment));
    Gtk::VScrollbar *vscrollbar = Gtk::manage (new Gtk::VScrollbar (vadjustment));
    vscrollbar->set_inverted (true);

    attach (area, 2, 3, 0, 1, Gtk::FILL | Gtk::EXPAND, Gtk::FILL | Gtk::EXPAND);
    attach (*hscrollbar, 2, 3, 2, 3, Gtk::FILL | Gtk::EXPAND, Gtk::FILL);
    attach (*vscrollbar, 0, 1, 0, 1, Gtk::FILL, Gtk::FILL | Gtk::EXPAND);
    if (haxis) attach (*haxis, 2, 3, 1, 2, Gtk::FILL | Gtk::EXPAND, Gtk::FILL);
    if (vaxis) attach (*vaxis, 1, 2, 0, 1, Gtk::FILL, Gtk::FILL | Gtk::EXPAND);
}

GrBx::Graphbox::~Graphbox ()
{
    if (haxis) delete haxis;
    if (vaxis) delete vaxis;
}

void GrBx::Graphbox::append_graph (const Glib::RefPtr<GrBx::Graph> &_graph)
{
    area.append_graph (_graph);
}

void GrBx::Graphbox::remove_graph (const Glib::RefPtr<GrBx::Graph> &_graph)
{
    area.remove_graph (_graph);
}

int GrBx::Graphbox::find_graph (const Glib::RefPtr<GrBx::Graph> &_graph)
{
    return area.find_graph (_graph);
}

Glib::RefPtr<GrBx::Graph> GrBx::Graphbox::get_graph (unsigned _pos)
{
    return area.get_graph (_pos);
}

void GrBx::Graphbox::set_axis_step (double _haxis_step, double _vaxis_step)
{
    if (haxis) haxis->set_step (_haxis_step);
    if (vaxis) vaxis->set_step (_vaxis_step);
}

void GrBx::Graphbox::convert_position_to_value (double _x_pos, double _y_pos, double &_x_value, double &_y_value)
{
    area.convert_position_to_value (_x_pos, _y_pos, _x_value, _y_value);
}

Glib::SignalProxy1<bool, GdkEventMotion*> GrBx::Graphbox::signal_motion_notify_event ()
{
    return area.signal_motion_notify_event ();
}

#ifndef _GRBX_GRAPHBOX_H_
#define _GRBX_GRAPHBOX_H_

#include "axis.h"
#include "area.h"

#include <gtkmm/table.h>

namespace GrBx
{
    class Graphbox : public Gtk::Table
    {
	public:
	Graphbox (bool _has_haxis = true, bool _has_vaxis = true);
	virtual ~Graphbox ();

	public:
	void append_graph (const Glib::RefPtr<GrBx::Graph> &_graph);
	void remove_graph (const Glib::RefPtr<GrBx::Graph> &_graph);
	int find_graph (const Glib::RefPtr<GrBx::Graph> &_graph);
	Glib::RefPtr<GrBx::Graph> get_graph (unsigned _pos);
	void set_axis_step (double _haxis_step, double _vaxis_step);
	void convert_position_to_value (double _x_pos, double _y_pos, double &_x_value, double &_y_value);
	Glib::SignalProxy1<bool, GdkEventMotion*> signal_motion_notify_event ();
	
	private:
	Gtk::Adjustment hadjustment, vadjustment;
	GrBx::Area area;
	Gtk::PolicyType hscrollbar_policy, vscrollbar_policy;
	GrBx::Axis *haxis, *vaxis;
    };
}

#endif //_GRBX_GRAPHBOX_H_

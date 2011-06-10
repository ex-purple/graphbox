#ifndef _GRBX_AREA_H_
#define _GRBX_AREA_H_

#include "widget.h"
#include "graph.h"

#include <gtkmm/adjustment.h>

namespace GrBx
{
    class Area : public GrBx::Widget
    {
	public:
	Area (Gtk::Adjustment &_hadjustment, Gtk::Adjustment &_vadjustment);
	virtual ~Area ();
	
	public:
	const Gtk::Adjustment& get_hadjustment () const;
	const Gtk::Adjustment& get_vadjustment () const;
	Gtk::Adjustment& get_hadjustment ();
	Gtk::Adjustment& get_vadjustment ();
	void append_graph (const Glib::RefPtr<GrBx::Graph> &_graph);
	void remove_graph (const Glib::RefPtr<GrBx::Graph> &_graph);
	int find_graph (const Glib::RefPtr<GrBx::Graph> &_graph);
	Glib::RefPtr<GrBx::Graph> get_graph (unsigned _pos);
	void convert_position_to_value (double _x_pos, double _y_pos, double &_x_value, double &_y_value);
	
	private:
	Area (const Area &_area);

    	private:
	virtual void on_realize ();
	virtual void on_unrealize ();
	virtual void on_size_request (Gtk::Requisition *_requisition);
	virtual bool on_expose_event (GdkEventExpose *_expose);
	virtual bool on_motion_notify_event (GdkEventMotion *_motion);
	virtual bool on_scroll_event (GdkEventScroll *_scroll);
	virtual bool on_button_press_event (GdkEventButton *_button);
	void on_adjustment_value_changed ();
	void on_graph_visible_changed ();
	void draw_graphs ();
	void calculate_bounds (double &_x1, double &_y1, double &_x2, double &_y2);
	void alignment_all ();

	private:
	typedef std::vector<Glib::RefPtr<GrBx::Graph> > Graphs;
	
	private:
	Gtk::Adjustment &hadjustment, &vadjustment;
	Graphs graphs;
	double sx, sy;
    };
}

#endif //_GRBX_AREA_H_

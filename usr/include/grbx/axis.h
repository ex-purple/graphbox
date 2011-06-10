#ifndef _GRBX_AXIS_H_
#define _GRBX_AXIS_H_

#include "area.h"

#include <gtkmm/adjustment.h>

namespace GrBx
{
    class Axis : public GrBx::Widget
    {
	public:
	Axis (GrBx::Area &_area, Gtk::Adjustment &_adjustment);
	virtual ~Axis () = 0;

	public:
	const Gtk::Adjustment& get_adjustment () const;
	double get_step () const;
	void set_step (double _step);
	
	protected:
	virtual bool on_expose_event (GdkEventExpose *_expose) = 0;
	virtual bool on_area_motion_notify_event (GdkEventMotion *_motion) = 0;
	virtual void draw_dial () = 0;
	virtual void set_cursor_pos (double _pos) = 0;
	virtual double convert_position_to_value (double _pos) = 0;
	void draw_frame ();
	
	private:
	void on_adjustment_changed ();

	private:
	GrBx::Area &area;
	Gtk::Adjustment &adjustment;
	double step;
    };
}

#endif //_GRBX_AXIS_H_

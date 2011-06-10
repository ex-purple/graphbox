#ifndef _GRBX_VAXIS_H_
#define _GRBX_VAXIS_H_

#include "axis.h"

namespace GrBx
{
    class VAxis : public GrBx::Axis
    {
	public:
	VAxis (GrBx::Area &_area);
	virtual ~VAxis ();
	
	private:
	virtual void on_size_request (Gtk::Requisition *_requisition);
	virtual bool on_expose_event (GdkEventExpose *_expose);
	virtual bool on_area_motion_notify_event (GdkEventMotion *_motion);
	virtual void draw_dial ();
	virtual void set_cursor_pos (double _pos);
	virtual double convert_position_to_value (double _pos);
    };
}

#endif //_GRBX_VAXIS_H_

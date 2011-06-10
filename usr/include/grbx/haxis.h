#ifndef _GRBX_HAXIS_H_
#define _GRBX_HAXIS_H_

#include "axis.h"

namespace GrBx
{
    class HAxis : public GrBx::Axis
    {
	public:
	HAxis (GrBx::Area &_area);
	virtual ~HAxis ();
	
	private:
	virtual void on_size_request (Gtk::Requisition *_requisition);
	virtual bool on_expose_event (GdkEventExpose *_expose);
	virtual bool on_area_motion_notify_event (GdkEventMotion *_motion);
	virtual void draw_dial ();
	virtual void set_cursor_pos (double _pos);
	virtual double convert_position_to_value (double _pos);
    };
}

#endif //_GRBX_HAXIS_H_

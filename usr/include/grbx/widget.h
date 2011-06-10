#ifndef _GRBX_WIDGET_H_
#define _GRBX_WIDGET_H_

#include <gtkmm/widget.h>

namespace GrBx
{
    class Widget : public Gtk::Widget
    {
	public:
	Widget ();
	virtual ~Widget () = 0;
	
	protected:
	virtual void on_realize ();
	virtual void on_unrealize ();
	void update_pixbuf ();

	protected:
	Glib::RefPtr<Gdk::Window> window;
	Glib::RefPtr<Gdk::Pixbuf> pixbuf;
    };
}

#endif //_GRBX_WIDGET_H_

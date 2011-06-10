#include <grbx/widget.h>

GrBx::Widget::Widget ()
{
    set_has_window (false);
}

GrBx::Widget::~Widget ()
{

}

void GrBx::Widget::on_realize ()
{ 
    Gtk::Widget::on_realize ();   
    if (!window)
    {
	GdkWindowAttr attributes;
	memset (&attributes, 0, sizeof attributes);

	const Gtk::Allocation &allocation = get_allocation ();
	attributes.x = allocation.get_x ();
	attributes.y = allocation.get_y ();
	attributes.width = allocation.get_width ();
	attributes.height = allocation.get_height ();

	attributes.event_mask = get_events () | Gdk::EXPOSURE_MASK;
	attributes.window_type = GDK_WINDOW_CHILD;
	attributes.wclass = GDK_INPUT_OUTPUT;

	window = Gdk::Window::create (get_window (), &attributes, GDK_WA_X | GDK_WA_Y);
	set_has_window ();
	set_window (window);
	
	modify_bg (Gtk::STATE_NORMAL, Gdk::Color ("white"));
	modify_fg (Gtk::STATE_NORMAL, Gdk::Color ("white"));
	
	window->set_user_data (gobj ());
	window->ensure_native ();
    }
}

void GrBx::Widget::on_unrealize ()
{
    pixbuf.reset ();
    window.reset ();
    Gtk::Widget::on_unrealize ();
}

void GrBx::Widget::update_pixbuf ()
{
    if (get_is_drawable () && window)
    {
	if (pixbuf) pixbuf.reset ();
	pixbuf = Gdk::Pixbuf::create (Glib::RefPtr<Gdk::Drawable>::cast_static (window), 0, 0, get_width (), get_height ());
    }
}

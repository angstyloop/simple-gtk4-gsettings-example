#include "example.h"

struct _GtkExample
{
	GtkDialog parent;
	GSettings *settings;
	GtkDropDown *enum0;
	GtkText *string0;
	GtkScaleButton *uint0;
	GtkCheckButton *bool0;
};

G_DEFINE_TYPE( GtkExample, gtk_example, GTK_TYPE_DIALOG );

static void
gtk_example_dispose( GObject *gobject )
{
	GtkExample *e = GTK_EXAMPLE( gobject );
	g_clear_object( &e->settings );
	G_OBJECT_CLASS( gtk_example_parent_class )->dispose( gobject );
}

static void
gtk_example_init( GtkExample *e )
{
	gtk_widget_init_template( GTK_WIDGET( e ) );
 	e->settings = g_settings_new( "org.gtk.example" );
	g_settings_bind( e->settings, "enum0",
		e->enum0, "selected", G_SETTINGS_BIND_DEFAULT );
	g_settings_bind( e->settings, "string0",
		e->string0, "text", G_SETTINGS_BIND_DEFAULT );
	g_settings_bind( e->settings, "uint0",
		e->uint0, "value", G_SETTINGS_BIND_DEFAULT );
	g_settings_bind( e->settings, "bool0",
		e->bool0, "active", G_SETTINGS_BIND_DEFAULT );
}

static void
gtk_example_class_init( GtkExampleClass *class )
{
	GObjectClass *object_class = G_OBJECT_CLASS( class );
	object_class->dispose = gtk_example_dispose;
	gtk_widget_class_set_template_from_resource( GTK_WIDGET_CLASS( class ),
		"/org/gtk/example/example.ui" );
	gtk_widget_class_bind_template_child( GTK_WIDGET_CLASS ( class ),
		GtkExample, enum0 );
	gtk_widget_class_bind_template_child( GTK_WIDGET_CLASS ( class ),
		GtkExample, string0 );
	gtk_widget_class_bind_template_child( GTK_WIDGET_CLASS ( class ),
		GtkExample, uint0 );
	gtk_widget_class_bind_template_child( GTK_WIDGET_CLASS ( class ),
		GtkExample, bool0 );
}

GtkWidget *
gtk_example_new( void ) {
  return GTK_WIDGET( g_object_new( GTK_EXAMPLE_TYPE_PREF, NULL ) );
}

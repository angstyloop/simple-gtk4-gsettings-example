#include <gtk/gtk.h>
#include "example.h"

#if GLIB_CHECK_VERSION( 2, 74, 0 )
static int app_flags = G_APPLICATION_DEFAULT_FLAGS;
#else
static int app_flags = G_APPLICATION_FLAGS_NONE;
#endif

static void
gtk_example_response( GtkDialog *example,
	gint response_id, gpointer user_data )
{
	printf( "response_id: %d", response_id );
	gtk_window_destroy( GTK_WINDOW( example ) );
}

static void
activate( GtkApplication *app, gpointer user_data )
{
	GtkWidget *window = gtk_application_window_new( app );
	GtkWidget *e = ( GtkWidget* ) gtk_example_new();
	gtk_window_set_transient_for( GTK_WINDOW( e ), GTK_WINDOW( window ) );
	gtk_window_present( GTK_WINDOW ( e ) );
	GtkWidget *box = gtk_box_new( GTK_ORIENTATION_VERTICAL, 0 );
	gtk_widget_set_halign ( box, GTK_ALIGN_CENTER );
	gtk_widget_set_valign ( box, GTK_ALIGN_CENTER );
	gtk_window_set_child ( GTK_WINDOW ( window ), box );
	gtk_window_set_transient_for( GTK_WINDOW( e ), GTK_WINDOW( window ));
	g_signal_connect( GTK_DIALOG( e ),
		"response", G_CALLBACK( gtk_example_response ), window );
	gtk_widget_show( window );
	gtk_window_present( GTK_WINDOW( e ) );
}

int
main( int argc, char *argv[] )
{
	g_setenv ("GSETTINGS_SCHEMA_DIR", ".", FALSE);
	GtkApplication *app = gtk_application_new( "org.gtk.example", app_flags );
	g_signal_connect( app, "activate", G_CALLBACK( activate ), NULL );
	int status = g_application_run( G_APPLICATION( app ), argc, argv );
	g_object_unref( app );
	return status;
}

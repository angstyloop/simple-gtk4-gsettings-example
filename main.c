#include <gtk/gtk.h>
#include "example.h"

#if GLIB_CHECK_VERSION( 2, 74, 0 )
static int app_flags = G_APPLICATION_DEFAULT_FLAGS;
#else
static int app_flags = G_APPLICATION_FLAGS_NONE;
#endif

#define GTK_RESPONSE_EXAMPLE 0

static void
gtk_file_chooser_response( GtkFileChooserDialog *chooser,
	gint response_id, gpointer user_data )
{
	if (response_id == GTK_RESPONSE_ACCEPT) {
		GFile *file = gtk_file_chooser_get_file( GTK_FILE_CHOOSER( chooser ) );
		gchar* path = g_file_get_path(file);
		puts(path);
		g_free(path);
		g_object_unref(file);
		g_object_unref(chooser);
	} else if (response_id == GTK_RESPONSE_EXAMPLE) {
		GtkExample* e = GTK_EXAMPLE( user_data );
		gtk_window_present( GTK_WINDOW( e ) );
	} else {
		/* ... */
	}

}

static void
activate( GtkApplication *app, gpointer user_data )
{
	GtkWidget *window = gtk_application_window_new( app );

	GtkWidget* chooser =
		gtk_file_chooser_dialog_new("Open File",
			(GtkWindow*) window,
			GTK_FILE_CHOOSER_ACTION_OPEN,
			"Cancel",
			GTK_RESPONSE_CANCEL,
			"Open",
			GTK_RESPONSE_ACCEPT,
			NULL);

	GtkWidget *e = ( GtkWidget* ) gtk_example_new();

	gtk_dialog_add_button( GTK_DIALOG( chooser ), "Save Options...", GTK_RESPONSE_EXAMPLE );

	g_signal_connect( chooser,
		"response", G_CALLBACK(gtk_file_chooser_response), e );

	gtk_window_set_transient_for( GTK_WINDOW( e ), GTK_WINDOW( window ));

	gtk_widget_show( window );

	gtk_widget_show(chooser);
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

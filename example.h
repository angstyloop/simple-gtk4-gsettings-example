#ifndef __GTK_EXAMPLE_H__
#define __GTK_EXAMPLE_H__

#include <gtk/gtk.h>

#define GTK_EXAMPLE_TYPE_PREF gtk_example_get_type()
G_DECLARE_FINAL_TYPE( GtkExample, gtk_example, GTK, EXAMPLE, GtkWindow )

GtkWidget *
gtk_example_new( void );

#endif /* __GTK_EXAMPLE_H__ */

#ifndef GTK_COMMON_H_
#define GTK_COMMON_H_

#include <gtk/gtk.h>

void 		gtk_common_init(GtkBuilder *builder);
GObject* 	g_get_object(const char *name);
GtkObject* 	gtk_get_object(const char *name);
GtkWidget* 	gtk_get_widget(const char *name);

void 		gtk_switch_button_switch(GtkButton *button, const char *container_name, const char *image_show_name, const char *image_hide_name);

#endif /* GTK_COMMON_H_ */

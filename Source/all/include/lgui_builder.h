#ifndef LGUI_BUILDER_H_
#define LGUI_BUILDER_H_

#include <gtk/gtk.h>

GtkWidget* 	lgui_builder_get_window						(GtkBuilder *builder, const char *id);
GtkWidget* 	lgui_builder_get_box						(GtkBuilder *builder, const char *id);
GtkButton* 	lgui_builder_get_switch_button				(GtkBuilder *builder, const char *id);
GtkButton* 	lgui_builder_get_switch_check_button		(GtkBuilder *builder, const char *id);


#endif /* LGUI_BUILDER_H_ */

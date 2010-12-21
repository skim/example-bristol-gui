#ifndef LGUI_COMMON_H_
#define LGUI_COMMON_H_

#include <gtk/gtk.h>

const char* lgui_name_new								(const char *id, const char *widget_type);

GtkButton* 	lgui_builder_get_switch_button				(GtkBuilder *builder, const char *id);
GtkButton* 	lgui_builder_get_switch_check_button		(GtkBuilder *builder, const char *id);
GtkWidget* 	lgui_builder_get_box						(GtkBuilder *builder, const char *id);

void 		lgui_switch_button_visible_connect			(GtkBuilder *builder, const char *id);
void 		lgui_switch_check_button_sensitive_connect	(GtkBuilder *builder, const char *id);

#endif /* LGUI_COMMON_H_ */

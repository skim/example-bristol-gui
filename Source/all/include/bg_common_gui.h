#ifndef BG_COMMON_GUI_H_
#define BG_COMMON_GUI_H_

#include <gtk/gtk.h>

GtkWidget* 	gtkc_image_new_from_file_scaled(const char *filename, double scale);
void 		gtkc_label_add_attribute(GtkWidget *label, PangoAttribute *attribute);
GtkWidget* 	gtkc_switch_hbox_new(const char *label_text, const char *stock_image_show, const char *stock_image_hide, GtkWidget *widget_to_switch);

#endif /* BG_COMMON_GUI_H_ */

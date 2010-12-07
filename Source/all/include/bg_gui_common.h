#ifndef BG_GUI_COMMON_H_
#define BG_GUI_COMMON_H_

#include <gtk/gtk.h>

GtkWidget* 	bg_new_scaled_image_from_file(const char *filename, double scale);
void 		bg_label_add_attribute(GtkWidget *label, PangoAttribute *attribute);

#endif /* BG_GUI_COMMON_H_ */

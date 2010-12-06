#ifndef GTK_COMMON_H_
#define GTK_COMMON_H_

#include <gtk/gtk.h>

void 			gtkc_init(GtkBuilder *builder);
GObject* 		gtkc_get_gobject(const char *name);
GtkObject* 		gtkc_get_object(const char *name);
GtkWidget* 		gtkc_get_widget(const char *name);
GtkEntry* 		gtkc_get_entry(const char *name);
GtkImage* 		gtkc_get_image(const char *name);
GtkAdjustment*	gtkc_get_adjustment(const char *name);
GtkComboBox *	gtkc_get_combo_box(const char *name);

void 		gtkc_switch_button_switch(GtkButton *button, const char *container_name, const char *image_show_name, const char *image_hide_name);
void 		gtkc_entry_set_value(const char *name, const char *value);
void 		gtkc_adjustment_set_value(const char *name, double value);
void		gtkc_combo_box_set_active(const char *name, unsigned int value);

#endif /* GTK_COMMON_H_ */

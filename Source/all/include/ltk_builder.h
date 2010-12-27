#ifndef LTK_BUILDER_H_
#define LTK_BUILDER_H_

#include <gtk/gtk.h>

GtkBuilder* 		ltk_builder_new_from_data_path	(const char *filename);
GtkWidget* 			ltk_builder_get_widget			(GtkBuilder *builder, const char *name);
GtkButton*			ltk_builder_get_button			(GtkBuilder *builder, const char *name);
GtkToggleButton* 	ltk_builder_get_toggle_button	(GtkBuilder *builder, const char *name) ;
GtkComboBox*		ltk_builder_get_combo_box		(GtkBuilder *builder, const char *name);

#endif /* LTK_BUILDER_H_ */

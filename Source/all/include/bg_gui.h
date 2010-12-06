#ifndef GUI_H_
#define GUI_H_

#include "bg_data.h"
#include <gtk/gtk.h>

typedef struct {
	GtkBuilder 	*builder;
	GtkWidget 	*window_root;
	GtkWidget	*box_params;
	GtkWidget 	*notebook_companies;
	GHashTable 	*notebooks_synths;
	GHashTable	*boxes_params_synths;
} bg_gui;

bg_gui* bg_gui_new(GtkBuilder *builder, bg_store *store);

void bg_gui_show(bg_gui* gui);
void bg_gui_switch_audioproperties(bg_gui *gui);


#endif /* GUI_H_ */

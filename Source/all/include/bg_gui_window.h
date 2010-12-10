#ifndef BG_GUI_H_
#define BG_GUI_H_

#include "bg_config.h"
#include "bg_data.h"
#include <gtk/gtk.h>

typedef struct {
	GtkWidget 	*window_root;
	GtkWidget 	*notebook_categories;
	GHashTable 	*notebooks_synths;
	BgStore 	*store;
} bg_gui;

bg_gui* bg_gui_new(int *argc, char ***argv, BgStore *store);
void 	bg_gui_add_category(bg_gui *gui, BgCategory *category);
void 	bg_gui_add_synth(bg_gui *gui, BgSynth *synth);
void 	bg_gui_main(bg_gui *gui);

#endif /* BG_GUI_H_ */

#include "bg_data.h"
#include "bg_gui.h"
#include <gtk/gtk.h>

int main(int argc, char **argv) {
	//data setup
	bg_store *store = bg_store_new();
	bg_category *moog = bg_category_new(store, "moog", "Moog");
	bg_synth *mini = bg_synth_new(store, moog, "mini", "Mini");
	bg_synth *explorer = bg_synth_new(store, moog, "explorer", "Voyager");
	bg_category *circuits = bg_category_new(store, "circuits", "Sequential Circuits");
	bg_synth *pro5 = bg_synth_new(store, circuits, "pro5", "Prophet 5");
	bg_synth *pro10 = bg_synth_new(store, circuits, "pro10", "Prophet 10");
	//gui setup
	bg_gui *gui = bg_gui_new(&argc, &argv);
	bg_gui_add_synth(gui, mini);
	bg_gui_add_synth(gui, explorer);
	bg_gui_add_synth(gui, pro5);
	bg_gui_add_synth(gui, pro10);
	//go
	bg_gui_main(gui);
	return 0;
}

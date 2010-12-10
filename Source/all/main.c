#include "bg_config.h"
#include "bg_data.h"
#include "bg_gui_window.h"
#include <gtk/gtk.h>

int main(int argc, char **argv) {
	//data setup
	BgStore *store = bg_store_new();
	BgCategory *moog = bg_category_new(store, "moog", "Moog");
	bg_synth_new(store, moog, "mini", "Mini", "mini.png");
	bg_synth_new(store, moog, "explorer", "Voyager", "explorer.png");

	BgCategory *circuits = bg_category_new(store, "circuits", "Sequential Circuits");
	bg_synth_new(store, circuits, "pro5", "Prophet 5", "pro5.png");
	bg_synth_new(store, circuits, "pro10", "Prophet 10", "pro10.png");

	bg_profile_new(store, "silent", "Silent");

	//gui setup
	bg_gui *gui = bg_gui_new(&argc, &argv, store);

	//go
	bg_gui_main(gui);
	return 0;
}

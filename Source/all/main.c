#include "bg_data.h"
#include "bg_gui.h"
#include <gtk/gtk.h>

static bg_store* bg_create_data() {
	bg_store *store = bg_store_new();
	bg_category *moog = bg_category_new(store, "moog", "Moog");
	bg_synth_new(store, moog, "mini", "Mini");
	bg_synth_new(store, moog, "explorer", "Voyager");
	bg_category *circuits = bg_category_new(store, "circuits", "Sequential Circuits");
	bg_synth_new(store, circuits, "pro5", "Prophet 5");
	bg_synth_new(store, circuits, "pro10", "Prophet 10");
	return store;
}

int main(int argc, char **argv) {
	bg_store *store = bg_create_data();
	gtk_init(&argc, &argv);
	GtkWidget *window = bg_window_new();
	gtk_widget_show_all(window);
	gtk_main();
	return 0;
}

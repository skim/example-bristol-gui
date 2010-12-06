#include <gtk/gtk.h>
#include "bg_gui.h"
#include "bg_data.h"
#include "gtkc_all.h"
#include "bg_handlers.h"

int main(int argc, char **argv) {
	gtk_init(&argc, &argv);
	GtkBuilder *builder = gtk_builder_new();
	GError *error = NULL;
	if (!gtk_builder_add_from_file(builder, "Data/Gtk/mainwindow.glade", &error)) {
		g_warning("%s", error->message);
		return 1;
	} else {
		bg_store *store = bg_store_new();

		bg_company *circuits = bg_company_new(store, "circuits", "Sequential Circuits");
		bg_synth_new(circuits, "pro10", "Prophet 10", "Data/Gtk/prophet-10.png");
		bg_synth_new(circuits, "pro5", "Prophet 5", "Data/Gtk/prophet-5.png");

		bg_company *moog = bg_company_new(store, "moog", "Moog");
		bg_synth_new(moog, "explorer", "Voyager", "Data/Gtk/explorer.png");
		bg_synth_new(moog, "mini", "Mini", "Data/Gtk/mini.png");

		bg_gui *gui = bg_gui_new(builder, store);
		bg_handlers_init(store, gui);

		bg_gui_show(gui);

		g_object_unref(builder);
	}
	return 0;
}

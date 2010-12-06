#include <gtk/gtk.h>
#include "bg_gui.h"
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
		gtkc_init(builder);
		GtkWidget *window = gtkc_get_widget("window_root");
		bg_gui_prepare("mini");
		bg_gui_set("mini", bg_configuration_new("mini-default"));
		gtk_builder_connect_signals(builder, NULL);
		gtk_widget_show(window);
		gtk_main();
		g_object_unref(builder);
	}
	return 0;
}

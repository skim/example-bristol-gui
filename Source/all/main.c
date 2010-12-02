#include <gtk/gtk.h>
#include "handlers.h"

int main(int argc, char **argv) {
	gtk_init(&argc, &argv);
	GtkBuilder *builder = gtk_builder_new();
	GError *error = NULL;
	if (!gtk_builder_add_from_file(builder, "Data/Gtk/mainwindow.glade", &error)) {
		g_warning("%s", error->message);
		return 1;
	} else {
		GtkWidget *window = GTK_WIDGET(gtk_builder_get_object(builder, "window_root"));
		gtk_builder_connect_signals(builder, NULL);
		init_handlers(builder);
		gtk_widget_show(window);
		gtk_main();
		g_object_unref(builder);
	}
	return 0;
}

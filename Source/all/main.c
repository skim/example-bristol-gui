#include <gtk/gtk.h>
#include "gtk_common.h"
#include "handlers.h"
#include "gui.h"

int main(int argc, char **argv) {
	gtk_init(&argc, &argv);
	GtkBuilder *builder = gtk_builder_new();
	GError *error = NULL;
	if (!gtk_builder_add_from_file(builder, "Data/Gtk/mainwindow.glade", &error)) {
		g_warning("%s", error->message);
		return 1;
	} else {
		gtk_common_init(builder);
		GtkWidget *window = gtk_get_widget("window_root");
		bg_prepare_combo_soundengine("combo_soundengine_mini");
		bg_prepare_entry_identifier("entry_identifier_mini", "mini");
		bg_prepare_adjust_samplerate("adjust_samplerate_mini", 44100);
		bg_prepare_adjust_midichannel("adjust_midichannel_mini", 1);
		gtk_builder_connect_signals(builder, NULL);
		gtk_widget_show(window);
		gtk_main();
		g_object_unref(builder);
	}
	return 0;
}

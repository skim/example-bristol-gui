#include "bg_common_basic.h"
#include "bg_config.h"
#include "lgtk.h"
#include <gtk/gtk.h>


int main(int argc, char **argv) {
	gtk_init(&argc, &argv);
	GtkBuilder *builder = gtk_builder_new();
	GError *error = NULL;
	gtk_builder_add_from_file(builder, bg_make_path(BG_GLADE_FILE), &error);
	if (error != NULL) {
		g_error("Error: %s", error->message);
		return 1;
	} else {
		GtkWidget *window = GTK_WIDGET(gtk_builder_get_object(builder, "window_root"));
		lgtk_builder_signal_switch_connect(builder, "switch_profile", "box_profile");
		lgtk_builder_signal_switch_connect(builder, "switch_synth", "box_synth");
		lgtk_builder_signal_switch_connect(builder, "switch_options", "box_options");
		lgtk_builder_signal_switch_connect(builder, "switch_runtimes", "box_runtimes");
		gtk_widget_show_all(window);
		gtk_main();
	}
	return 0;
}


#include "llib.h"
#include "ltk.h"
#include "lgui.h"
#include <gtk/gtk.h>

int main(int argc, char **argv) {
	gtk_init(&argc, &argv);

	GtkBuilder *builder = ltk_builder_new_from_data_path("bristolgui.glade");
	if (builder == NULL) {
		g_error("could not load gui definition");
	}

	lgui_switch_button_visible_connect(builder, "profile");
	lgui_switch_button_visible_connect(builder, "synth");
	lgui_switch_button_visible_connect(builder, "options");
	lgui_switch_button_visible_connect(builder, "runtimes");

	lgui_switch_check_button_sensitive_connect(builder, "engine");
	lgui_switch_check_button_sensitive_connect(builder, "midichannel");

	GtkWidget *window_root = ltk_builder_get_widget(builder, "window_root");
	gtk_widget_show_all(window_root);

	gtk_main();

	return 0;
}


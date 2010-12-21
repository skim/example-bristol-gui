#include "llib.h"
#include "ltk.h"
#include <gtk/gtk.h>

int main(int argc, char **argv) {
	gtk_init(&argc, &argv);

	GtkBuilder *builder = ltk_builder_new_from_data_path("bristolgui.glade");
	if (builder == NULL) {
		g_error("could not load gui definition");
	}
	GtkButton *switch_profile = ltk_builder_get_button(builder, "switch_profile");
	GtkWidget *box_profile = ltk_builder_get_widget(builder, "box_profile");
	ltk_switch_hide_connect(switch_profile, box_profile);

	GtkButton *check_engine = ltk_builder_get_button(builder, "check_midichannel");
	GtkWidget *box_engine = ltk_builder_get_widget(builder, "box_midichannel");
	ltk_switch_deactivate_connect(check_engine, box_engine);

	GtkWidget *window_root = ltk_builder_get_widget(builder, "window_root");
	gtk_widget_show_all(window_root);

	gtk_main();

	return 0;
}


#include "gui.h"
#include <lgui.h>

GtkBuilder* bg_prepare_gui(const char *filename) {
	GtkBuilder *builder = ltk_builder_new_from_data_path("bristolgui.glade");
	if (builder == NULL) {
		g_error("could not load gui definition");
	}

	PangoFontDescription *monospace = pango_font_description_new();
	pango_font_description_set_family(monospace, "monospace");
	gtk_widget_modify_font(ltk_builder_get_widget(builder, "text_command"), monospace);

	GtkWidget *window_root = ltk_builder_get_widget(builder, "window_root");
	g_signal_connect(window_root, "delete_event", G_CALLBACK(gtk_main_quit), NULL);

	ltk_switch_visible_connect(ltk_builder_get_button(builder, "switch_profile"), ltk_builder_get_widget(builder, "box_profile"));
	ltk_switch_visible_connect(ltk_builder_get_button(builder, "switch_synth"), ltk_builder_get_widget(builder, "box_synth"));
	ltk_switch_visible_connect(ltk_builder_get_button(builder, "switch_synth"), ltk_builder_get_widget(builder, "box_check_synth"));
	ltk_switch_visible_connect(ltk_builder_get_button(builder, "switch_options"), ltk_builder_get_widget(builder, "box_options"));
	ltk_switch_visible_connect(ltk_builder_get_button(builder, "switch_runtimes"), ltk_builder_get_widget(builder, "box_runtimes"));

	return builder;
}

#include "llib.h"
#include "ltk.h"
#include "lgui.h"
#include <gtk/gtk.h>

int main(int argc, char **argv) {

	LValueList *engines = l_value_list_new_string();
	l_value_list_put_value(engines, "JACK", l_value_new_string("jack"));
	l_value_list_put_value(engines, "ALSA", l_value_new_string("alsa"));
	l_value_list_put_value(engines, "OSS", l_value_new_string("oss"));

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
	lgui_switch_check_button_sensitive_connect(builder, "samplerate");

	GtkComboBox *combo_box = ltk_builder_get_combo_box(builder, "combo_engine");
	ltk_combo_box_fill(combo_box, engines);

	GtkWidget *window_root = lgui_builder_get_window(builder, "root");
	g_signal_connect(window_root, "delete_event", G_CALLBACK(gtk_main_quit), NULL);
	gtk_widget_show_all(window_root);

	gtk_main();

	return 0;
}


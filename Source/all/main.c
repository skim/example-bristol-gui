#include "llib.h"
#include "ltk.h"
#include "lgui.h"
#include <gtk/gtk.h>

int main(int argc, char **argv) {

	LOptionList *profile = l_option_list_new();
	l_option_list_put_option(profile, l_option_new_string("engine", NULL));
	l_option_list_put_option(profile, l_option_new_int("midichannel", "channel"));
	l_option_list_put_option(profile, l_option_new_int("samplerate", "rate"));

	l_option_list_set_value(profile, "engine", l_value_new_string("alsa"));

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

	LValueList *engines = l_value_list_new_string();
	l_value_list_put_value(engines, "JACK", l_value_new_string("jack"));
	l_value_list_put_value(engines, "ALSA", l_value_new_string("alsa"));
	l_value_list_put_value(engines, "OSS", l_value_new_string("oss"));


	GtkComboBox *combo_box = ltk_builder_get_combo_box(builder, "combo_engine");
	ltk_combo_box_fill(combo_box, engines);
	ltk_combo_box_connect_option(combo_box, profile, "engine");
	GtkToggleButton *check_engine = ltk_builder_get_toggle_button(builder, "check_engine");
	ltk_toggle_button_connect_option(check_engine, profile, "engine");

	LValueList *samplerates = l_value_list_new_int();
	l_value_list_put_value(samplerates, "11,025", l_value_new_int(11025));
	l_value_list_put_value(samplerates, "32,000", l_value_new_int(32000));
	l_value_list_put_value(samplerates, "44,100", l_value_new_int(44100));
	l_value_list_put_value(samplerates, "48,100", l_value_new_int(48000));

	GtkComboBox *combo_samplerate = ltk_builder_get_combo_box(builder, "combo_samplerate");
	ltk_combo_box_fill(combo_samplerate, samplerates);
	ltk_combo_box_set_active_value(combo_samplerate, l_value_new_int(44100));

	GtkWidget *window_root = lgui_builder_get_window(builder, "root");
	g_signal_connect(window_root, "delete_event", G_CALLBACK(gtk_main_quit), NULL);
	gtk_widget_show_all(window_root);

	gtk_main();

	return 0;
}


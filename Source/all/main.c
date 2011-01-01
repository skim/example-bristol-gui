#include <lgui.h>
#include <gtk/gtk.h>

static void bg_prepare_engine(GtkBuilder *builder, LOptionList *profile) {
	g_assert(builder != NULL);
	g_assert(profile != NULL);
	l_option_list_put_option(profile, l_option_new_string("engine", NULL));
	l_option_list_set_value(profile, "engine", l_value_new_string("alsa"));
	LValueList *engines = l_value_list_new_string();
	l_value_list_put_value(engines, "JACK", l_value_new_string("jack"));
	l_value_list_put_value(engines, "ALSA", l_value_new_string("alsa"));
	l_value_list_put_value(engines, "OSS", l_value_new_string("oss"));

	GtkComboBox *combo_box = ltk_builder_get_combo_box(builder, "combo_engine");
	ltk_combo_box_fill(combo_box, engines);
	ltk_switch_sensitive_connect(ltk_builder_get_button(builder, "check_engine"), ltk_builder_get_widget(builder, "box_engine"));
	ltk_combo_box_connect_to_option(combo_box, profile, "engine");

	GtkToggleButton *check_engine = ltk_builder_get_toggle_button(builder, "check_engine");
	ltk_toggle_button_connect_to_option(check_engine, profile, "engine");
}

static void bg_prepare_midichannel(GtkBuilder *builder, LOptionList *profile) {
	g_assert(builder != NULL);
	g_assert(profile != NULL);
	l_option_list_put_option(profile, l_option_new_int("midichannel", "channel"));
	l_option_list_set_value(profile, "midichannel", l_value_new_int(1));
	GtkAdjustment *adjustment = ltk_builder_get_adjustment(builder, "adjust_midichannel");
	ltk_switch_sensitive_connect(ltk_builder_get_button(builder, "check_midichannel"), ltk_builder_get_widget(builder, "box_midichannel"));
	ltk_adjustment_connect_to_option(adjustment, profile, "midichannel");
	GtkToggleButton *check_engine = ltk_builder_get_toggle_button(builder, "check_midichannel");
	ltk_toggle_button_connect_to_option(check_engine, profile, "midichannel");
}

static void bg_prepare_samplerate(GtkBuilder *builder, LOptionList *profile) {
	g_assert(builder != NULL);
	g_assert(profile != NULL);
	l_option_list_put_option(profile, l_option_new_int("samplerate", "rate"));
	l_option_list_set_value(profile, "samplerate", l_value_new_int(44100));
	LValueList *samplerates = l_value_list_new_int();
	l_value_list_put_value(samplerates, "11,025", l_value_new_int(11025));
	l_value_list_put_value(samplerates, "32,000", l_value_new_int(32000));
	l_value_list_put_value(samplerates, "44,100", l_value_new_int(44100));
	l_value_list_put_value(samplerates, "48,100", l_value_new_int(48000));
	GtkComboBox *combo_samplerate = ltk_builder_get_combo_box(builder, "combo_samplerate");
	ltk_combo_box_fill(combo_samplerate, samplerates);
	ltk_switch_sensitive_connect(ltk_builder_get_button(builder, "check_samplerate"), ltk_builder_get_widget(builder, "box_samplerate"));
	GtkToggleButton *check_samplerate = ltk_builder_get_toggle_button(builder, "check_samplerate");
	ltk_toggle_button_connect_to_option(check_samplerate, profile, "samplerate");
	GtkAdjustment *adjust_samplerate = ltk_builder_get_adjustment(builder, "adjust_samplerate");
	ltk_combo_box_connect_to_adjustment(combo_samplerate, adjust_samplerate);
	ltk_adjustment_connect_to_option(adjust_samplerate, profile, "samplerate");
	ltk_combo_box_set_active_value_from_option(combo_samplerate, profile, "samplerate");
}

int main(int argc, char **argv) {

	gtk_init(&argc, &argv);

	GtkBuilder *builder = ltk_builder_new_from_data_path("bristolgui.glade");
	if (builder == NULL) {
		g_error("could not load gui definition");
	}

	ltk_switch_visible_connect(ltk_builder_get_button(builder, "switch_profile"), ltk_builder_get_widget(builder, "box_profile"));
	ltk_switch_visible_connect(ltk_builder_get_button(builder, "switch_synth"), ltk_builder_get_widget(builder, "box_synth"));
	ltk_switch_visible_connect(ltk_builder_get_button(builder, "switch_options"), ltk_builder_get_widget(builder, "box_options"));
	ltk_switch_visible_connect(ltk_builder_get_button(builder, "switch_runtimes"), ltk_builder_get_widget(builder, "box_runtimes"));

	LOptionList *profile = l_option_list_new();
	bg_prepare_engine(builder, profile);
	bg_prepare_midichannel(builder, profile);
	bg_prepare_samplerate(builder, profile);

	GtkWidget *window_root = ltk_builder_get_widget(builder, "window_root");
	g_signal_connect(window_root, "delete_event", G_CALLBACK(gtk_main_quit), NULL);
	gtk_widget_show_all(window_root);

	gtk_main();

	return 0;
}


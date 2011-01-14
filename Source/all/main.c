#include <lgui.h>
#include "bg_session.h"
#include <gtk/gtk.h>

#define BG_DATA_PATH "./Data"

static GtkTextBuffer *buffer_command;

void bg_update_profile(LOptionList *profile, LOption *option, gpointer data) {
	g_debug("value changed for: %s", l_option_get_id(option));
	const char *cli = l_option_list_render_cli(profile, "startBristol ");
	gtk_text_buffer_set_text(buffer_command, cli, -1);
}

int main(int argc, char **argv) {

	l_set_data_path(BG_DATA_PATH);
	gtk_init(&argc, &argv);

	GtkBuilder *builder = ltk_builder_new_from_data_path("bristolgui.glade");
	if (builder == NULL) {
		g_error("could not load gui definition");
	}

	buffer_command = ltk_builder_get_text_buffer(builder, "buffer_command");
	g_assert(buffer_command != NULL);
	PangoFontDescription *monospace = pango_font_description_new();
	pango_font_description_set_family(monospace, "monospace");
	gtk_widget_modify_font(ltk_builder_get_widget(builder, "text_command"), monospace);

	GtkWidget *window_root = ltk_builder_get_widget(builder, "window_root");
	g_signal_connect(window_root, "delete_event", G_CALLBACK(gtk_main_quit), NULL);

	ltk_switch_visible_connect(ltk_builder_get_button(builder, "switch_profile"), ltk_builder_get_widget(builder, "box_profile"));
	ltk_switch_visible_connect(ltk_builder_get_button(builder, "switch_synth"), ltk_builder_get_widget(builder, "box_synth"));
	ltk_switch_visible_connect(ltk_builder_get_button(builder, "switch_options"), ltk_builder_get_widget(builder, "box_options"));
	ltk_switch_visible_connect(ltk_builder_get_button(builder, "switch_runtimes"), ltk_builder_get_widget(builder, "box_runtimes"));

	LValueList *engines = l_value_list_new_string();
	l_value_list_put_value(engines, "JACK", l_value_new_string("jack"));
	l_value_list_put_value(engines, "ALSA", l_value_new_string("alsa"));
	l_value_list_put_value(engines, "OSS", l_value_new_string("oss"));

	LValueList *samplerates = l_value_list_new_int();
	l_value_list_put_value(samplerates, "11,025 Hz - (1/4 Audio CD)", l_value_new_int(11025));
	l_value_list_put_value(samplerates, "22,050 Hz - (1/2 Audio CD)", l_value_new_int(22050));
	l_value_list_put_value(samplerates, "44,100 Hz - (Audio CD)", l_value_new_int(44100));
	l_value_list_put_value(samplerates, "48,000 Hz - (Video Standard)", l_value_new_int(48000));
	l_value_list_put_value(samplerates, "96,000 Hz - (DVD Audio)", l_value_new_int(96000));

	LOption *midichannel = l_option_new_int("midichannel", "channel");

	BgSession *session = bg_session_new(builder);

	LOptionList *profile = l_option_list_new();
	l_option_list_add_value_change_listener(profile, bg_update_profile, NULL);

	LValue *value_synth = l_value_new_string("minilongword");
	l_value_set_enabled(value_synth, TRUE);
	LValue *value_engine = l_value_list_nth_value(engines, 2);
	LValue *value_samplerate = l_value_list_nth_value(samplerates, 3);
	LValue *value_midichannel = l_value_new_int(1);

	l_option_list_insert_option(profile, l_option_new_string("synth", FALSE), value_synth);
	l_option_list_insert_option(profile, l_option_new_string("engine", NULL), value_engine);
	l_option_list_insert_option(profile, l_option_new_int("samplerate", "rate"), value_samplerate);
	l_option_list_insert_option(profile, l_option_new_int("midichannel", "channel"), value_midichannel);
	bg_session_insert_profile(session, "Default", profile);

	bg_session_register_combo_box(session, "engine", "combo_engine", engines);
	bg_session_register_enable_button(session, "engine", "check_engine", NULL);

	bg_session_register_adjustment(session, "midichannel", "adjust_midichannel");
	bg_session_register_enable_button(session, "midichannel", "check_midichannel", "box_midichannel");

	bg_session_register_combo_box(session, "samplerate", "combo_samplerate", samplerates);
	bg_session_register_enable_button(session, "samplerate", "check_samplerate", NULL);

	bg_session_set_active_profile(session, "Default");

	gtk_text_buffer_set_text(buffer_command, l_option_list_render_cli(profile, "startBristol "), -1);

	gtk_widget_show_all(window_root);
	gtk_main();

	return 0;
}


#include <lgui.h>
#include "bg_session.h"
#include <gtk/gtk.h>

#define BG_DATA_PATH "./Data"

static GtkTextBuffer *buffer_command = NULL;

void bg_buffer_command_update(GtkObject *object, gpointer data) {
	LOptionList *profile = (LOptionList*) data;
	g_assert(profile != NULL);
	const char *cli = l_option_list_render_cli(profile);
	g_debug("values: %d", l_option_list_length_values(profile));
	gtk_text_buffer_set_text(buffer_command, l_option_list_render_cli(profile), -1);
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

	ltk_switch_visible_connect(ltk_builder_get_button(builder, "switch_profile"), ltk_builder_get_widget(builder, "box_profile"));
	ltk_switch_visible_connect(ltk_builder_get_button(builder, "switch_synth"), ltk_builder_get_widget(builder, "box_synth"));
	ltk_switch_visible_connect(ltk_builder_get_button(builder, "switch_options"), ltk_builder_get_widget(builder, "box_options"));
	ltk_switch_visible_connect(ltk_builder_get_button(builder, "switch_runtimes"), ltk_builder_get_widget(builder, "box_runtimes"));

	BgSession *session = bg_session_new(builder);

	LOption *option_engine = l_option_new_string("engine", NULL);
	LValueList *engines = l_value_list_new_string();
	l_value_list_put_value(engines, "JACK", l_value_new_string("jack"));
	l_value_list_put_value(engines, "ALSA", l_value_new_string("alsa"));
	l_value_list_put_value(engines, "OSS", l_value_new_string("oss"));
	bg_session_add_option_combo_box(session, option_engine, engines, l_value_new_string("alsa"), "combo_engine", "check_engine", "box_engine");

	LOption *samplerate = l_option_new_int("samplerate", "rate");
	LValueList *samplerates = l_value_list_new_int();
	l_value_list_put_value(samplerates, "11,025 Hz - (1/4 Audio CD)", l_value_new_int(11025));
	l_value_list_put_value(samplerates, "22,050 Hz - (1/2 Audio CD)", l_value_new_int(22050));
	l_value_list_put_value(samplerates, "44,100 Hz - (Audio CD)", l_value_new_int(44100));
	l_value_list_put_value(samplerates, "48,000 Hz - (Video Standard)", l_value_new_int(48000));
	l_value_list_put_value(samplerates, "96,000 Hz - (DVD Audio)", l_value_new_int(96000));
	bg_session_add_option_combo_box(session, samplerate, samplerates, l_value_new_int(44000), "combo_samplerate", "check_samplerate", "box_samplerate");

	LOption *midichannel = l_option_new_int("midichannel", "channel");
	bg_session_add_option_adjustment(session, midichannel, l_value_new_int(1), "adjust_midichannel", "check_midichannel", "box_midichannel");

	bg_session_on_change_connect(session, G_CALLBACK(bg_buffer_command_update));

	bg_session_add_profile(session, "Default");
	bg_session_add_profile(session, "Other");
	bg_session_set_active_profile(session, "Other");

	GtkWidget *window_root = ltk_builder_get_widget(builder, "window_root");
	g_signal_connect(window_root, "delete_event", G_CALLBACK(gtk_main_quit), NULL);
	gtk_widget_show_all(window_root);

	gtk_main();

	return 0;
}


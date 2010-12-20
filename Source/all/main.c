#include "bg_common.h"
#include "bg_config.h"
#include "bg_gui.h"
#include "bg_session.h"
#include "bg_control.h"
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

		//[M] setting up session/ profiles
		BgProfile *profile = bg_profile_new("Default");
		BgSession *session = bg_session_new(profile);
		//defining flags for options
		bg_option_list_add_flag(profile->options, "midichannel", "channel");
		bg_option_list_add_flag(profile->options, "samplerate", "rate");
		bg_profile_add_option(profile, bg_option_new_string("engine", "oss"));
		//setting up combo list
		BgEntryList *engines = bg_entry_list_new();
		bg_entry_list_add_new(engines, "JACK", "jack");
		bg_entry_list_add_new(engines, "ALSA", "alsa");
		bg_entry_list_add_new(engines, "OSS", "oss");

		//[V] initializing/ connecting the gui
		bg_switch_button_init(builder, "profile");
		bg_switch_button_init(builder, "synth");
		bg_switch_button_init(builder, "options");
		bg_switch_button_init(builder, "runtimes");

		bg_combo_box_init(builder, "engine", engines, 0);
		bg_switch_check_button_init(builder, "engine", FALSE);
		bg_adjustment_set_value(builder, "midichannel", 1);
		bg_switch_check_button_init(builder, "midichannel", FALSE);
		bg_adjustment_set_value(builder, "samplerate", 44100);
		bg_switch_check_button_init(builder, "samplerate", FALSE);

		//[C] initializing/ connecting controllers
		bg_control_init(session, builder, "engine", "combo");
		bg_control_connect(session, builder, "engine", "combo");
		bg_control_init(session, builder, "midichannel", "adjust");
		bg_control_connect(session, builder, "midichannel", "adjust");
		bg_control_init(session, builder, "samplerate", "adjust");
		bg_control_connect(session, builder, "samplerate", "adjust");
		bg_control_before_start(session, builder);

		gtk_widget_show_all(window);
		gtk_main();
	}
	return 0;
}


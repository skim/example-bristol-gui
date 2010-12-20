#include "bg_common.h"
#include "bg_config.h"
#include "bg_gui.h"
#include "bg_session.h"
#include "bg_control.h"
#include <gtk/gtk.h>

void bg_options_configure(BgOptionList *options) {
	bg_option_list_add_config(options, bg_option_config_new("engine", "combo", NULL));
	bg_option_list_add_config(options, bg_option_config_new("midichannel", "adjust", "channel"));
	bg_option_list_add_config(options, bg_option_config_new("samplerate", "adjust", "rate"));
	bg_option_list_add_config(options, bg_option_config_new("synth", "special", NULL));
}

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
		bg_options_configure(profile->options);
		BgSession *session = bg_session_new(profile);
		bg_profile_add_option(profile, bg_option_new_string("engine", "oss"));
		bg_profile_add_option(profile, bg_option_new_int("midichannel", 1));
		bg_profile_add_option(profile, bg_option_new_string("synth", "mini"));

		BgProfile *alternative = bg_profile_new("Alternative Profile");
		bg_options_configure(alternative->options);
		bg_profile_add_option(alternative, bg_option_new_string("synth", "mini"));
		bg_profile_add_option(alternative, bg_option_new_string("engine", "jack"));
		bg_session_add_profile(session, alternative);
		//setting up combo lists
		BgEntryList *profiles = bg_session_get_profiles_as_entries(session);
		BgEntryList *engines = bg_entry_list_new();
		bg_entry_list_add_new(engines, "JACK", "jack");
		bg_entry_list_add_new(engines, "ALSA", "alsa");
		bg_entry_list_add_new(engines, "OSS", "oss");

		//[V] initializing/ connecting the gui
		bg_switch_button_init(builder, "profile");
		bg_switch_button_init(builder, "synth");
		bg_switch_button_init(builder, "options");
		bg_switch_button_init(builder, "runtimes");
		bg_combo_box_init(builder, "profile", profiles, 0);

		bg_combo_box_init(builder, "engine", engines, 0);
		bg_switch_check_button_init(builder, "engine", FALSE);
		bg_adjustment_set_value(builder, "midichannel", 1);
		bg_switch_check_button_init(builder, "midichannel", FALSE);
		bg_adjustment_set_value(builder, "samplerate", 44100);
		bg_switch_check_button_init(builder, "samplerate", FALSE);

		//[C] initializing/ connecting controllers
		bg_control_before_start(session, builder);

		gtk_widget_show_all(window);
		gtk_main();
	}
	return 0;
}


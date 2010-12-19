#include "bg_common.h"
#include "bg_config.h"
#include "bg_gui.h"
#include "bg_session.h"
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

		BgProfile *profile = bg_profile_new("Default");
		bg_profile_add_option(profile, bg_option_new_string("engine", FALSE, "alsa"));

		bg_gui_button_switch_prepare(builder, "profile");

		bg_gui_button_switch_prepare(builder, "synth");
		bg_gui_button_switch_prepare(builder, "options");
		bg_gui_button_switch_prepare(builder, "runtimes");

		BgEntryList *engines = bg_entry_list_new();
		bg_entry_list_add_new(engines, "JACK", "jack");
		bg_entry_list_add_new(engines, "ALSA", "alsa");
		bg_entry_list_add_new(engines, "OSS", "oss");
		bg_gui_combobox_init(builder, "engine", engines, 0);
		bg_gui_checkbox_switch_init(builder, "engine", FALSE);

		BgOption *option_engine = bg_profile_get_option(profile, "engine");
		if (option_engine != NULL) {
			bg_gui_combobox_set_active_value(builder, "engine", option_engine->value_string);
		}

		bg_gui_adjust_set_value(builder, "midichannel", 1);
		bg_gui_checkbox_switch_init(builder, "midichannel", FALSE);

		bg_gui_adjust_set_value(builder, "samplerate", 44100);
		bg_gui_checkbox_switch_init(builder, "samplerate", FALSE);

		gtk_widget_show_all(window);
		gtk_main();
	}
	return 0;
}


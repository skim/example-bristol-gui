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
		BgSession *session = bg_session_new(profile);

		bg_gui_prepare_switch(builder, "profile");

		bg_gui_prepare_switch(builder, "synth");
		bg_gui_prepare_switch(builder, "options");
		bg_gui_prepare_switch(builder, "runtimes");


		bg_gui_prepare_check(builder, "engine", TRUE);

		bg_gui_prepare_adjust(builder, "midichannel", 1);
		bg_gui_prepare_check(builder, "midichannel", FALSE);

		bg_gui_prepare_adjust(builder, "samplerate", 44100);
		bg_gui_prepare_check(builder, "samplerate", FALSE);

		gtk_widget_show_all(window);
		gtk_main();
	}
	return 0;
}


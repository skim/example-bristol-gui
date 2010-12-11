#include "bg_common_basic.h"
#include "bg_config.h"
#include "bg_option.h"
#include "bg_options_general.h"
#include <gtk/gtk.h>

void showcase_options() {
	//get choices from defaults
	BgOptionChoiceList *engines = bg_engine_choices_new();
	BgOptionChoiceList *synths =  bg_synth_choices_new();
	BgOptionChoiceList *general = bg_general_choices_new();

	//choose engine & synth
	BgOptionList *options = bg_option_list_new();
	bg_option_list_add(options, bg_option_choice_list_get(engines, 0));
	bg_option_list_add(options, bg_option_choice_list_get(synths, 1));

	//choose some options more
	bg_option_list_add(options, bg_option_choice_list_get(general, 0));
	bg_option_list_add(options, bg_option_choice_list_get(general, 1));

	//reconfigure some
	bg_int_option_set(bg_option_list_get(options, "channel"), 4);
	bg_int_option_set(bg_option_list_get(options, "rate"), 96000);

	//run
	BgCommand *startBristol = bg_command_new("startBristol", options);
	g_debug("%s", startBristol->command);
}

int main(int argc, char **argv) {
	showcase_options();
	gtk_init(&argc, &argv);
	GtkBuilder *builder = gtk_builder_new();
	GError *error = NULL;
	gtk_builder_add_from_file(builder, bg_make_path(BG_GLADE_FILE), &error);
	if (error != NULL) {
		g_error("Error: %s", error->message);
		return 1;
	} else {
		GtkWidget *window = GTK_WIDGET(gtk_builder_get_object(builder, "window_root"));
		gtk_widget_show_all(window);
		gtk_main();
	}
	return 0;
}


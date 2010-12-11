#include "bg_common_basic.h"
#include "bg_config.h"
#include "bg_option.h"
#include "bg_options_general.h"
#include <gtk/gtk.h>

int main(int argc, char **argv) {

	BgOptionChoiceList *engines = bg_engine_choices_new();
	BgOptionChoiceList *synths =  bg_synth_choices_new();

	BgOptionList *options = bg_option_list_new();
	bg_option_list_add(options, bg_option_choide_list_get(engines, 0));
	bg_option_list_add(options, bg_option_choide_list_get(synths, 1));

	BgCommand *startBristol = bg_command_new("startBristol", options);
	g_debug("%s", startBristol->command);

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


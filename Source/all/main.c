#include <lgui.h>
#include <gtk/gtk.h>
#include <string.h>
#include "bg_session.h"
#include "app_profile.h"
#include "app_session.h"


#define BG_DATA_PATH "./Data"

int main(int argc, char **argv) {
	gtk_init(&argc, &argv);
	l_set_data_path(BG_DATA_PATH);
	g_debug("data path: %s", BG_DATA_PATH);

	GtkBuilder *builder = ltk_builder_new_from_data_path("bristolgui.glade");
	if (builder == NULL) {
		g_error("could not load gui definition");
	}

	BgSession *session = bg_session_new(builder);
	app_session_prepare(session);
	app_profile_prepare_session(session);

	LOptionList *profile_default = app_profile_new();
	LOptionList *profile_other = l_option_list_new_from_option_list(profile_default);
	LOption *o = l_option_list_get_option(profile_other, "engine");
	g_assert(l_option_get_choices(o) != NULL);
	app_session_add_profile(session, "Default", profile_default);
	app_session_add_profile(session, "Other", profile_other);

	GtkWidget *window_root = ltk_builder_get_widget(builder, "window_root");
	g_signal_connect(window_root, "delete-event", G_CALLBACK(gtk_main_quit), NULL);
	gtk_widget_show_all(window_root);
	gtk_main();

	return 0;
}


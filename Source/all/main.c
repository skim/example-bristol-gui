#include <lgui.h>
#include "bg_session.h"
#include "profile.h"
#include "gui.h"
#include <gtk/gtk.h>
#include <stdlib.h>
#include <gc.h>

#define BG_DATA_PATH "./Data"

static void bg_start_profile(GtkButton *button, gpointer data) {
	BgSession *session = (BgSession*) data;
	g_assert(data != NULL);
	LOptionList *profile = bg_session_get_active_profile(session);
	g_assert(profile != NULL);
	const char *cli = l_option_list_render_cli(profile, "startBristol");
	GError *error = NULL;
	if (!g_spawn_command_line_async(cli, &error)) {
		g_warning("Could not start profile, reason: %s", error->message);
	}
}

int main(int argc, char **argv) {
	gtk_init(&argc, &argv);

	l_set_data_path(BG_DATA_PATH);
	g_debug("data path: %s", BG_DATA_PATH);


	GtkBuilder *builder = ltk_builder_new_from_data_path("bristolgui.glade");
	if (builder == NULL) {
		g_error("could not load gui definition");
	}

	BgSession *session = bg_create_session(builder);
	bg_session_insert_profile(session, "Default", bg_create_default_profile(session));
	bg_session_insert_profile(session, "Polyphonic", bg_create_default_profile(session));
	bg_prepare_gui(session);
	bg_session_set_active_profile(session, "Default");

	gtk_widget_show_all(ltk_builder_get_widget(builder, "window_root"));
	gtk_main();

	return 0;
}


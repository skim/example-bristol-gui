#include <lgui.h>
#include <lgui_test.h>
#include <gtk/gtk.h>
#include <string.h>
#include <stdlib.h>
#include "gui.h"
#include "session.h"
#include "profile.h"


#define BG_DATA_PATH "./Data"

static gboolean run_tests = FALSE;
static GOptionEntry entries[] = { { "tests", 't', 0, G_OPTION_ARG_NONE, &run_tests, "Run unit tests", NULL }, { NULL } };

int main(int argc, char **argv) {
	//command line arguments
	GError *error = NULL;
	GOptionContext *context;
	context = g_option_context_new("- a GUI for the bristol synthesizer emulation");
	g_option_context_add_main_entries(context, entries, "english");
	g_option_context_add_group(context, gtk_get_option_group(TRUE));
	if (!g_option_context_parse(context, &argc, &argv, &error)) {
		g_print("option parsing failed: %s\n", error->message);
		exit(1);
	}
	if (run_tests) {
		//run tests if arg is present
		lgui_test_init(&argc, &argv);
		g_debug("running tests...");
		int ex = lgui_test();
		g_debug("done");
		g_debug("strdups: %d", l_get_n_strdups());
		return ex;
	} else {
		//run bristolgui

		gtk_init(&argc, &argv);
		l_set_data_path(BG_DATA_PATH);
		g_debug("BG_DATA_PATH %s", BG_DATA_PATH);

		GtkBuilder *builder = ltk_builder_new_from_data_path("bristolgui.glade");
		bg_gui_connect(builder);
		LSession *session = bg_session_new();
		LProfile *profile = bg_profile_new();
		l_session_add_profile(session, "Default", profile);
		LProfile *poly = l_profile_copy(profile);
		l_profile_set_option_value_int(poly, "samplerate", 11025);
		l_profile_set_option_enabled(poly, "samplerate", TRUE);
		l_profile_set_option_enabled(poly, "engine", FALSE);
		l_profile_set_option_enabled(poly, "synth", TRUE);
		l_session_add_profile(session, "Polyphonic", poly);

		bg_session_connect(session, builder);

		bg_session_activate_profile(session, "Polyphonic", builder);

		GtkWidget *window_root = ltk_builder_get_widget(builder, "window_root");
		g_signal_connect(window_root, "delete-event", G_CALLBACK(gtk_main_quit), NULL);
		gtk_widget_show_all(window_root);
		gtk_main();
		g_debug("strdups: %d", l_get_n_strdups());
		return 0;
	}
	return 1;
}


#include <lgui.h>
#include <lgui_test.h>
#include <gtk/gtk.h>
#include <string.h>
#include <stdlib.h>

#define BG_DATA_PATH "./Data"

static gboolean run_tests = FALSE;

static GOptionEntry entries[] = { { "tests", 't', 0, G_OPTION_ARG_NONE, &run_tests, "Run unit tests", NULL }, { NULL } };

int main(int argc, char **argv) {
	GError *error = NULL;
	GOptionContext *context;
	context = g_option_context_new("- a GUI for the bristol synthesizer emulation");
	g_option_context_add_main_entries(context, entries, "english");
	g_option_context_add_group(context, gtk_get_option_group(TRUE));
	if (!g_option_context_parse(context, &argc, &argv, &error)) {
		g_print("option parsing failed: %s\n", error->message);
		exit(1);
	}
	gtk_init(&argc, &argv);
	if (run_tests) {
		g_debug("running lgui tests...");
		int ex = llib_test(&argc, &argv);
		g_debug("done");
		return ex;
	} else {
		l_set_data_path(BG_DATA_PATH);
		g_debug("BG_DATA_PATH %s", BG_DATA_PATH);
		return 0;
	}
	return 1;
}


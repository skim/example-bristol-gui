#include <lgui.h>
#include "bg_session.h"
#include "profile.h"
#include "gui.h"
#include <gtk/gtk.h>

#define BG_DATA_PATH "./Data"

static GtkTextBuffer *buffer_command;

static void bg_update_profile(LOptionList *profile, LOption *option, gpointer data) {
	const char *cli = l_option_list_render_cli(profile, "startBristol");
	gtk_text_buffer_set_text(buffer_command, cli, -1);
}

static void bg_start_profile(GtkButton *button, gpointer data) {
	BgSession *session = (BgSession*) data;
	g_assert(data != NULL);
	LOptionList *profile = bg_session_get_active_profile(session);
	g_assert(profile != NULL);
	const char *cli = l_option_list_render_cli(profile, "startBristol");
	GError *error;
	if (!g_spawn_command_line_async(cli, &error)) {
		g_warning("Could not start profile, reason: %s", error->message);
	}
}

static void bg_change_profile(LValue *value, gpointer data) {
	g_assert(value != NULL);
	BgSession *session = (BgSession*) data;
	g_assert(session != NULL);
	bg_session_set_active_profile(session, l_value_get_string(value));
	bg_update_profile(bg_session_get_active_profile(session), NULL, NULL);
	g_debug("changed profile: %s", l_value_get_string(value));
}

static void bg_new_profile(GtkButton *button, gpointer data) {
	BgSession *session = (BgSession*) data;
	g_assert(session != NULL);
	GtkDialog *dialog = ltk_builder_get_dialog(bg_session_get_builder(session), "dialog_profile_new");
	g_assert(dialog != NULL);
	int result = gtk_dialog_run(dialog);
	g_debug("result: %d", result);
	gtk_widget_hide(GTK_WIDGET(dialog));
}

int main(int argc, char **argv) {
	l_set_data_path(BG_DATA_PATH);
	g_debug("data path: %s", BG_DATA_PATH);

	gtk_init(&argc, &argv);

	GtkBuilder* builder = bg_prepare_gui("bristolgui.glade");
	BgSession *session = bg_create_session(builder);

	buffer_command = ltk_builder_get_text_buffer(builder, "buffer_command");
	g_signal_connect(ltk_builder_get_button(builder, "button_start"), "clicked", G_CALLBACK(bg_start_profile), session);

	GtkButton *button_profile_new = ltk_builder_get_button(builder, "button_profile_new");
	g_assert(button_profile_new != NULL);
	g_signal_connect(button_profile_new, "clicked", G_CALLBACK(bg_new_profile), session);

	LOptionList *profile = bg_create_default_profile();
	l_option_list_add_value_change_listener(profile, bg_update_profile, NULL);
	LOptionList *other_profile = bg_create_profile(profile);
	l_option_list_add_value_change_listener(other_profile, bg_update_profile, NULL);
	bg_session_insert_profile(session, "Default", profile);
	bg_session_insert_profile(session, "Other", other_profile);

	LValueList *profile_names = bg_session_get_profile_names(session);
	g_assert(l_value_list_length(profile_names) > 0);
	GtkComboBox *combo_profile = ltk_builder_get_combo_box(builder, "combo_profile");
	ltk_combo_box_fill(combo_profile, profile_names);
	LValue *selected_profile = l_value_new_from_value(l_value_list_nth_value(profile_names, 0));
	ltk_combo_box_connect_value(combo_profile, selected_profile);
	l_value_add_update_listener(selected_profile, bg_change_profile, session);

	bg_session_set_active_profile(session, "Default");

	bg_update_profile(profile, NULL, NULL);
	gtk_widget_show_all(ltk_builder_get_widget(builder, "window_root"));
	gtk_main();

	return 0;
}


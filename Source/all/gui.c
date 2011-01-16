#include "gui.h"
#include "bg_session.h"
#include "profile.h"
#include <lgui.h>

static void bg_new_profile(GtkButton *button, gpointer data) {
	BgSession *session = (BgSession*) data;
	g_assert(session != NULL);
	GtkDialog *dialog = ltk_builder_get_dialog(bg_session_get_builder(session), "dialog_profile_new");
	g_assert(dialog != NULL);
	int result = gtk_dialog_run(dialog);
	g_debug("result: %d", result);
	gtk_widget_hide(GTK_WIDGET(dialog));
}

static void bg_change_profile(LValue *value, gpointer data) {
	g_assert(value != NULL);
	BgSession *session = (BgSession*) data;
	g_assert(session != NULL);
	bg_session_set_active_profile(session, l_value_get_string(value));
	GtkTextBuffer *buffer_command = ltk_builder_get_text_buffer(bg_session_get_builder(session), "buffer_command");
	bg_update_profile(bg_session_get_active_profile(session), NULL, buffer_command);
	g_debug("changed profile: %s", l_value_get_string(value));
}

void bg_prepare_gui(BgSession *session) {
	g_assert(session != NULL);
	GtkBuilder *builder = bg_session_get_builder(session);

	PangoFontDescription *monospace = pango_font_description_new();
	pango_font_description_set_family(monospace, "monospace");
	gtk_widget_modify_font(ltk_builder_get_widget(builder, "text_command"), monospace);

	GtkWidget *window_root = ltk_builder_get_widget(builder, "window_root");
	g_signal_connect(window_root, "delete_event", G_CALLBACK(gtk_main_quit), NULL);

	ltk_switch_visible_connect(ltk_builder_get_button(builder, "switch_profile"), ltk_builder_get_widget(builder, "box_profile"));
	ltk_switch_visible_connect(ltk_builder_get_button(builder, "switch_synth"), ltk_builder_get_widget(builder, "box_synth"));
	ltk_switch_visible_connect(ltk_builder_get_button(builder, "switch_synth"), ltk_builder_get_widget(builder, "box_check_synth"));
	ltk_switch_visible_connect(ltk_builder_get_button(builder, "switch_options"), ltk_builder_get_widget(builder, "box_options"));
	ltk_switch_visible_connect(ltk_builder_get_button(builder, "switch_runtimes"), ltk_builder_get_widget(builder, "box_runtimes"));

	GtkButton *button_profile_new = ltk_builder_get_button(builder, "button_profile_new");
	g_assert(button_profile_new != NULL);
	g_signal_connect(button_profile_new, "clicked", G_CALLBACK(bg_new_profile), session);

	GtkComboBox *combo_profile = ltk_builder_get_combo_box(builder, "combo_profile");
	g_assert(combo_profile != NULL);
	LValueList *profiles = bg_session_get_profile_names(session);
	g_assert(profiles != NULL && l_value_list_length(profiles) > 0);
	LValue *profile_selected = l_value_new_from_value(l_value_list_nth_value(profiles, 0));
	ltk_combo_box_fill(combo_profile, profiles);
	ltk_combo_box_connect_value(combo_profile, profile_selected);
	l_value_add_update_listener(profile_selected, bg_change_profile, session);

	GtkDialog *dialog_profile_new = ltk_builder_get_dialog(builder, "dialog_profile_new");
	g_assert(dialog_profile_new != NULL);
}

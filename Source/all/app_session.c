#include "app_session.h"
#include "app_profile.h"
#include <string.h>

static void app_event_profile_selected(LValue *value, gpointer data) {
	g_assert(value != NULL);
	BgSession *session = (BgSession*) data;
	g_assert(session != NULL);
	bg_session_set_active_profile(session, l_value_get_string(value));
	g_debug("switched to profile: %s", l_value_get_string(value));
}

static void app_event_show_profile_new(GtkButton *button, gpointer data) {
	BgSession *session = (BgSession*) data;
	g_assert(session);
	GtkBuilder *builder =bg_session_get_builder(session);
	GtkDialog *dialog =  ltk_builder_get_dialog(builder, "dialog_profile_new");
	g_assert(dialog != NULL);
	GtkEntry *entry = ltk_builder_get_entry(builder, "entry_profile_name");
	g_assert(entry != NULL);
	gtk_entry_set_text(entry, "");
	int response = 0;
	while (response == 0) {
		gtk_widget_grab_focus(GTK_WIDGET(entry));
		response = gtk_dialog_run(dialog);
	}
	gtk_widget_hide(GTK_WIDGET(dialog));
}

typedef struct {
	BgSession *session;
	LValue *profile_selected;
} APpEventProfileNew;

static void app_event_profile_new(GtkButton *button, gpointer data) {
	APpEventProfileNew *event = (APpEventProfileNew*) data;
	g_assert(event != NULL);
	BgSession *session = event->session;
	g_assert(session != NULL);
	GtkBuilder *builder = bg_session_get_builder(session);
	GtkDialog *dialog = ltk_builder_get_dialog(builder, "dialog_profile_new");
	g_assert(dialog != NULL);
	GtkEntry *entry = ltk_builder_get_entry(builder, "entry_profile_name");
	g_assert(entry != NULL);
	const char *name = gtk_entry_get_text(entry);
	int response = 0;
	if (name == NULL || strlen(name) == 0) {
		ltk_message_error(GTK_WINDOW(dialog), "The profile could not be created", "Please enter a name for the profile.");
	} else if (bg_session_has_profile(session, name)) {
		ltk_message_error(GTK_WINDOW(dialog), "The profile could not be created", "A profile with that name already exists.");
	} else {
		LOptionList *profile = app_profile_new();
		app_session_add_profile(session, g_strdup(name), profile);
		l_value_set_string(event->profile_selected, name);
		response = 1;
	}
	gtk_dialog_response(dialog, response);
}

static void app_event_dialog_cancel(GtkButton *button, gpointer data) {
	GtkDialog *dialog = GTK_DIALOG(data);
	g_assert(dialog != NULL);
	gtk_dialog_response(dialog, 1);
}

void app_session_prepare(BgSession *session) {
	g_assert(session != NULL);
	GtkBuilder *builder = bg_session_get_builder(session);
	//switch profile
	LValue *profile_selected = l_value_new_string(NULL);
	GtkComboBox *combo_profile = ltk_builder_get_combo_box(bg_session_get_builder(session), "combo_profile");
	g_assert(combo_profile != NULL);
	ltk_combo_box_fill(combo_profile, l_value_list_new_string());
	ltk_combo_box_connect_value(combo_profile, profile_selected);
	l_value_add_update_listener(profile_selected, app_event_profile_selected, session);
	//show new profile dialog
	GtkButton *button_profile_new = ltk_builder_get_button(builder, "button_profile_new");
	g_assert(button_profile_new != NULL);
	g_signal_connect(button_profile_new, "clicked", G_CALLBACK(app_event_show_profile_new), session);
	//create new profile
	GtkButton *button_profile_new_ok = ltk_builder_get_button(builder, "button_profile_new_ok");
	g_assert(button_profile_new_ok != NULL);
	APpEventProfileNew *event_new = g_new(APpEventProfileNew, 1);
	event_new->session = session;
	event_new->profile_selected = profile_selected;
	g_signal_connect(button_profile_new_ok, "clicked", G_CALLBACK(app_event_profile_new), event_new);
	GtkButton *button_profile_new_cancel = ltk_builder_get_button(builder, "button_profile_new_cancel");
	g_assert(button_profile_new_cancel != NULL);
	g_signal_connect(button_profile_new_cancel, "clicked", G_CALLBACK(app_event_dialog_cancel), ltk_builder_get_dialog(builder, "dialog_profile_new"));
}

void app_session_add_profile(BgSession *session, const char *name, LOptionList *profile) {
	g_assert(session != NULL);
	g_assert(name != NULL && strlen(name) > 0);
	g_assert(profile != NULL);
	g_assert(!bg_session_has_profile(session, name));
	bg_session_insert_profile(session, name, profile);
	GtkComboBox *combo_profile = ltk_builder_get_combo_box(bg_session_get_builder(session), "combo_profile");
	g_assert(combo_profile != NULL);
	ltk_combo_box_fill(combo_profile, bg_session_get_profile_names(session));
}

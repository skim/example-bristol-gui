#include "bg_session.h"
#include <string.h>
#include <lgui.h>

#define BG_SESSION_ID_KEY "bg_option_id"

struct _BgSession {
	GtkBuilder *builder;
	GHashTable *profiles;
	LValueList *profile_names;
	GHashTable *widgets;
	GHashTable *enable_buttons;
	char *active_profile;
};

BgSession* bg_session_new(GtkBuilder *builder) {
	g_assert(builder != NULL);
	BgSession *session = g_new(BgSession, 1);
	session->builder = builder;
	session->profiles = g_hash_table_new(g_str_hash, g_str_equal);
	session->profile_names = l_value_list_new_string();
	session->widgets = g_hash_table_new(g_str_hash, g_str_equal);
	session->enable_buttons = g_hash_table_new(g_str_hash, g_str_equal);
	session->active_profile = NULL;
	g_debug("new session");
	return session;
}

LOptionList* bg_session_get_profile(BgSession *session, const char *name) {
	g_assert(session != NULL);
	g_assert(name != NULL && strlen(name) > 0);
	return (LOptionList*) g_hash_table_lookup(session->profiles, name);
}

LOptionList* bg_session_get_active_profile(BgSession *session) {
	g_assert(session != NULL);
	if (session->active_profile == NULL) {
		return NULL;
	} else {
		return (LOptionList*) g_hash_table_lookup(session->profiles, g_strdup(session->active_profile));
	}
}

void bg_session_set_active_profile(BgSession *session, const char *name) {
	g_assert(session != NULL);
	g_assert(name != NULL && strlen(name) > 0);
	LOptionList *profile = bg_session_get_profile(session, name);
	if (profile == NULL) {
		g_warning("no profile for name: %s", name);
	} else {
		session->active_profile = g_strdup(name);
		g_debug("set active profile: %s", name);
	}
}

void bg_session_insert_profile(BgSession *session, const char *name, LOptionList *profile) {
	g_assert(session != NULL);
	g_assert(name != NULL && strlen(name) > 0);
	g_assert(profile != NULL);
	if (bg_session_get_profile(session, name)) {
		g_warning("a profile with the name %s already exists", name);
	} else {
		g_hash_table_insert(session->profiles, g_strdup(name), profile);
		l_value_list_put_value(session->profile_names, name, l_value_new_string(name));
		g_debug("inserted profile: %s", name);
		if (bg_session_get_active_profile(session) == NULL) {
			bg_session_set_active_profile(session, name);
		}
	}
}

void bg_session_register_combo_box(BgSession *session, const char *option_name, const char *widget_name, LValueList *filling) {
	g_assert(session != NULL);
	g_assert(option_name != NULL && strlen(option_name) > 0);
	g_assert(widget_name != NULL && strlen(widget_name) > 0);
	g_assert(filling != NULL);
	GtkComboBox *combo = ltk_builder_get_combo_box(session->builder, widget_name);
	g_assert(combo != NULL);
	ltk_combo_box_fill(combo, filling);
	g_hash_table_insert(session->widgets, g_strdup(option_name), combo);
	g_debug("registered combo box: %s to option: %s", widget_name, option_name);
}

void bg_session_register_adjustment(BgSession *session, const char *option_name, const char *widget_name) {
	g_assert(session != NULL);
	g_assert(option_name != NULL && strlen(option_name) > 0);
	g_assert(widget_name != NULL && strlen(widget_name) > 0);
	GtkAdjustment *adjust = ltk_builder_get_adjustment(session->builder, widget_name);
	g_assert(adjust != NULL);
	g_hash_table_insert(session->widgets, g_strdup(option_name), adjust);
	g_debug("registered adjustment: %s for option: %s", widget_name, option_name);
}

void bg_session_register_enable_button(BgSession *session, const char *option_name, const char *button_name, const char *widget_to_toggle) {
	g_assert(session != NULL);
	g_assert(option_name != NULL && strlen(option_name) > 0);
	g_assert(button_name != NULL && strlen(button_name) > 0);
	g_assert(widget_to_toggle == NULL || strlen(widget_to_toggle) > 0);
	GtkButton *toggle = ltk_builder_get_button(session->builder, button_name);
	g_assert(toggle != NULL);
	GtkWidget *widget = NULL;
	if (widget_to_toggle != NULL) {
		widget = ltk_builder_get_widget(session->builder, widget_to_toggle);
	} else {
		widget = GTK_WIDGET(g_hash_table_lookup(session->widgets, option_name));
	}
	g_assert(widget != NULL);
	ltk_switch_sensitive_connect(toggle, widget);
	g_hash_table_insert(session->enable_buttons, g_strdup(option_name), toggle);
	g_debug("registered toggle: %s for option: %s", button_name, option_name);
}

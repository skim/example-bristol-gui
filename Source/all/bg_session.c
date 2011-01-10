#include "bg_session.h"
#include <string.h>
#include <lgui.h>

#define BG_OPTION_KEY_WIDGET "BGWIDGET"

struct _BgSession {
	LOptionList *base_profile;
	char *active_profile;
	GHashTable *profiles;
	GtkBuilder *builder;
};

BgSession* bg_session_new(GtkBuilder *builder) {
	g_assert(builder != NULL);
	BgSession *session = g_new(BgSession, 1);
	session->profiles = g_hash_table_new(g_str_hash, g_str_equal);
	session->builder = builder;
	session->base_profile = l_option_list_new();
	return session;
}

void bg_session_set_active_profile(BgSession *session, const char *profile_name) {
	g_assert(session != NULL);
	g_assert(profile_name != NULL);
	if (g_hash_table_lookup(session->profiles, profile_name) != NULL) {
		session->active_profile = g_strdup(profile_name);
	} else {
		g_warning("could not activate profile: %s, profile not found", profile_name);
	}
}

LOptionList* bg_session_get_active_profile(BgSession *session) {
	g_assert(session != NULL);
	g_assert(session->active_profile != NULL && strlen(session->active_profile) > 0);
	return (LOptionList*) g_hash_table_lookup(session->profiles, session->active_profile);
}

static void bg_session_connect_toggle(BgSession *session, const char *toggle_name, const char *con_name) {
	if (toggle_name != NULL) {
		GtkToggleButton *toggle = ltk_builder_get_toggle_button(session->builder, toggle_name);
		GtkWidget *widget = ltk_builder_get_widget(session->builder, con_name);
		g_assert(toggle != NULL);
		g_assert(widget != NULL);
		ltk_switch_sensitive_connect(GTK_BUTTON(toggle), widget);
	}
}

static void bg_session_add_option(BgSession *session, LOption *option) {
	g_assert(session != NULL);
	g_assert(option != NULL);
	l_option_list_put_option(session->base_profile, option);
}

void bg_session_add_option_combo_box(BgSession *session, LOption *option, LValueList *choices, const char *combo_name, const char *toggle_name,
		const char *con_name) {
	g_assert(session != NULL);
	g_assert(option != NULL);
	g_assert(choices != NULL);
	g_assert(combo_name != NULL && strlen(combo_name) > 1);
	bg_session_add_option(session, option);
	GtkComboBox *combo = ltk_builder_get_combo_box(session->builder, combo_name);
	g_assert(combo != NULL);
	ltk_combo_box_fill(combo, choices);
	bg_session_connect_toggle(session, toggle_name, con_name);
	l_option_put_data(option, BG_OPTION_KEY_WIDGET, "combo");
}

void bg_session_add_option_adjustment(BgSession *session, LOption *option, const char *adjust_name, const char *toggle_name,
		const char *con_name) {
	g_assert(session != NULL);
	g_assert(option != NULL);
	g_assert(adjust_name != NULL && strlen(adjust_name) > 1);
	bg_session_add_option(session, option);
	GtkAdjustment *adjust = ltk_builder_get_adjustment(session->builder, adjust_name);
	g_assert(adjust != NULL);
	bg_session_connect_toggle(session, toggle_name, con_name);
	l_option_put_data(option, BG_OPTION_KEY_WIDGET, "adjust");
}

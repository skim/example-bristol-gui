#include "bg_session.h"
#include <string.h>
#include <lgui.h>

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

LOptionList* bg_session_get_active_profile(BgSession *session) {
	g_assert(session != NULL);
	if (session->active_profile == NULL) {
		return NULL;
	} else {
		return (LOptionList*) g_hash_table_lookup(session->profiles, g_strdup(session->active_profile));
	}
}

static void bg_session_disconnect_option(BgSession *session, const char *option_name) {
	g_assert(session != NULL);
	g_assert(option_name != NULL && strlen(option_name) > 0);
	LOptionList *profile = bg_session_get_active_profile(session);
	g_assert(profile != NULL);
	LValue *value = l_option_list_get_value(profile, option_name);
	if (value == NULL) {
		g_warning("in profile: %s: no value found for option: %s\ninstead of providing no value, set a default value, it will be disabled by default", session->active_profile, option_name);
	} else {
		GtkButton *toggle = GTK_BUTTON(g_hash_table_lookup(session->enable_buttons, option_name));
		if (toggle != NULL) {
			ltk_switch_disconnect_enable_value(toggle, value);
			g_debug("disconnected enable toggle for option: %s", option_name);
		}
		GtkObject *widget = g_hash_table_lookup(session->widgets, option_name);
		if (widget == NULL) {
			g_warning("no widget registered for option: %s", option_name);
		} else {
			if (GTK_IS_COMBO_BOX(widget)) {
				ltk_combo_box_disconnect_value(GTK_COMBO_BOX(widget), value);
				g_debug("disconnected combo box to option: %s", option_name);
			} else if (GTK_IS_ADJUSTMENT(widget)) {
				ltk_adjustment_disconnect_value(GTK_ADJUSTMENT(widget), value);
				g_debug("disconnected adjustment to option: %s", option_name);
			}
		}
		g_debug("disconnected option: %s", option_name);
	}
}

static void bg_session_connect_option(BgSession *session, const char *option_name) {
	g_assert(session != NULL);
	g_assert(option_name != NULL && strlen(option_name) > 0);
	LOptionList *profile = bg_session_get_active_profile(session);
	g_assert(profile != NULL);
	LValue *value = l_option_list_get_value(profile, option_name);
	if (value == NULL) {
		g_warning("in profile: %s: no value found for option: %s\ninstead of providing no value, set a default value, it will be disabled by default", session->active_profile, option_name);
	} else {
		GtkButton *toggle = GTK_BUTTON(g_hash_table_lookup(session->enable_buttons, option_name));
		if (toggle != NULL) {
			ltk_switch_connect_enable_value(toggle, value);
			g_debug("connected enable toggle for option: %s", option_name);
		}
		GtkObject *widget = g_hash_table_lookup(session->widgets, option_name);
		if (widget == NULL) {
			g_warning("no widget registered for option: %s", option_name);
		} else {
			if (GTK_IS_COMBO_BOX(widget)) {
				ltk_combo_box_connect_value(GTK_COMBO_BOX(widget), value);
				g_debug("connected combo box to option: %s", option_name);
			} else if (GTK_IS_ADJUSTMENT(widget)) {
				ltk_adjustment_connect_value(GTK_ADJUSTMENT(widget), value);
				g_debug("connected adjustment to option: %s", option_name);
			}
		}
		g_debug("connected option: %s", option_name);
	}
}

static void bg_session_disconnect_active_profile(BgSession *session) {
	g_assert(session != NULL);
	LOptionList *profile = bg_session_get_active_profile(session);
	g_assert(profile != NULL);
	GList *option_keys = l_option_list_get_option_ids(profile);
	int i;
	for (i = 0; i < g_list_length(option_keys); i++) {
		bg_session_disconnect_option(session, (char*) g_list_nth_data(option_keys, i));
	}
}

static void bg_session_connect_active_profile(BgSession *session) {
	g_assert(session != NULL);
	LOptionList *profile = bg_session_get_active_profile(session);
	g_assert(profile != NULL);
	GList *option_keys = l_option_list_get_option_ids(profile);
	int i;
	for (i = 0; i < g_list_length(option_keys); i++) {
		bg_session_connect_option(session, (char*) g_list_nth_data(option_keys, i));
	}
}

void bg_session_set_active_profile(BgSession *session, const char *name) {
	g_assert(session != NULL);
	g_assert(name != NULL && strlen(name) > 0);
	LOptionList *profile = bg_session_get_profile(session, name);
	if (profile == NULL) {
		g_warning("no profile for name: %s", name);
	} else {
		LOptionList *profile = bg_session_get_active_profile(session);
		if (profile != NULL) {
			bg_session_disconnect_active_profile(session);
		}
		session->active_profile = g_strdup(name);
		g_debug("set active profile: %s", name);
		bg_session_connect_active_profile(session);
	}
}

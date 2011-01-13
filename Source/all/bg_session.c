#include "bg_session.h"
#include <string.h>
#include <lgui.h>

typedef struct {
	GtkObject *widget;
	GList *on_change_funcs;
} BgOptionData;

struct _BgSession {
	LOptionList *base_profile;
	GHashTable *option_data;
	char *active_profile;
	GHashTable *profiles;
	GtkBuilder *builder;
};

BgOptionData* bg_option_data_new(GtkObject *widget) {
	g_assert(widget != NULL);
	BgOptionData *data = g_new(BgOptionData, 1);
	data->widget = widget;
	data->on_change_funcs = NULL;
	return data;
}

BgSession* bg_session_new(GtkBuilder *builder) {
	g_assert(builder != NULL);
	BgSession *session = g_new(BgSession, 1);
	session->profiles = g_hash_table_new(g_str_hash, g_str_equal);
	session->option_data = g_hash_table_new(g_str_hash, g_str_equal);
	session->builder = builder;
	session->base_profile = l_option_list_new();
	session->active_profile = NULL;
	return session;
}

LOptionList* bg_session_get_profile(BgSession *session, const char *name) {
	g_assert(session != NULL);
	g_assert(name != NULL && strlen(name) > 0);
	return (LOptionList*) g_hash_table_lookup(session->profiles, name);
}

static LOptionList* bg_session_new_profile(BgSession *session) {
	g_assert(session != NULL);
	LOptionList *profile = l_option_list_new();
	int i;
	for (i = 0; i < l_option_list_length_options(session->base_profile); i++) {
		LOption *source_option = l_option_list_nth_option(session->base_profile, i);
		l_option_list_insert_option(profile, l_option_new_from_option(source_option));
	}
	g_debug("created new profile with %d options", i);
	return profile;
}

void bg_session_add_profile(BgSession *session, const char *name) {
	g_assert(session != NULL);
	g_assert(name != NULL && strlen(name) > 0);
	if (bg_session_get_profile(session, name) != NULL) {
		g_warning("not adding profile %s, profile exists already", name);
	} else {
		g_hash_table_insert(session->profiles, g_strdup(name), bg_session_new_profile(session));
		g_debug("added profile %s", name);
		if (bg_session_get_active_profile(session) == NULL) {
			bg_session_set_active_profile(session, name);
		}
	}
}

static void bg_session_connect_active_profile(BgSession *session) {
	g_assert(session != NULL);
	LOptionList *profile = bg_session_get_active_profile(session);
	g_assert(profile != NULL);
	if (profile != NULL) {
		GList *keys = g_hash_table_get_keys(session->option_data);
		int i;
		for (i = 0; i < g_list_length(keys); i++) {
			BgOptionData *data = g_hash_table_lookup(session->option_data, g_list_nth_data(keys, i));
			int j;
			for (j = 0; j < g_list_length(data->on_change_funcs); j++) {
				GCallback func = (GCallback) g_list_nth_data(data->on_change_funcs, j);
				if (GTK_IS_ADJUSTMENT(data->widget)) {
					g_signal_connect(data->widget, "value-changed", G_CALLBACK(func), profile);
				} else if (GTK_IS_COMBO_BOX(data->widget)) {
					g_signal_connect(data->widget, "changed", G_CALLBACK(func), profile);
				}
			}
		}
		g_debug("connected profile %s to %d widgets", session->active_profile, i);
	}
}

static void bg_session_disconnect_active_profile(BgSession *session) {
	g_assert(session != NULL);
	LOptionList *profile = bg_session_get_active_profile(session);
	if (profile != NULL) {
		GList *keys = g_hash_table_get_keys(session->option_data);
		int i;
		for (i = 0; i < g_list_length(keys); i++) {
			BgOptionData *data = g_hash_table_lookup(session->option_data, g_list_nth_data(keys, i));
			if (g_list_length(data->on_change_funcs) > 0) {
				gtk_signal_disconnect_by_data(data->widget, profile);
			}
		}
		g_debug("disconnected profile %s from %d widgets", session->active_profile, i);
	}
}

void bg_session_set_active_profile(BgSession *session, const char *name) {
	g_assert(session != NULL);
	g_assert(name != NULL);
	if (g_hash_table_lookup(session->profiles, name) != NULL) {
		bg_session_disconnect_active_profile(session);
		session->active_profile = g_strdup(name);
		bg_session_connect_active_profile(session);
		g_debug("activated profile %s", name);
	} else {
		g_warning("could not activate profile: %s, profile not found", name);
	}
}

LOptionList* bg_session_get_active_profile(BgSession *session) {
	g_assert(session != NULL);
	if (session->active_profile == NULL) {
		return NULL;
	} else {
		return (LOptionList*) g_hash_table_lookup(session->profiles, session->active_profile);
	}
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
	l_option_list_insert_option(session->base_profile, option);
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
	BgOptionData *data = bg_option_data_new(GTK_OBJECT(combo));
	g_hash_table_insert(session->option_data, g_strdup(l_option_get_id(option)), data);
}

void bg_session_add_option_adjustment(BgSession *session, LOption *option, const char *adjust_name, const char *toggle_name, const char *con_name) {
	g_assert(session != NULL);
	g_assert(option != NULL);
	g_assert(adjust_name != NULL && strlen(adjust_name) > 1);
	bg_session_add_option(session, option);
	GtkAdjustment *adjust = ltk_builder_get_adjustment(session->builder, adjust_name);
	g_assert(adjust != NULL);
	bg_session_connect_toggle(session, toggle_name, con_name);
	BgOptionData *data = bg_option_data_new(GTK_OBJECT(adjust));
	g_hash_table_insert(session->option_data, g_strdup(l_option_get_id(option)), data);
}

void bg_session_on_change_connect(BgSession *session, GCallback func) {
	g_assert(session != NULL);
	g_assert(func != NULL);
	GList *keys = g_hash_table_get_keys(session->option_data);
	int i;
	for (i = 0; i < g_list_length(keys); i++) {
		BgOptionData *data = g_hash_table_lookup(session->option_data, g_list_nth_data(keys, i));
		data->on_change_funcs = g_list_append(data->on_change_funcs, func);
	}
	g_debug("added on_change func to %d options", i);
}

#include "session.h"
#include "profile.h"
#include <string.h>

typedef struct {
	LSession *session;
	GtkBuilder *builder;
} BgProfileSelectData;

LSession* bg_session_new() {
	LSession *session = l_session_new();
	return session;
}

static void bg_session_combo_activate_profile(GtkComboBox *box, gpointer data) {
	BgProfileSelectData *odata = (BgProfileSelectData*) data;
	g_assert(data != NULL);
	int i = gtk_combo_box_get_active(box);
	char *name = (char*)g_list_nth_data(l_session_get_profile_names(odata->session), i);
	g_assert(name != NULL);
	bg_session_activate_profile(odata->session, name, odata->builder);
}

LSession* bg_session_connect(LSession *session, GtkBuilder *builder) {
	g_assert(session != NULL);
	g_assert(builder != NULL);
	GtkComboBox *combo = ltk_builder_get_combo_box(builder, "combo_profile");
	g_assert(combo != NULL);
	ltk_combo_box_set_cell_renderer_text(combo);
	GList *names = l_session_get_profile_names(session);
	g_assert(g_list_length(names) > 0);
	ltk_combo_box_set_choices_string(combo, names);
}


void bg_session_activate_profile(LSession *session, const char *name, GtkBuilder *builder) {
	g_assert(session != NULL);
	g_assert(name != NULL && strlen(name) > 0);
	g_assert(l_session_has_profile(session, name));
	if (l_session_get_selected_profile(session) != NULL) {
		bg_profile_disconnect(l_session_get_selected_profile(session), builder);
	}
	l_session_select_profile(session, name);
	bg_profile_connect(l_session_get_selected_profile(session), builder);
	GtkComboBox *combo = ltk_builder_get_combo_box(builder, "combo_profile");
	g_assert(combo != NULL);
	if (ltk_is_signal_registered(combo, BG_SIGNAL_SESSION_ACTIVATE_PROFILE)) {
		gpointer data = ltk_disconnect_signal(combo, BG_SIGNAL_SESSION_ACTIVATE_PROFILE);
		g_free(data);
		g_assert(!ltk_is_signal_registered(combo, BG_SIGNAL_SESSION_ACTIVATE_PROFILE));
	}
	GList *names = l_session_get_profile_names(session);
	g_assert(g_list_length(names) > 0);
	gtk_combo_box_set_active(combo, l_list_index(names, l_session_get_selected_profile_name(session), l_string_compare));
	BgProfileSelectData *data = g_new(BgProfileSelectData, 1);
	data->session = session;
	data->builder = builder;
	LSid sid = g_signal_connect(combo, "changed", G_CALLBACK(bg_session_combo_activate_profile), data);
	ltk_register_signal(combo, BG_SIGNAL_SESSION_ACTIVATE_PROFILE, sid, data);
}

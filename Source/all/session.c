#include "session.h"
#include "profile.h"

LSession* bg_session_new() {
	LSession *session = l_session_new();
	l_session_add_profile(session, "Default", bg_profile_new());
	l_session_select_profile(session, "Default");
	return session;
}

LSession* bg_session_connect(LSession *session, GtkBuilder *builder) {
	g_assert(session != NULL);
	g_assert(builder != NULL);
	LProfile *profile = l_session_get_selected_profile(session);
	g_assert(profile != NULL);
	GtkComboBox *combo = ltk_builder_get_combo_box(builder, "combo_profile");
	ltk_combo_box_set_cell_renderer_text(combo);
	GList *names = l_session_get_profile_names(session);
	ltk_combo_box_set_choices_string(combo, names);
	gtk_combo_box_set_active(combo, l_list_index(names, l_session_get_selected_profile_name(session), l_string_compare));
	bg_profile_connect(profile, builder);
}

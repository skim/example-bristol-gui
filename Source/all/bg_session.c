#include "bg_session.h"
#include "bg_config.h"

BgSession* bg_session_new(BgProfile *profile) {
	g_assert(profile != NULL);
	BgSession *session = g_new(BgSession, 1);
	session->profiles = NULL;
	session->profiles = g_list_append(session->profiles, profile);
	session->index_profile = 0;
	return session;
}

BgProfile* bg_session_get_active_profile(BgSession *session) {
	return (BgProfile*) g_list_nth_data(session->profiles, session->index_profile);
}

BgProfile* bg_profile_new(const char *name) {
	BgProfile *profile = g_new(BgProfile, 1);
	profile->name = g_strdup(name);
	profile->options = bg_option_list_new();
	return profile;
}

void bg_profile_add_option(BgProfile *profile, BgOption *option) {
	bg_option_list_add(profile->options, option);
}

BgOption* bg_profile_get_option(BgProfile *profile, const char *id) {
	return bg_option_list_get(profile->options, id);
}

void bg_profile_remove_option(BgProfile *profile, const char *id) {
	BgOption *option = bg_option_list_get(profile->options, id);
	if (option == NULL) {
		g_warning("option %s does not exist for this profile", id);
	} else {
		bg_option_list_remove(profile->options, option);
	}
}

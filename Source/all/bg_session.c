#include "bg_session.h"

BgSession* bg_session_new(BgProfile *profile) {
	g_assert(profile != NULL);
	BgSession *session = g_new(BgSession, 1);
	session->profiles = NULL;
	session->profiles = g_list_append(session->profiles, profile);
	session->index_profile = 0;
	return session;
}

BgProfile* bg_profile_new(const char *name) {
	BgProfile *profile = g_new(BgProfile, 1);
	profile->name = g_strdup(name);
	return profile;
}


#ifndef BG_SESSION_H_
#define BG_SESSION_H_

#include <glib.h>
#include "bg_common.h"

typedef struct {
	char *name;
	BgOptionList *options;
} BgProfile;

typedef struct {
	GList *profiles;
	int index_profile;
} BgSession;

BgSession* 		bg_session_new(BgProfile *profile);
BgProfile* 		bg_session_get_active_profile(BgSession *session);
BgProfile* 		bg_profile_new(const char *name);
void			bg_profile_add_option(BgProfile *profile, BgOption *option);
BgOption* 		bg_profile_get_option(BgProfile *profile, const char *id);
void			bg_profile_remove_option(BgProfile *profile, const char *id);

#endif /* BG_SESSION_H_ */

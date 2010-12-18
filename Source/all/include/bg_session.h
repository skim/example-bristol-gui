#ifndef BG_SESSION_H_
#define BG_SESSION_H_

#include <glib.h>
#include "bg_common.h"


typedef struct {
	char *name;
} BgProfile;

typedef struct {
	GList *profiles;
	int index_profile;
} BgSession;

BgSession* bg_session_new(BgProfile *profile);
BgProfile* bg_profile_new(const char *name);

#endif /* BG_SESSION_H_ */

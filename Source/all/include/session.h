#ifndef SESSION_H_
#define SESSION_H_

#include <lgui.h>

#define BG_SIGNAL_SESSION_ACTIVATE_PROFILE "bg_signal_session_activate_profile"

LSession* bg_session_new				();
LSession* bg_session_connect			(LSession *session, GtkBuilder *builder);
void 	 bg_session_activate_profile	(LSession *session, const char *name, GtkBuilder *builder);

#endif /* SESSION_H_ */

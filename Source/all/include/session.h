#ifndef SESSION_H_
#define SESSION_H_

#include <lgui.h>

LSession* bg_session_new();
LSession* bg_session_connect(LSession *session, GtkBuilder *builder);

#endif /* SESSION_H_ */

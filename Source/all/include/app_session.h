#ifndef APP_SESSION_H_
#define APP_SESSION_H_

#include <lgui.h>
#include "bg_session.h"

void app_session_prepare(BgSession *session);
void app_session_add_profile(BgSession *session, const char *name, LOptionList *profile);

#endif /* APP_SESSION_H_ */

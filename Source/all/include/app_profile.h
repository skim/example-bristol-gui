#ifndef APP_PROFILE_H_
#define APP_PROFILE_H_

#include <lgui.h>
#include "bg_session.h"

LOptionList* app_profile_new();
void app_profile_prepare_session(BgSession *session);

#endif /* APP_PROFILE_H_ */

#ifndef PROFILE_H_
#define PROFILE_H_

#include <lgui.h>

#define BG_SIGNAL_PROFILE_UPDATE_BUFFER_COMMAND "bg_profile_update_buffer_command"

LProfile* 	bg_profile_new			();
void 		bg_profile_connect		(LProfile *profile, GtkBuilder *builder);
void 		bg_profile_disconnect	(LProfile *profile, GtkBuilder *builder);

#endif /* PROFILE_H_ */

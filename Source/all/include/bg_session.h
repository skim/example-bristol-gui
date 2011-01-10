#ifndef BG_SESSION_H_
#define BG_SESSION_H_

#include <gtk/gtk.h>
#include <llib.h>

#define BG_SESSION_DEFAULT_PROFILE "Default"

typedef struct _BgSession BgSession;

BgSession* 	bg_session_new(GtkBuilder *builder);
void		bg_session_set_active_profile(BgSession *session, const char *profile_name);
void		bg_session_add_option_combo_box(BgSession *session, LOption *option, LValueList *choices, const char *combo_name, const char *toggle_name, const char *con_name);
void		bg_session_add_option_adjustment(BgSession *session, LOption *option, const char *adjust_name, const char *toggle_name, const char *con_name);

#endif /* BG_SESSION_H_ */

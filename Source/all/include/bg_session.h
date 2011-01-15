#ifndef BG_SESSION_H_
#define BG_SESSION_H_

#include <gtk/gtk.h>
#include <llib.h>

typedef struct _BgSession BgSession;

BgSession* 		bg_session_new(GtkBuilder *builder);
void			bg_session_insert_profile(BgSession *session, const char *name, LOptionList *profile);
void 			bg_session_set_active_profile(BgSession *session, const char *name);
LOptionList*	bg_session_get_active_profile(BgSession *session);
void 			bg_session_register_combo_box(BgSession *session, const char *option_name, const char *widget_name, LValueList *filling);
void 			bg_session_register_adjustment(BgSession *session, const char *option_name, const char *widget_name);
void 			bg_session_register_enable_button(BgSession *session, const char *option_name, const char *button_name, const char *widget_to_toggle);
void 			bg_session_connect_profile(BgSession *session, const char *name);
LValueList* 	bg_session_get_profile_names(BgSession *session);

#endif /* BG_SESSION_H_ */

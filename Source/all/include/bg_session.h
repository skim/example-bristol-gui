#ifndef BG_SESSION_H_
#define BG_SESSION_H_

#include <gtk/gtk.h>
#include <llib.h>

typedef struct _BgSession BgSession;

BgSession* 		bg_session_new(GtkBuilder *builder);
void			bg_session_insert_profile(BgSession *session, const char *name, LOptionList *profile);
void 			bg_session_set_active_profile(BgSession *session, const char *name);
void 			bg_session_register_combo_box(BgSession *session, const char *option_name, const char *widget_name, LValueList *filling);
void 			bg_session_register_adjustment(BgSession *session, const char *option_name, const char *widget_name);
void 			bg_session_register_enable_button(BgSession *session, const char *option_name, const char *button_name, const char *widget_to_toggle);

#endif /* BG_SESSION_H_ */

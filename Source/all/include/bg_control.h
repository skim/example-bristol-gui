#ifndef BG_CONTROL_H_
#define BG_CONTROL_H_

#include "bg_session.h"
#include <gtk/gtk.h>

void bg_option_switch_check_button_control_init(BgSession *session, GtkBuilder *builder, const char *id, const char *option_widget);
BgOption* bg_get_option_from_widget(GtkBuilder *builder, const char *id, GObject *widget);

#endif /* BG_CONTROL_H_ */

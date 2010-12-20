#ifndef BG_CONTROL_H_
#define BG_CONTROL_H_

#include "bg_session.h"
#include <gtk/gtk.h>

void 		bg_option_init(BgSession *session, GtkBuilder *builder, const char *id, const char *option_widget);
void 		bg_option_connect(BgSession *session, GtkBuilder *builder, const char *id, const char *option_widget);
void 		bg_options_before_start(BgSession *session, GtkBuilder *builder);
// only here so the function order in bg_control.c makes more sense
BgOption* 	bg_get_option_from_widget(GtkBuilder *builder, const char *id, GObject *widget);

#endif /* BG_CONTROL_H_ */

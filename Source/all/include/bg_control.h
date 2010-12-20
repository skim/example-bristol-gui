#ifndef BG_CONTROL_H_
#define BG_CONTROL_H_

#include "bg_session.h"
#include <gtk/gtk.h>

/*
 * control:
 *
 * A checkbox with an attached widget/ adjustment. Naming contract:
 *
 * check_[id]: 			the check button to add/ remove the option from the profile
 * box_[id]:			the h-/ vbox containing this control's widgets
 * [widgetprefix]_[id]: the widget(s) controlling the option
 *
 */

void 		bg_control_init(BgSession *session, GtkBuilder *builder, const char *id, const char *option_widget);
void 		bg_control_connect(BgSession *session, GtkBuilder *builder, const char *id, const char *option_widget);
void 		bg_control_before_start(BgSession *session, GtkBuilder *builder);
// only here so the function order in bg_control.c makes more sense
BgOption* 	bg_control_get_option_from_widget(GtkBuilder *builder, const char *id, GObject *widget);

#endif /* BG_CONTROL_H_ */

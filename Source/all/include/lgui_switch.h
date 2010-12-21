#ifndef LGUI_SWITCH_H_
#define LGUI_SWITCH_H_

#include <gtk/gtk.h>

void 		lgui_switch_button_visible_connect			(GtkBuilder *builder, const char *id);
void 		lgui_switch_check_button_sensitive_connect	(GtkBuilder *builder, const char *id);

#endif /* LGUI_SWITCH_H_ */

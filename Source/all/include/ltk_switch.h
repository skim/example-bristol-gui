#ifndef LTK_SWITCH_H_
#define LTK_SWITCH_H_

#include "ltk_config.h"
#include <gtk/gtk.h>

void ltk_switch_hide_connect		(GtkButton *button, GtkWidget *widget_to_hide);
void ltk_switch_deactivate_connect	(GtkButton *button, GtkWidget *widget_to_deactivate);

#endif /* LTK_SWITCH_H_ */

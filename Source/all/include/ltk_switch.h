#ifndef LTK_SWITCH_H_
#define LTK_SWITCH_H_

#include "ltk_config.h"
#include <gtk/gtk.h>

void ltk_switch_visible_connect		(GtkButton *button, GtkWidget *widget);
void ltk_switch_sensitive_connect	(GtkButton *button, GtkWidget *widget);

#endif /* LTK_SWITCH_H_ */

#ifndef LGTK_H_
#define LGTK_H_

#include <gtk/gtk.h>

#define LGTK_SWITCH_ICON_STOCK_SHOW			"gtk-go-down"
#define LGTK_SWITCH_ICON_STOCK_HIDE			"gtk-go-up"
#define LGTK_SWITCH_ICON_SIZE				GTK_ICON_SIZE_MENU

void lgtk_signal_switch_connect(GtkButton *button, GtkWidget *widget);
void lgtk_builder_signal_switch_connect(GtkBuilder *builder, const char *button_name, const char *widget_name);

#endif /* LGTK_H_ */

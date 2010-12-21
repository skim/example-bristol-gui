#include "ltk_switch.h"
#include "ltk_config.h"
#include "ltk_common.h"

static void ltk_switch_hide_button_clicked(GtkButton *button, gpointer data) {
	GtkWidget *widget = GTK_WIDGET(data);
	gtk_widget_set_visible(widget, !gtk_widget_get_visible(widget));
	GType type = G_OBJECT_TYPE(button);
	if (type == GTK_TYPE_BUTTON) {
		if (gtk_widget_get_visible(widget)) {
			ltk_button_set_stock_image(button, LTK_SWITCH_STOCK_HIDE, LTK_SWITCH_ICON_SIZE);
		} else {
			ltk_button_set_stock_image(button, LTK_SWITCH_STOCK_SHOW, LTK_SWITCH_ICON_SIZE);
		}
	}
}

static void ltk_switch_deactive_button_clicked(GtkButton *button, gpointer data) {
	GtkWidget *widget = GTK_WIDGET(data);
	gtk_widget_set_sensitive(widget, !gtk_widget_get_sensitive(widget));
	GType type = G_OBJECT_TYPE(button);
	if (type == GTK_TYPE_CHECK_BUTTON) {
		GtkWidget *label = gtk_bin_get_child(GTK_BIN(button));
		gtk_widget_set_sensitive(label, gtk_widget_get_sensitive(widget));
	}
}

void ltk_switch_hide_connect(GtkButton *button, GtkWidget *widget_to_hide) {
	g_assert(button != NULL);
	g_assert(widget_to_hide != NULL);
	g_signal_connect(button, "clicked", G_CALLBACK(ltk_switch_hide_button_clicked), widget_to_hide);
}

void ltk_switch_deactivate_connect(GtkButton *button, GtkWidget *widget_to_deactivate) {
	g_assert(button != NULL);
	g_assert(widget_to_deactivate != NULL);
	g_signal_connect(button, "clicked", G_CALLBACK(ltk_switch_deactive_button_clicked), widget_to_deactivate);
}

#include "ltk_switch.h"
#include "ltk_config.h"
#include "ltk_common.h"

static void ltk_switch_visible_button_clicked(GtkButton *button, gpointer data) {
	GtkWidget *widget = GTK_WIDGET(data);
	gtk_widget_set_visible(widget, !gtk_widget_get_visible(widget));
	GType type = G_OBJECT_TYPE(button);
	if (type == GTK_TYPE_BUTTON) {
		if (gtk_widget_get_visible(widget)) {
			ltk_button_set_stock_image(button, LTK_SWITCH_VISIBLE_STOCK_HIDE, LTK_SWITCH_VISIBLE_ICON_SIZE);
		} else {
			ltk_button_set_stock_image(button, LTK_SWITCH_VISIBLE_STOCK_SHOW, LTK_SWITCH_VISIBLE_ICON_SIZE);
		}
	}
}

static void ltk_switch_sensitive_button_clicked(GtkButton *button, gpointer data) {
	GtkWidget *widget = GTK_WIDGET(data);
	gtk_widget_set_sensitive(widget, !gtk_widget_get_sensitive(widget));
	GType type = G_OBJECT_TYPE(button);
	if (type == GTK_TYPE_CHECK_BUTTON) {
		GtkWidget *label = gtk_bin_get_child(GTK_BIN(button));
		gtk_widget_set_sensitive(label, gtk_widget_get_sensitive(widget));
	}
}

void ltk_switch_visible_connect(GtkButton *button, GtkWidget *widget) {
	g_assert(button != NULL);
	g_assert(widget != NULL);
	g_signal_connect(button, "clicked", G_CALLBACK(ltk_switch_visible_button_clicked), widget);
}

void ltk_switch_sensitive_connect(GtkButton *button, GtkWidget *widget) {
	g_assert(button != NULL);
	g_assert(widget != NULL);
	g_signal_connect(button, "clicked", G_CALLBACK(ltk_switch_sensitive_button_clicked), widget);
}

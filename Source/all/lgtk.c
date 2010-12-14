#include "lgtk.h"

static void lgtk_switch(GtkButton *button, gpointer widget_) {
	GtkWidget *widget = GTK_WIDGET(widget_);
	gtk_widget_set_visible(widget, !gtk_widget_get_visible(widget));
	char *stock = NULL;
	if (gtk_widget_get_visible(widget)) {
		stock = LGTK_SWITCH_ICON_STOCK_HIDE;
	} else {
		stock = LGTK_SWITCH_ICON_STOCK_SHOW;
	}
	gtk_button_set_image(button, gtk_image_new_from_stock(stock, LGTK_SWITCH_ICON_SIZE));
}

void lgtk_signal_switch_connect(GtkButton *button, GtkWidget *widget) {
	g_signal_connect(button, "clicked", G_CALLBACK(lgtk_switch), widget);
}

void lgtk_builder_signal_switch_connect(GtkBuilder *builder, const char *button_name, const char *widget_name) {
	lgtk_signal_switch_connect(GTK_BUTTON(gtk_builder_get_object(builder, button_name)), GTK_WIDGET(gtk_builder_get_object(builder, widget_name)));
}

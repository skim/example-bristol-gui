#include "gtk_common.h"

static GtkBuilder *gbuilder = NULL;

void gtk_common_init(GtkBuilder *builder) {
	gbuilder = builder;
}

GtkWidget* gtk_get_widget(const char *name) {
	return GTK_WIDGET(gtk_builder_get_object(gbuilder, name));
}

GtkObject* gtk_get_object(const char *name) {
	return GTK_OBJECT(gtk_builder_get_object(gbuilder, name));
}

GObject* g_get_object(const char *name) {
	return G_OBJECT(gtk_builder_get_object(gbuilder, name));
}

GtkImage* gtk_get_image(const char *name) {
	return GTK_IMAGE(gtk_builder_get_object(gbuilder, name));
}

void gtk_switch_button_switch(GtkButton *button, const char *container_name, const char *image_show_name, const char *image_hide_name) {
	GtkWidget *container = gtk_get_widget(container_name);
	gtk_widget_set_visible(container, !gtk_widget_get_visible(container));
	GtkIconSize stock_size;
	gtk_image_get_stock(GTK_IMAGE(gtk_button_get_image(button)), NULL, &stock_size);
	if (gtk_widget_get_visible(container)) {
		gtk_image_set_from_stock(GTK_IMAGE(gtk_button_get_image(button)), image_hide_name, stock_size);
	} else {
		gtk_image_set_from_stock(GTK_IMAGE(gtk_button_get_image(button)), image_show_name, stock_size);
	}
}

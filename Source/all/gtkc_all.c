#include "gtkc_all.h"

static GtkBuilder *gbuilder = NULL;

void gtkc_init(GtkBuilder *builder) {
	gbuilder = builder;
}

GtkWidget* gtkc_get_widget(const char *name) {
	return GTK_WIDGET(gtk_builder_get_object(gbuilder, name));
}

GtkObject* gtkc_get_object(const char *name) {
	return GTK_OBJECT(gtk_builder_get_object(gbuilder, name));
}

GtkEntry* gtkc_get_entry(const char *name) {
	return GTK_ENTRY(gtk_builder_get_object(gbuilder, name));
}

GObject* gtkc_get_gobject(const char *name) {
	return G_OBJECT(gtk_builder_get_object(gbuilder, name));
}

GtkImage* gtkc_get_image(const char *name) {
	return GTK_IMAGE(gtk_builder_get_object(gbuilder, name));
}

GtkAdjustment *gtkc_get_adjustment(const char *name) {
	return GTK_ADJUSTMENT(gtkc_get_object(name));
}

GtkComboBox *gtkc_get_combo_box(const char *name) {
	return GTK_COMBO_BOX(gtk_builder_get_object(gbuilder, name));
}

void gtkc_switch_button_switch(GtkButton *button, const char *container_name, const char *image_show_name, const char *image_hide_name) {
	GtkWidget *container = gtkc_get_widget(container_name);
	gtk_widget_set_visible(container, !gtk_widget_get_visible(container));
	GtkIconSize stock_size;
	gtk_image_get_stock(GTK_IMAGE(gtk_button_get_image(button)), NULL, &stock_size);
	if (gtk_widget_get_visible(container)) {
		gtk_image_set_from_stock(GTK_IMAGE(gtk_button_get_image(button)), image_hide_name, stock_size);
	} else {
		gtk_image_set_from_stock(GTK_IMAGE(gtk_button_get_image(button)), image_show_name, stock_size);
	}
}

void gtkc_entry_set_value(const char *name, const char *value) {
	gtk_entry_set_text(gtkc_get_entry(name), value);
}

void gtkc_adjustment_set_value(const char *name, double value) {
	gtk_adjustment_set_value(gtkc_get_adjustment(name), value);
}

void gtkc_combo_box_set_active(const char *name, unsigned int value) {
	gtk_combo_box_set_active(gtkc_get_combo_box(name), value);
}

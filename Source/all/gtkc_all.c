#include "gtkc_all.h"

static GtkBuilder *gbuilder = NULL;

void gtkc_init(GtkBuilder *builder) {
	gbuilder = builder;
}

GtkWidget* gtkc_new_placeholder() {
	return gtk_label_new("Cpt. Placeholder");
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

GtkLabel* gtkc_get_label(const char *name) {
	return GTK_LABEL(gtkc_get_widget(name));
}

GtkButton* gtkc_get_button(const char *name) {
	return GTK_BUTTON(gtkc_get_widget(name));
}

GtkImage* gtkc_get_image(const char *name) {
	return GTK_IMAGE(gtk_builder_get_object(gbuilder, name));
}

GtkNotebook* gtkc_get_notebook(const char *name) {
	return GTK_NOTEBOOK(gtkc_get_widget(name));
}

GtkAdjustment *gtkc_get_adjustment(const char *name) {
	return GTK_ADJUSTMENT(gtkc_get_object(name));
}

GtkComboBox *gtkc_get_combo_box(const char *name) {
	return GTK_COMBO_BOX(gtk_builder_get_object(gbuilder, name));
}

void gtkc_label_set_text(const char *name, const char *text) {
	gtk_label_set_text(gtkc_get_label(name), text);
}

void gtkc_switch_button_switch(const char *button_name, const char *container_name, const char *image_show_name, const char *image_hide_name) {
	GtkWidget *container = gtkc_get_widget(container_name);
	gtk_widget_set_visible(container, !gtk_widget_get_visible(container));
	GtkIconSize stock_size;
	GtkButton *button = gtkc_get_button(button_name);
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

GtkListStore* gtkc_combo_box_get_model(const char *name) {
	return GTK_LIST_STORE(gtk_combo_box_get_model(gtkc_get_combo_box(name)));

}

void gtkc_combo_box_set_active(const char *name, unsigned int value) {
	gtk_combo_box_set_active(gtkc_get_combo_box(name), value);
}

GtkTreeIter* gtkc_combo_box_append(const char *name) {
	GtkTreeIter *iter = g_new(GtkTreeIter, 1);
	gtk_list_store_append(gtkc_combo_box_get_model(name), iter);
	return iter;
}

//NEW

GtkWidget* gtkc_container_get_child(GtkWidget *container, unsigned int index) {
	return GTK_WIDGET(g_list_nth_data(gtk_container_get_children(GTK_CONTAINER(container)), index));
}

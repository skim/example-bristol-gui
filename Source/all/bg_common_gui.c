#include "bg_config.h"
#include "bg_common_gui.h"



GtkWidget* gtkc_image_new_from_file_scaled(const char *filename, double scale) {
	GtkWidget *image = NULL;
	GError *error = NULL;
	GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file(filename, &error);
	if (error == NULL) {
		//scale
		pixbuf = gdk_pixbuf_scale_simple(pixbuf, gdk_pixbuf_get_width(pixbuf) * BG_GUI_SCALE_TAB_IMAGES, gdk_pixbuf_get_height(pixbuf)
				* BG_GUI_SCALE_TAB_IMAGES, GDK_INTERP_BILINEAR);
		image = gtk_image_new_from_pixbuf(pixbuf);
	} else {
		g_warning("error loading image: %s: %s", filename, error->message);
		g_free(pixbuf);
		image = gtk_image_new_from_stock("gtk-missing-image", GTK_ICON_SIZE_MENU);
	}
	return image;
}

void gtkc_label_add_attribute(GtkWidget *label, PangoAttribute *attribute) {
	if (gtk_label_get_attributes(GTK_LABEL(label)) == NULL) {
		gtk_label_set_attributes(GTK_LABEL(label), pango_attr_list_new());
	}
	pango_attr_list_insert(gtk_label_get_attributes(GTK_LABEL(label)), attribute);
}

static void gtkc_switch_hbox_switch(GtkButton *button, gpointer data) {
	GtkWidget *widget = GTK_WIDGET(data);
	gtk_widget_set_visible(widget, !gtk_widget_get_visible(widget));
	if (gtk_widget_get_visible(widget)) {
		gtk_button_set_image(button, gtk_image_new_from_stock((const char*) g_object_get_data(G_OBJECT(button), "stock-image-hide"), GTK_ICON_SIZE_MENU));
	} else {
		gtk_button_set_image(button, gtk_image_new_from_stock((const char*) g_object_get_data(G_OBJECT(button), "stock-image-show"), GTK_ICON_SIZE_MENU));
	}
}

GtkWidget* gtkc_switch_hbox_new(const char *label_text, const char *stock_image_show, const char *stock_image_hide, GtkWidget *widget_to_switch) {
	GtkWidget *hbox = gtk_hbox_new(FALSE, 0);
	GtkWidget *label = gtk_label_new(g_strdup(label_text));
	gtkc_label_add_attribute(label, pango_attr_weight_new(PANGO_WEIGHT_BOLD));
	gtk_box_pack_start(GTK_BOX(hbox), label, FALSE, FALSE, BG_GUI_PADDING);
	gtk_box_pack_start(GTK_BOX(hbox), gtk_hseparator_new(), TRUE, TRUE, BG_GUI_PADDING);
	GtkWidget *button = gtk_button_new();
	g_object_set_data(G_OBJECT(button), "stock-image-show", g_strdup(stock_image_show));
	g_object_set_data(G_OBJECT(button), "stock-image-hide", g_strdup(stock_image_hide));
	gtk_button_set_image(GTK_BUTTON(button), gtk_image_new_from_stock(stock_image_hide, GTK_ICON_SIZE_MENU));
	gtk_button_set_relief(GTK_BUTTON(button), GTK_RELIEF_NONE);
	gtk_box_pack_start(GTK_BOX(hbox), button, FALSE, FALSE, BG_GUI_PADDING);
	g_signal_connect(button, "clicked", G_CALLBACK(gtkc_switch_hbox_switch), widget_to_switch);
	return hbox;
}

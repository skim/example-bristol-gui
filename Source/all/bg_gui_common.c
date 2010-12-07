#include "bg_config.h"
#include "bg_gui_common.h"

GtkWidget* bg_new_scaled_image_from_file(const char *filename, double scale) {
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

void bg_label_add_attribute(GtkWidget *label, PangoAttribute *attribute) {
	if (gtk_label_get_attributes(GTK_LABEL(label)) == NULL) {
		gtk_label_set_attributes(GTK_LABEL(label), pango_attr_list_new());
	}
	pango_attr_list_insert(gtk_label_get_attributes(GTK_LABEL(label)), attribute);
}

#include "common_gui.h"

void gtk_switchbutton_switch(GtkBuilder *builder, GtkButton *button, const char *container_name, const char *image_stock_show, const char *image_stock_hide) {
	GtkWidget *container = GTK_WIDGET(gtk_builder_get_object(builder, container_name));
	gtk_widget_set_visible(container, !gtk_widget_get_visible(container));
	GtkImage *image = (GtkImage*) gtk_button_get_image(button);
	GtkIconSize *size = g_malloc(sizeof(GtkIconSize*));
	gtk_image_get_stock(image, NULL, size);
	if (gtk_widget_get_visible(container)) {
		gtk_image_set_from_stock(image, image_stock_hide, *size);
	} else {
		gtk_image_set_from_stock(image, image_stock_show, *size);
	}
	g_free(size);
}

#include "ltk_common.h"

void ltk_button_set_stock_image(GtkButton *button, const char *stock_name, GtkIconSize size) {
	gtk_button_set_image(button, gtk_image_new_from_stock(stock_name, size));
}

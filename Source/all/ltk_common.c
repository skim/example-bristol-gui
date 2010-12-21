#include "ltk_common.h"
#include "string.h"

void ltk_button_set_stock_image(GtkButton *button, const char *stock_name, GtkIconSize size) {
	g_assert(button != NULL);
	g_assert(stock_name != NULL && strlen(stock_name) > 0);
	gtk_button_set_image(button, gtk_image_new_from_stock(stock_name, size));
}

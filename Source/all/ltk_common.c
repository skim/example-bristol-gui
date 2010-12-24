#include "ltk_common.h"
#include "string.h"

void ltk_button_set_stock_image(GtkButton *button, const char *stock_name, GtkIconSize size) {
	g_assert(button != NULL);
	g_assert(stock_name != NULL && strlen(stock_name) > 0);
	gtk_button_set_image(button, gtk_image_new_from_stock(stock_name, size));
}

void ltk_combo_box_fill(GtkComboBox *combo_box, LValueList *values) {
	g_assert(combo_box != NULL);
	g_assert(values != NULL);
	GtkListStore *store = NULL;
	store = gtk_list_store_new(2, G_TYPE_STRING, G_TYPE_POINTER);
	GtkTreeIter iter;
	int i;
	for (i = 0; i < l_value_list_length(values); i++) {
		gtk_list_store_append(store, &iter);
		LValue *value = l_value_list_nth_value(values, i);
		gtk_list_store_set(store, &iter, 0, l_value_list_nth_display_name(values, i), 1, value, -1);
	}
	gtk_combo_box_set_model(combo_box, GTK_TREE_MODEL(store));
	GtkCellRenderer *renderer = gtk_cell_renderer_text_new();
	gtk_cell_layout_pack_start(GTK_CELL_LAYOUT(combo_box), renderer, FALSE);
	gtk_cell_layout_set_attributes(GTK_CELL_LAYOUT(combo_box), renderer, "text", 0, NULL);
	gtk_combo_box_set_active(combo_box, 0);
}

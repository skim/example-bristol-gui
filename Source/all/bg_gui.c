#include "bg_gui.h"
#include "bg_config.h"
#include "stdlib.h"

static void bg_gui_switched(GtkButton *button, gpointer data) {
	BgGuiPayload *payload = (BgGuiPayload*) data;
	GtkWidget *box = GTK_WIDGET(gtk_builder_get_object(payload->builder, bg_gui_name(payload->id, "box")));
	gtk_widget_set_visible(box, !gtk_widget_get_visible(box));
	char *stock_name = gtk_widget_get_visible(box) ? BG_STOCK_HIDE : BG_STOCK_SHOW;
	GtkWidget *image = gtk_image_new_from_stock(stock_name, GTK_ICON_SIZE_MENU);
	gtk_button_set_image(button, image);
}

static void bg_gui_toggled(GtkCheckButton *check, gpointer data) {
	GtkWidget *label = gtk_bin_get_child(GTK_BIN(check));
	BgGuiPayload *load = (BgGuiPayload*) data;
	gtk_widget_set_sensitive(label, gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(check)));
	char *box_name = bg_gui_name(load->id, "box");
	gtk_widget_set_sensitive(GTK_WIDGET(gtk_builder_get_object(load->builder, box_name)), gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(check)));
}

char *bg_gui_name(const char *id, const char *widget) {
	return g_strdup_printf("%s_%s", widget, id);
}

BgGuiPayload *bg_gui_payload_new(GtkBuilder *builder, const char *id) {
	BgGuiPayload *load = g_new(BgGuiPayload, 1);
	load->builder = builder;
	load->id = g_strdup(id);
	return load;
}

void bg_gui_checkbox_prepare(GtkBuilder *builder, const char *id, gboolean active) {
	GtkCheckButton *check = GTK_CHECK_BUTTON(gtk_builder_get_object(builder, bg_gui_name(id, "check")));
	BgGuiPayload *payload = bg_gui_payload_new(builder, id);
	g_signal_connect(check, "toggled", G_CALLBACK(bg_gui_toggled), payload);
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check), active);
	bg_gui_toggled(check, payload);
}

void bg_gui_combobox_prepare(GtkBuilder *builder, const char *id, BgEntryList *entries, int selected) {
	GtkComboBox *combo = GTK_COMBO_BOX(gtk_builder_get_object(builder, bg_gui_name(id, "combo")));
	GtkListStore *store = gtk_list_store_new(2, G_TYPE_STRING, G_TYPE_STRING);
	gtk_combo_box_set_model(combo, GTK_TREE_MODEL(store));
	GtkTreeIter iter;
	int i;
	for (i = 0; i < g_list_length(entries->list); i++) {
		BgEntry *entry = bg_entry_list_nth(entries, i);
		gtk_list_store_append(store, &iter);
		gtk_list_store_set(store, &iter, 0, entry->name, 1, entry->value, -1);
	}
	GtkCellRenderer *renderer = gtk_cell_renderer_text_new();
	gtk_cell_layout_pack_start(GTK_CELL_LAYOUT(combo), renderer, TRUE);
	gtk_cell_layout_set_attributes(GTK_CELL_LAYOUT(combo), renderer, "text", 0, NULL);
	if (selected == -1) {
		selected = 0;
	}
	gtk_combo_box_set_active(combo, selected);
}

int bg_gui_combobox_get_index(GtkBuilder *builder, const char *id, const char *value) {
	GtkComboBox *combo = GTK_COMBO_BOX(gtk_builder_get_object(builder, bg_gui_name(id, "combo")));
	GtkTreeModel *store = gtk_combo_box_get_model(combo);
	GtkTreeIter iter;
	int row = 0;
	gboolean valid = gtk_tree_model_get_iter_first(store, &iter);
	while (valid) {
		char *name;
		char *_value;
		gtk_tree_model_get(store, &iter, 0, &name, 1, &_value, -1);
		if (g_str_equal(_value, value)) {
			return row;
		} else {
			g_free(name);
			g_free(_value);
			row++;
			valid = gtk_tree_model_iter_next(store, &iter);
		}
	}
	return -1;
}

void bg_gui_combobox_set_active_value(GtkBuilder *builder, const char *id, const char *value) {
	int index = bg_gui_combobox_get_index(builder, id, value);
	if (index != -1) {
		g_debug("setting active on %s to %d (%s)", bg_gui_name(id, "combo"), index, value);
		gtk_combo_box_set_active(GTK_COMBO_BOX(gtk_builder_get_object(builder, bg_gui_name(id, "combo"))), index);
	} else {
		g_warning("no combo entry for value: %s", value);
	}
}

const char* bg_gui_combobox_get_active_value(GtkBuilder *builder, const char *id) {
	GtkComboBox *combo = GTK_COMBO_BOX(gtk_builder_get_object(builder, bg_gui_name(id, "combo")));
	GtkTreeModel *store = gtk_combo_box_get_model(combo);
	GtkTreeIter iter;
	if (gtk_combo_box_get_active_iter(combo, &iter)) {
		char *_name;
		char *value = NULL;
		gtk_tree_model_get(store, &iter, 0, &_name, 1, value, -1);
		g_free(_name);
		return g_strdup(value);

	} else {
		return NULL;
	}

}

void bg_gui_adjust_set_value(GtkBuilder *builder, const char *id, double value) {
	GtkAdjustment *adjust = GTK_ADJUSTMENT(gtk_builder_get_object(builder, bg_gui_name(id, "adjust")));
	gtk_adjustment_set_value(adjust, value);
}

void bg_gui_switch_prepare(GtkBuilder *builder, const char *id) {
	GtkButton *button = GTK_BUTTON(gtk_builder_get_object(builder, bg_gui_name(id, "switch")));
	BgGuiPayload *payload = bg_gui_payload_new(builder, id);
	g_signal_connect(button, "clicked", G_CALLBACK(bg_gui_switched), payload);
}

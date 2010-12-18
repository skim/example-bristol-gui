#include "bg_gui.h"

typedef struct {
	GtkLabel *label;
	BgData *data;
} _BgGuiProfile;

void bg_combo_prepare(GtkComboBox *combo) {
	g_assert(combo != NULL);
	GtkListStore *store = gtk_list_store_new(1, G_TYPE_STRING);
	gtk_combo_box_set_model(GTK_COMBO_BOX(combo), GTK_TREE_MODEL(store));
	GtkCellRenderer *renderer = gtk_cell_renderer_text_new();
	gtk_cell_layout_pack_start(GTK_CELL_LAYOUT( combo ), renderer, TRUE);
	gtk_cell_layout_set_attributes(GTK_CELL_LAYOUT(combo), renderer, "text", 0, NULL);
}

static void _bg_combo_profile_changed(GtkComboBox *combo, gpointer gui_profile_) {
	g_assert(gtk_combo_box_get_active(combo) != -1);
	_BgGuiProfile *gui = (_BgGuiProfile*) gui_profile_;
	BgProfile *profile = bg_data_get_profile(gui->data, gtk_combo_box_get_active(combo));
	g_assert(profile != NULL);
	gtk_label_set_text(gui->label, profile->name);
	gui->data->current_profile = profile;
}

static void _bg_list_store_add_profile(gpointer profile_, gpointer store_) {
	BgProfile *profile = (BgProfile*) profile_;
	GtkListStore *store = GTK_LIST_STORE(store_);
	GtkTreeIter iter;
	gtk_list_store_append(store, &iter);
	gtk_list_store_set(store, &iter, 0, g_strdup(profile->name), -1);
}

void bg_combo_set_profiles(GtkComboBox *combo, GtkLabel *label, BgData *data) {
	g_assert(combo != NULL);
	g_assert(label != NULL);
	g_assert(data != NULL);
	GtkListStore *store = GTK_LIST_STORE(gtk_combo_box_get_model(combo));
	gtk_list_store_clear(store);
	g_list_foreach(bg_data_get_profiles(data), _bg_list_store_add_profile, store);
	if (gtk_combo_box_get_active(combo) == -1) {
		gtk_combo_box_set_active(combo, 0);
	}
	_BgGuiProfile *gui = g_new(_BgGuiProfile, 1);
	gui->data = data;
	gui->label = label;
	g_signal_connect(combo, "changed", G_CALLBACK(_bg_combo_profile_changed), gui);
}


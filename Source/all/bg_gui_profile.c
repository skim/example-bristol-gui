#include "bg_gui_profile.h"
#include "bg_config.h"
#include <gtk/gtk.h>
#include <string.h>

static void bg_gui_combo_box_profiles_fill(gpointer object, gpointer data) {
	BgProfile *profile = (BgProfile*) object;
	GtkListStore *store = GTK_LIST_STORE(data);
	GtkTreeIter iter;
	gtk_list_store_append(store, &iter);
	gtk_list_store_set(store, &iter, 0, profile->name, 1, profile, -1);
}

GtkWidget* bg_gui_combo_box_profiles_new(GListProxy *profiles) {
	GtkListStore *store = gtk_list_store_new(2, G_TYPE_STRING, G_TYPE_POINTER, NULL);
	g_list_foreach(profiles->list, bg_gui_combo_box_profiles_fill, store);
	GtkWidget *combo = gtk_combo_box_new_with_model(GTK_TREE_MODEL(store));
	GtkCellRenderer *renderer = gtk_cell_renderer_text_new();
	gtk_cell_layout_pack_start(GTK_CELL_LAYOUT(combo), renderer, TRUE);
	gtk_cell_layout_set_attributes(GTK_CELL_LAYOUT(combo), renderer, "text", 0, NULL);
	gtk_combo_box_set_active(GTK_COMBO_BOX(combo), 0);
	g_object_unref(G_OBJECT(store));
	return combo;
}

char* bg_gui_new_profile_name(GListProxy *profiles) {
	return g_strdup_printf("Profile-%d", g_list_length(profiles->list) + 2);
}

int bg_list_compare_profile_name(gconstpointer a, gconstpointer b) {
	BgProfile *id_a = (BgProfile*) a;
	BgProfile *id_b = (BgProfile*) b;
	return g_strcmp0(id_a->name, id_b->name);
}


void bg_gui_profile_name_changed(GtkEditable *editable, gpointer data) {
	char *text = gtk_editable_get_chars(editable, 0, -1);
	if (text != NULL) {
		text = g_strstrip(text);
	}
	GListProxy *proxy = (GListProxy*) data;
	if (text == NULL || strlen(text) == 0) {
		GtkWidget *error = GTK_WIDGET(g_object_get_data(G_OBJECT(editable), "error-label"));
		gtk_label_set_text(GTK_LABEL(error), "Please provide a name for the new profile.");
		gtk_widget_show(error);
	} else if (g_list_find_custom(proxy->list, text, bg_list_compare_profile_name) != NULL) {
		GtkWidget *error = GTK_WIDGET(g_object_get_data(G_OBJECT(editable), "error-label"));
		gtk_label_set_text(GTK_LABEL(error), g_strdup_printf("A profile with this name already exists: %s.", text));
		gtk_widget_show(error);
	} else {
		GtkWidget *error = GTK_WIDGET(g_object_get_data(G_OBJECT(editable), "error-label"));
		gtk_widget_hide(error);
	}
}

void bg_gui_dialog_new_profile(GtkWidget *window_root, BgStore *store) {
	GtkWidget *dialog = gtk_dialog_new_with_buttons("New Profile", GTK_WINDOW(window_root), GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
			GTK_STOCK_CANCEL, GTK_RESPONSE_REJECT, GTK_STOCK_OK, GTK_RESPONSE_ACCEPT, NULL);
	GtkWidget *box = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
	GtkWidget *error = gtk_label_new(NULL);
	gtk_widget_hide(error);
	gtk_box_pack_start(GTK_BOX(box), error, FALSE, FALSE, BG_GUI_PADDING);
	GtkWidget *hbox = gtk_hbox_new(FALSE, 0);
	gtk_box_pack_start(GTK_BOX(hbox), gtk_label_new("Name for the new profile"), FALSE, FALSE, BG_GUI_PADDING);
	GtkWidget *entry = gtk_entry_new_with_max_length(256);
	g_object_set_data(G_OBJECT(entry), "error-label", error);
	g_signal_connect(entry, "changed", G_CALLBACK(bg_gui_profile_name_changed), store->profiles);
	gtk_entry_set_text(GTK_ENTRY(entry), bg_gui_new_profile_name(store->profiles));
	gtk_widget_set_size_request(entry, 96, -1);
	gtk_box_pack_start(GTK_BOX(hbox), entry, TRUE, TRUE, BG_GUI_PADDING);
	gtk_box_pack_start(GTK_BOX(box), hbox, FALSE, FALSE, BG_GUI_PADDING);
	GtkWidget *hbox2 = gtk_hbox_new(FALSE, 0);
	gtk_box_pack_start(GTK_BOX(hbox2), gtk_label_new("Copy settings from"), FALSE, FALSE, BG_GUI_PADDING);
	GtkWidget *combo = bg_gui_combo_box_profiles_new(store->profiles);
	gtk_widget_set_size_request(combo, 96, -1);
	GtkTreeIter iter;
	gtk_list_store_insert(GTK_LIST_STORE(gtk_combo_box_get_model(GTK_COMBO_BOX(combo))), &iter, 0);
	gtk_list_store_set(GTK_LIST_STORE(gtk_combo_box_get_model(GTK_COMBO_BOX(combo))), &iter, 0, "None", 1, "", -1);
	gtk_combo_box_set_active(GTK_COMBO_BOX(combo), 0);
	gtk_box_pack_start(GTK_BOX(hbox2), combo, TRUE, TRUE, BG_GUI_PADDING);
	gtk_box_pack_start(GTK_BOX(box), hbox2, FALSE, FALSE, BG_GUI_PADDING);
	gtk_widget_show_all(box);
	gboolean valid = FALSE;
	int response;
	while (!valid) {
		response = gtk_dialog_run(GTK_DIALOG(dialog));
		if (response == GTK_RESPONSE_ACCEPT) {
			valid = TRUE;
			g_debug("accept");
		}
	}
	gtk_widget_destroy(dialog);
}

static void bg_gui_profile_new(GtkButton *button, gpointer data) {
	g_debug("new profile button");
	bg_gui_dialog_new_profile(GTK_WIDGET(g_object_get_data(G_OBJECT(button), "window_root")), (BgStore*) data);
}

GtkWidget *bg_gui_box_buttons_profiles_new(BgStore *store, GtkWidget *window_root) {
	GtkWidget *box = gtk_hbox_new(FALSE, 0);
	GtkWidget *button_new = gtk_button_new();
	gtk_button_set_image(GTK_BUTTON(button_new), gtk_image_new_from_stock(BG_GUI_STOCK_NEW, GTK_ICON_SIZE_MENU));
	gtk_widget_set_tooltip_text(button_new, "Add a new profile.");
	gtk_box_pack_start(GTK_BOX(box), button_new, FALSE, FALSE, 0);
	g_object_set_data(G_OBJECT(button_new), "window_root", window_root);
	g_signal_connect(button_new, "clicked", G_CALLBACK(bg_gui_profile_new), store);
	GtkWidget *button_save = gtk_button_new();
	gtk_button_set_image(GTK_BUTTON(button_save), gtk_image_new_from_stock(BG_GUI_STOCK_SAVE, GTK_ICON_SIZE_MENU));
	gtk_widget_set_tooltip_text(button_save, "Save the current profile.");
	gtk_box_pack_start(GTK_BOX(box), button_save, FALSE, FALSE, 0);
	GtkWidget *button_delete = gtk_button_new();
	gtk_button_set_image(GTK_BUTTON(button_delete), gtk_image_new_from_stock(BG_GUI_STOCK_DELETE, GTK_ICON_SIZE_MENU));
	gtk_widget_set_tooltip_text(button_save, "Delete the current profile.");
	gtk_box_pack_start(GTK_BOX(box), button_delete, FALSE, FALSE, 0);
	return box;
}

GtkWidget* bg_gui_profiles_box_new(BgStore *store, GtkWidget *window_root) {
	GtkWidget *box_profiles = gtk_hbox_new(FALSE, 0);
	GtkWidget *combo_profiles = bg_gui_combo_box_profiles_new(store->profiles);
	gtk_box_pack_start(GTK_BOX(box_profiles), gtk_label_new("Profiles"), FALSE, FALSE, BG_GUI_PADDING);
	gtk_box_pack_start(GTK_BOX(box_profiles), combo_profiles, TRUE, TRUE, BG_GUI_PADDING);
	GtkWidget *box_buttons = bg_gui_box_buttons_profiles_new(store, window_root);
	gtk_box_pack_start(GTK_BOX(box_profiles), box_buttons, FALSE, FALSE, BG_GUI_PADDING);
	return box_profiles;
}


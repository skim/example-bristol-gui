#include "bg_gui.h"
#include "bg_configuration.h"
#include "bg_starter.h"
#include "gtkc_all.h"
#include <gtk/gtk.h>

#define WINDOW_ROOT	"window_root"
#define WINDOW_HELP	"window_help"
#define VIEW_HELP	"view_help"

void bg_gui_combo_configuration_prepare(const char *name) {
	g_debug("bg_gui_combo_configuration_prepare(%s)", name);
	GtkListStore *store = gtk_list_store_new(1, G_TYPE_STRING);
	//GtkTreeIter iter;
	GtkComboBox *combo = gtkc_get_combo_box(name);
	gtk_combo_box_set_model(combo, GTK_TREE_MODEL(store));
	gtk_combo_box_set_active(combo, 0);
	GtkCellRenderer *renderer = gtk_cell_renderer_text_new();
	gtk_cell_layout_pack_start(GTK_CELL_LAYOUT(combo), renderer, TRUE);
	gtk_cell_layout_set_attributes(GTK_CELL_LAYOUT(combo), renderer, "text", 0, NULL);
	g_object_unref(G_OBJECT(store));
}

void bg_gui_combo_soundengine_prepare(const char *name) {
	g_debug("bg_gui_combo_soundengine_prepare(%s)", name);
	GtkListStore *store = gtk_list_store_new(2, G_TYPE_STRING, G_TYPE_UINT);
	GtkTreeIter iter;
	gtk_list_store_append(store, &iter);
	gtk_list_store_set(store, &iter, 0, "JACK", 1, BG_JACK, -1);
	gtk_list_store_append(store, &iter);
	gtk_list_store_set(store, &iter, 0, "ALSA", 1, BG_ALSA, -1);
	gtk_list_store_append(store, &iter);
	gtk_list_store_set(store, &iter, 0, "Pulse Audio", 1, BG_PULSE, -1);
	gtk_list_store_append(store, &iter);
	gtk_list_store_set(store, &iter, 0, "OSS", 1, BG_OSS, -1);
	GtkComboBox *combo = gtkc_get_combo_box(name);
	gtk_combo_box_set_model(combo, GTK_TREE_MODEL(store));
	gtk_combo_box_set_active(combo, 0);
	GtkCellRenderer *renderer = gtk_cell_renderer_text_new();
	gtk_cell_layout_pack_start(GTK_CELL_LAYOUT(combo), renderer, TRUE);
	gtk_cell_layout_set_attributes(GTK_CELL_LAYOUT(combo), renderer, "text", 0, NULL);
	g_object_unref(G_OBJECT(store));
}

void bg_gui_prepare(const char *suffix) {
	g_debug("bg_gui_prepare(%s)", suffix);
	char *name = g_strconcat("combo_configuration_", suffix, NULL);
	bg_gui_combo_configuration_prepare(name);
	g_free(name);
	name = g_strconcat("combo_soundengine_", suffix, NULL);
	bg_gui_combo_soundengine_prepare(name);
	g_free(name);
}

void bg_synth_start(const char *synth_name) {
	start_bristol();
}

void bg_gui_set(const char *suffix, bg_configuration *config) {
	g_debug("bg_gui_set(%s, %s)", suffix, config->name);
	char *name = g_strconcat("combo_soundengine_", suffix, NULL);
	gtkc_combo_box_set_active(name, config->soundengine);
	g_free(name);
	name = g_strconcat("entry_identifier_", suffix, NULL);
	gtkc_entry_set_value(name, config->identifier);
	g_free(name);
	name = g_strconcat("adjust_samplerate_", suffix, NULL);
	gtkc_adjustment_set_value(name, config->samplerate);
	g_free(name);
	name = g_strconcat("adjust_periodsize_", suffix, NULL);
	gtkc_adjustment_set_value(name, config->periodsize);
	g_free(name);
	name = g_strconcat("adjust_midichannel_", suffix, NULL);
	gtkc_adjustment_set_value(name, config->midichannel);
	g_free(name);
	name = g_strconcat("combo_configuration_", suffix, NULL);

}


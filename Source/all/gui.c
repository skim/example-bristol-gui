#include "gui.h"
#include "gtk_common.h"
#include "starter.h"
#include <gtk/gtk.h>

#define WINDOW_ROOT	"window_root"
#define WINDOW_HELP	"window_help"
#define VIEW_HELP	"view_help"

void bg_prepare_combo_soundengine(const char *name) {
	GtkListStore *store = gtk_list_store_new(1, G_TYPE_STRING);
	GtkTreeIter iter;
	gtk_list_store_append(store, &iter);
	gtk_list_store_set(store, &iter, 0, "JACK", -1);
	gtk_list_store_append(store, &iter);
	gtk_list_store_set(store, &iter, 0, "ALSA", -1);
	gtk_list_store_append(store, &iter);
	gtk_list_store_set(store, &iter, 0, "Pulse Audio", -1);
	gtk_list_store_append(store, &iter);
	gtk_list_store_set(store, &iter, 0, "OSS", -1);
	GtkComboBox *combo = GTK_COMBO_BOX(gtk_get_widget(name));
	gtk_combo_box_set_model(combo, GTK_TREE_MODEL(store));
	gtk_combo_box_set_active(combo, 0);
	GtkCellRenderer *renderer = gtk_cell_renderer_text_new();
	gtk_cell_layout_pack_start(GTK_CELL_LAYOUT(combo), renderer, TRUE);
	gtk_cell_layout_set_attributes(GTK_CELL_LAYOUT(combo), renderer, "text", 0, NULL);
	g_object_unref(G_OBJECT(store));
}

void bg_prepare_entry_identifier(const char *name, const char *identifier) {
	GtkEntry *entry = GTK_ENTRY(gtk_get_widget(name));
	gtk_entry_set_text(entry, identifier);
}

void bg_prepare_adjust_samplerate(const char *name, unsigned int samplerate) {
	GtkAdjustment *adjust = GTK_ADJUSTMENT(gtk_get_object(name));
	gtk_adjustment_set_value(adjust, samplerate);
}

void bg_prepare_adjust_midichannel(const char *name, unsigned int midichannel) {
	GtkAdjustment *adjust = GTK_ADJUSTMENT(gtk_get_object(name));
	gtk_adjustment_set_value(adjust, midichannel);
}

void bg_show_help(const char *text_name) {
	GtkTextView *view = GTK_TEXT_VIEW(gtk_get_widget(VIEW_HELP));
	GtkTextBuffer *text = GTK_TEXT_BUFFER(g_get_object(text_name));
	gtk_text_view_set_buffer(view, text);
	GtkWidget *help = gtk_get_widget(WINDOW_HELP);
	gtk_widget_show(help);
	gtk_window_set_focus(GTK_WINDOW(help), GTK_WIDGET(view));
}

void bg_start_synth(const char *synth_name) {
	start_bristol();
}


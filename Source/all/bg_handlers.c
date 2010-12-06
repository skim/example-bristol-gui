#include "bg_handlers.h"
#include "bg_gui.h"
#include "bg_data.h"
#include <stdio.h>

typedef struct {
	bg_store *store;
	bg_gui *gui;
} bg_handle;

typedef struct {
	bg_company *company;
	bg_gui *gui;
} bg_handle_company;

typedef struct {
	bg_synth *synth;
	bg_gui *gui;
} bg_handle_synth;

gboolean find_synth_by_tab_index(gpointer key, gpointer value, gpointer data) {
	int index =	GPOINTER_TO_INT(data);
	bg_synth *synth = (bg_synth*) value;
	g_debug("%d, %d", index, synth->tab_index);
	return index == synth->tab_index;
}

gboolean on_window_destroy(GtkWidget *window, GdkEvent *event, gpointer data) {
	g_debug("exiting");
	gtk_main_quit();
	return TRUE;
}

gboolean on_synth_show(GtkNotebook* notebook, GtkNotebookPage *page, gint index, gpointer data) {
	bg_handle_company *handle = (bg_handle_company*) data;
	bg_synth *synth = (bg_synth*) g_hash_table_find(handle->company->synths, find_synth_by_tab_index, GINT_TO_POINTER(index));
	g_debug("switch-page, company: %s, synth: %s", handle->company->id, synth->id);
	gtk_widget_unparent(handle->gui->box_params);
	GtkWidget *box_params = GTK_WIDGET(g_hash_table_lookup(handle->gui->boxes_params_synths, synth->id));
	g_assert(handle->gui->box_params != NULL);
	gtk_box_pack_start(GTK_BOX(box_params), handle->gui->box_params, TRUE, TRUE, 4);
	return TRUE;
}

void on_button_switch_audioproperties_clicked(GtkButton *button, gpointer data) {
}

static void set_company_handlers(gpointer keypointer, gpointer value, gpointer data) {
	bg_handle *handle = (bg_handle*) data;
	bg_company *company = (bg_company*) value;
	g_debug("adding handlers for company-gui: %s", company->id);
	bg_handle_company *handle_company = g_new(bg_handle_company, 1);
	handle_company->gui = handle->gui;
	handle_company->company = company;
	g_signal_connect(g_hash_table_lookup(handle->gui->notebooks_synths, company->id), "switch-page", G_CALLBACK(on_synth_show), handle_company);
}

void bg_handlers_init(bg_store *store, bg_gui *gui) {
	g_debug("adding handlers");
	bg_handle *handle = g_new(bg_handle, 1);
	handle->store = store;
	handle->gui = gui;
	g_signal_connect(gui->window_root, "delete-event", G_CALLBACK(on_window_destroy), handle);
	g_hash_table_foreach(handle->store->companies, set_company_handlers, handle);
}

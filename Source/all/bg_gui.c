#include "bg_gui.h"
#include "bg_data.h"
#include "gtkc_all.h"
#include <glib.h>

#define WINDOW_ROOT			"window_root"
#define BOX_GUI				"box_gui"
#define IMAGE_STOCK_UP 		"gtk-go-up"
#define IMAGE_STOCK_DOWN 	"gtk-go-down"
#define BOX_COMPANIES		"box_companies"

static void _bg_gui_add_synth(gpointer key, gpointer value, gpointer data) {
	bg_synth *synth = (bg_synth*) value;
	bg_gui *gui = (bg_gui*) data;
	g_debug("adding gui for: %s-%s", synth->company->id, synth->id);
	GtkWidget *notebook_synths = g_hash_table_lookup(gui->notebooks_synths, synth->company->id);
	GtkWidget *box = gtk_vbox_new(FALSE, 0);
	GtkWidget *box_label = gtk_hbox_new(FALSE, 0);
	GtkWidget *image = gtk_image_new_from_file(synth->image_filename);
	gtk_box_pack_end(GTK_BOX(box_label), image, FALSE, FALSE, 4);
	GtkWidget *label = gtk_label_new(synth->name);
	gtk_label_set_attributes(GTK_LABEL(label), pango_attr_list_new());
	pango_attr_list_insert(gtk_label_get_attributes(GTK_LABEL(label)), pango_attr_scale_new(2));
	gtk_box_pack_end(GTK_BOX(box_label), label, FALSE, FALSE, 4);
	gtk_box_pack_start(GTK_BOX(box), box_label, FALSE, FALSE, 4);
	GtkWidget *box_params = gtk_hbox_new(FALSE, 0);
	gtk_box_pack_start(GTK_BOX(box), box_params, TRUE, TRUE, 4);
	synth->tab_index =gtk_notebook_append_page(GTK_NOTEBOOK(notebook_synths), box, gtk_label_new(synth->name));

	g_hash_table_insert(gui->notebooks_synths, synth->id, notebook_synths);
	g_hash_table_insert(gui->boxes_params_synths, synth->id, box_params);
}

static void _bg_gui_add_company(gpointer key, gpointer value, gpointer data) {
	bg_company *company = (bg_company*) value;
	bg_gui *gui = (bg_gui*) data;
	g_debug("adding gui for: %s", company->id);
	GtkWidget *box = gtk_vbox_new(FALSE, 0);
	GtkWidget *box_label = gtk_hbox_new(FALSE, 0);
	GtkWidget *label = gtk_label_new(g_strconcat(company->name, " Synthesizers", NULL));
	gtk_label_set_attributes(GTK_LABEL(label), pango_attr_list_new());
	pango_attr_list_insert(gtk_label_get_attributes(GTK_LABEL(label)), pango_attr_scale_new(1.5));
	gtk_box_pack_start(GTK_BOX(box_label), label, FALSE, FALSE, 4);
	gtk_box_pack_start(GTK_BOX(box), box_label, FALSE, FALSE, 4);
	GtkWidget *box_notebook_synths = gtk_hbox_new(FALSE, 0);
	GtkWidget *notebook_synths = gtk_notebook_new();
	gtk_box_pack_start(GTK_BOX(box_notebook_synths), notebook_synths, TRUE, TRUE, 4);
	gtk_box_pack_start(GTK_BOX(box), box_notebook_synths, FALSE, FALSE, 4);
	gtk_notebook_append_page(GTK_NOTEBOOK(gui->notebook_companies), box, gtk_label_new(company->name));

	g_hash_table_insert(gui->notebooks_synths, company->id, notebook_synths);
	g_hash_table_foreach(company->synths, _bg_gui_add_synth, gui);
}

bg_gui* bg_gui_new(GtkBuilder *builder, bg_store *store) {
	gtkc_init(builder);
	bg_gui *gui = g_new(bg_gui, 1);
	gui->window_root = gtkc_get_widget(WINDOW_ROOT);
	gui->box_params = gtkc_get_widget(BOX_GUI);
	gui->notebooks_synths = g_hash_table_new(g_str_hash, g_str_equal);
	gui->boxes_params_synths = g_hash_table_new(g_str_hash, g_str_equal);
	gui->notebook_companies = gtk_notebook_new();
	gtk_notebook_set_tab_pos(GTK_NOTEBOOK(gui->notebook_companies), GTK_POS_LEFT);
	GtkWidget *box_companies = gtkc_get_widget(BOX_COMPANIES);
	gtk_box_pack_start(GTK_BOX(box_companies), gui->notebook_companies, TRUE, TRUE, 4);
	g_hash_table_foreach(store->companies, _bg_gui_add_company, gui);
	return gui;
}

void bg_gui_show(bg_gui *gui) {
	gtk_widget_show_all(gtkc_get_widget("window_root"));
	gtk_main();
}

void bg_gui_switch_audioproperties(bg_gui *gui) {
	gtkc_switch_button_switch("button_switch_audioproperties", "box_audioproperties", IMAGE_STOCK_DOWN, IMAGE_STOCK_UP);
}

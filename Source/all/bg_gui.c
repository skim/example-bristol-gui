#include "bg_gui.h"

static gboolean on_window_close(GtkWidget *window, gpointer data) {
	g_debug("exiting");
	gtk_main_quit();
	return TRUE;
}

static void bg_gui_add_window_root(bg_gui *gui) {
	GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), BG_TITLE);
	GtkWidget *vbox = gtk_vbox_new(FALSE, 0);
	//status bar
	GtkWidget *statusbar = gtk_statusbar_new();
	gtk_statusbar_set_has_resize_grip(GTK_STATUSBAR(statusbar), TRUE);
	gtk_box_pack_end(GTK_BOX(vbox), statusbar, FALSE, FALSE, BG_GUI_PADDING);
	gtk_container_add(GTK_CONTAINER(window), vbox);
	//title
	GtkWidget *box_title = gtk_hbox_new(FALSE, 0);
	GtkWidget *label_title = gtk_label_new(g_strconcat(BG_TITLE, " v", BG_VERSION, NULL));
	gtk_box_pack_end(GTK_BOX(box_title), label_title, FALSE, FALSE, BG_GUI_PADDING);
	gtk_box_pack_start(GTK_BOX(vbox), box_title, FALSE, FALSE, BG_GUI_PADDING);
	//categories notebook
	GtkWidget *box_categories = gtk_hbox_new(FALSE, 0);
	GtkWidget *notebook_categories = gtk_notebook_new();
	gtk_notebook_set_tab_pos(GTK_NOTEBOOK(notebook_categories), GTK_POS_LEFT);
	gtk_box_pack_start(GTK_BOX(box_categories), notebook_categories, TRUE, TRUE, BG_GUI_PADDING);
	gtk_box_pack_start(GTK_BOX(vbox), box_categories, TRUE, TRUE, BG_GUI_PADDING);
	//signals
	g_signal_connect(window, "delete-event", G_CALLBACK(on_window_close), NULL);
	//store
	gui->window_root = window;
	gui->notebook_categories = notebook_categories;
}

void bg_gui_add_category(bg_gui *gui, bg_category *category) {
	GtkWidget *vbox = gtk_vbox_new(FALSE, 0);
	//title
	GtkWidget *box_title = gtk_hbox_new(FALSE, 0);
	GtkWidget *label_title = gtk_label_new(g_strconcat(category->name, " Synthesizers", NULL));
	gtk_label_set_attributes(GTK_LABEL(label_title), pango_attr_list_new());
	pango_attr_list_insert(gtk_label_get_attributes(GTK_LABEL(label_title)), pango_attr_scale_new(1.5));
	gtk_box_pack_start(GTK_BOX(box_title), label_title, FALSE, FALSE, BG_GUI_PADDING);
	gtk_box_pack_start(GTK_BOX(vbox), box_title, FALSE, FALSE, BG_GUI_PADDING);
	//content box
	GtkWidget *box_content = gtk_hbox_new(FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vbox), box_content, TRUE, TRUE, BG_GUI_PADDING);
	//add page
	gtk_notebook_append_page(GTK_NOTEBOOK(gui->notebook_categories), vbox, gtk_label_new(category->name));
	//store
	g_hash_table_insert(gui->boxes_category, category->id, box_content);
	g_debug("added gui for category: %s", category->id);
}

void bg_gui_add_synth(bg_gui *gui, bg_synth *synth) {
	if (g_hash_table_lookup(gui->boxes_category, synth->category->id) == NULL) {
		bg_gui_add_category(gui, synth->category);
		g_debug("was lazy add");
	}
}

bg_gui* bg_gui_new(int *argc, char ***argv) {
	gtk_init(argc, argv);
	bg_gui *gui = g_new(bg_gui, 1);
	gui->boxes_category = g_hash_table_new(g_str_hash, g_str_equal);
	bg_gui_add_window_root(gui);
	return gui;
}

void bg_gui_main(bg_gui *gui) {
	gtk_widget_show_all(gui->window_root);
	gtk_main();
}


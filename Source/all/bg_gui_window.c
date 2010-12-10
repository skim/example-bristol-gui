#include "bg_gui_window.h"
#include "bg_gui_profile.h"
#include "bg_common_gui.h"
#include "bg_common_basic.h"

static gboolean on_window_close(GtkWidget *window, gpointer data) {
	g_debug("leaving mainloop");
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

void bg_gui_add_category(bg_gui *gui, BgCategory *category) {
	g_assert(g_hash_table_lookup(gui->notebooks_synths, category->id) == NULL);
	GtkWidget *vbox = gtk_vbox_new(FALSE, 0);
	//title
	GtkWidget *box_title = gtk_hbox_new(FALSE, 0);
	GtkWidget *label_title = gtk_label_new(g_strconcat(category->name, " Synthesizers", NULL));
	gtkc_label_add_attribute(label_title, pango_attr_scale_new(BG_GUI_SCALE_CATEGORY));
	gtk_box_pack_start(GTK_BOX(box_title), label_title, FALSE, FALSE, BG_GUI_PADDING);
	gtk_box_pack_start(GTK_BOX(vbox), box_title, FALSE, FALSE, BG_GUI_PADDING);
	//synths
	GtkWidget *box_synths = gtk_hbox_new(FALSE, 0);
	GtkWidget *notebook_synths = gtk_notebook_new();
	gtk_notebook_set_tab_pos(GTK_NOTEBOOK(notebook_synths), GTK_POS_TOP);
	gtk_box_pack_start(GTK_BOX(box_synths), notebook_synths, TRUE, TRUE, BG_GUI_PADDING);
	gtk_box_pack_start(GTK_BOX(vbox), box_synths, TRUE, TRUE, BG_GUI_PADDING);
	//add page
	GtkWidget *label_tab = gtk_label_new(category->name);
	gtk_misc_set_alignment(GTK_MISC(label_tab), 0, 0.5);
	gtk_notebook_append_page(GTK_NOTEBOOK(gui->notebook_categories), vbox, label_tab);
	//store
	g_hash_table_insert(gui->notebooks_synths, category->id, notebook_synths);
	g_debug("added gui for category: %s", category->id);
}

void bg_gui_add_synth(bg_gui *gui, BgSynth *synth) {
	if (g_hash_table_lookup(gui->notebooks_synths, synth->category->id) == NULL) {
		bg_gui_add_category(gui, synth->category);
	}
	GtkWidget *notebook_synths = GTK_WIDGET(g_hash_table_lookup(gui->notebooks_synths, synth->category->id));
	GtkWidget *vbox = gtk_vbox_new(FALSE, 0);
	//title
	GtkWidget *box_title = gtk_hbox_new(FALSE, 0);
	if (synth->image_filename != NULL) {
		GtkWidget *image_title = gtk_image_new_from_file(bg_path_new(synth->image_filename));
		gtk_box_pack_end(GTK_BOX(box_title), image_title, FALSE, FALSE, BG_GUI_PADDING);
	}
	GtkWidget *label_title = gtk_label_new(synth->name);
	gtkc_label_add_attribute(label_title, pango_attr_scale_new(BG_GUI_SCALE_SYNTH));
	gtk_box_pack_end(GTK_BOX(box_title), label_title, FALSE, FALSE, BG_GUI_PADDING);
	gtk_box_pack_start(GTK_BOX(vbox), box_title, FALSE, FALSE, BG_GUI_PADDING);
	//tab
	GtkWidget *box_tab = gtk_hbox_new(FALSE, 4);
	//resized image for the tab label
	if (synth->image_filename != NULL && BG_GUI_SHOW_TAB_IMAGES) {
		GtkWidget *image_tab = gtkc_image_new_from_file_scaled(bg_path_new(synth->image_filename), BG_GUI_SCALE_TAB_IMAGES);
		gtk_box_pack_start(GTK_BOX(box_tab), image_tab, FALSE, FALSE, 0);
	}
	GtkWidget *label_tab = gtk_label_new(synth->name);
	gtk_box_pack_start(GTK_BOX(box_tab), label_tab, FALSE, FALSE, 0);
	gtk_widget_show_all(box_tab);
	//profiles panel
	GtkWidget *box_profiles = bg_gui_profiles_box_new(gui->store, gui->window_root);
	//switch profiles panel
	GtkWidget *switchbox_profiles = gtkc_switch_hbox_new("Profiles", BG_GUI_STOCK_SHOW, BG_GUI_STOCK_HIDE, box_profiles);
	gtk_box_pack_start(GTK_BOX(vbox), switchbox_profiles, FALSE, FALSE, BG_GUI_PADDING);
	gtk_box_pack_start(GTK_BOX(vbox), box_profiles, FALSE, FALSE, BG_GUI_PADDING);
	//audio panel
	GtkWidget *box_audio = gtk_hbox_new(FALSE, 0);
	gtk_box_pack_start(GTK_BOX(box_audio), gtk_label_new("TBD"), FALSE, FALSE, BG_GUI_PADDING);
	//switch audio panel
	GtkWidget *switchbox_audio = gtkc_switch_hbox_new("Audio Parameters", BG_GUI_STOCK_SHOW, BG_GUI_STOCK_HIDE, box_audio);
	gtk_box_pack_start(GTK_BOX(vbox), switchbox_audio, FALSE, FALSE, BG_GUI_PADDING);
	gtk_box_pack_start(GTK_BOX(vbox), box_audio, FALSE, FALSE, BG_GUI_PADDING);
	//add page
	gtk_notebook_append_page(GTK_NOTEBOOK(notebook_synths), vbox, box_tab);
	g_debug("added gui for synth: %s", synth->id);
}

static void bg_gui_synth_fill(gpointer object, gpointer data) {
	BgSynth *synth = (BgSynth*) object;
	bg_gui *gui = (bg_gui*) data;
	bg_gui_add_synth(gui, synth);
}

bg_gui* bg_gui_new(int *argc, char ***argv, BgStore *store) {
	gtk_init(argc, argv);
	bg_gui *gui = g_new(bg_gui, 1);
	gui->store = store;
	gui->notebooks_synths = g_hash_table_new(g_str_hash, g_str_equal);
	bg_gui_add_window_root(gui);
	g_debug("data path: %s", BG_PATH_DATA);
	g_list_foreach(store->synths, bg_gui_synth_fill, gui);
	return gui;
}

void bg_gui_main(bg_gui *gui) {
	gtk_widget_show_all(gui->window_root);
	g_debug("entering mainloop");
	gtk_main();
}


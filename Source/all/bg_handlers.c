#include "bg_handlers.h"
#include "bg_gui.h"
#include <stdio.h>

static bg_gui *gui;

void bg_handlers_init(bg_gui *_gui) {
	gui = _gui;
}

void on_window_root_destroy(GtkObject *object) {
	printf("exiting");
	gtk_main_quit();
}

void on_entry_identifier_mini_changed(GtkEditable *editable, gpointer data) {

}

void on_button_switch_audioproperties_clicked(GtkButton *button, gpointer data) {
	bg_gui_switch_audioproperties(gui);
}



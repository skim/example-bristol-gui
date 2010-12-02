#include "handlers.h"
#include "gtk_common.h"
#include "gui.h"
#include <stdio.h>

#define IMAGE_STOCK_UP 		"gtk-go-up"
#define IMAGE_STOCK_DOWN 	"gtk-go-down"

void on_window_root_destroy(GtkObject *object) {
	printf("exiting");
	gtk_main_quit();
}

void on_button_show_audioproperties_mini_clicked(GtkButton *button, gpointer data) {
	gtk_switch_button_switch(button, "box_audioproperties_mini", IMAGE_STOCK_DOWN, IMAGE_STOCK_UP);
}

void on_button_show_synthproperties_mini_clicked(GtkButton *button, gpointer data) {
	gtk_switch_button_switch(button, "box_synthproperties_mini", IMAGE_STOCK_DOWN, IMAGE_STOCK_UP);
}

void on_button_help_mini_clicked(GtkButton *button, gpointer data) {
	bg_show_help("text_help_mini");
}

void on_button_start_mini_clicked(GtkButton *button, gpointer data) {
	bg_start_synth("mini");
}

void on_button_stop_mini_clicked(GtkButton *button, gpointer data) {
}



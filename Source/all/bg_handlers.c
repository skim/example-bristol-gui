#include "bg_handlers.h"
#include "bg_gui.h"
#include "gtkc_all.h"
#include <stdio.h>

#define IMAGE_STOCK_UP 		"gtk-go-up"
#define IMAGE_STOCK_DOWN 	"gtk-go-down"

void on_window_root_destroy(GtkObject *object) {
	printf("exiting");
	gtk_main_quit();
}

void on_button_switch_configuration_mini_clicked(GtkButton *button, gpointer data) {
	gtkc_switch_button_switch(button, "box_configuration_mini", IMAGE_STOCK_DOWN, IMAGE_STOCK_UP);
}

void on_button_show_audioproperties_mini_clicked(GtkButton *button, gpointer data) {
	gtkc_switch_button_switch(button, "box_audioproperties_mini", IMAGE_STOCK_DOWN, IMAGE_STOCK_UP);
}

void on_button_show_synthproperties_mini_clicked(GtkButton *button, gpointer data) {
	gtkc_switch_button_switch(button, "box_synthproperties_mini", IMAGE_STOCK_DOWN, IMAGE_STOCK_UP);
}

void on_button_start_mini_clicked(GtkButton *button, gpointer data) {
	bg_synth_start("mini");
}



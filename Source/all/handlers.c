#include "handlers.h"
#include "common_gui.h"
#include <stdio.h>

#define IMAGE_STOCK_UP 		"gtk-go-up"
#define IMAGE_STOCK_DOWN 	"gtk-go-down"

static GtkBuilder *gbuilder = NULL;

void init_handlers(GtkBuilder *builder) {
	gbuilder = builder;
}

void on_window_root_destroy(GtkObject *object) {
	printf("exiting");
	gtk_main_quit();
}

void on_button_show_audioproperties_mini_clicked(GtkButton *button, gpointer data) {
	gtk_switchbutton_switch(gbuilder, button, "box_audioproperties_mini", IMAGE_STOCK_DOWN, IMAGE_STOCK_UP);
}

void on_button_show_synthproperties_mini_clicked(GtkButton *button, gpointer data) {
	gtk_switchbutton_switch(gbuilder, button, "box_synthproperties_mini", IMAGE_STOCK_DOWN, IMAGE_STOCK_UP);
}


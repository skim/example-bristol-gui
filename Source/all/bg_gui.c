#include "bg_gui.h"

GtkWidget* bg_window_new() {
	GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), BG_WINDOW_ROOT_TITLE);
	return window;
}

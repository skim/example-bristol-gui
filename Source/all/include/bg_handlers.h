#ifndef HANDLERS_H_
#define HANDLERS_H_

#include "bg_gui.h"
#include <gtk/gtk.h>

void bg_handlers_init(bg_gui *gui);
void on_window_root_destroy(GtkObject *object);
void on_button_switch_audioproperties_clicked(GtkButton *button, gpointer data);

#endif /* HANDLERS_H_ */

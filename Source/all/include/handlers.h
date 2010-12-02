#ifndef HANDLERS_H_
#define HANDLERS_H_

#include <gtk/gtk.h>

void init_handlers(GtkBuilder *builder);
void on_window_root_destroy(GtkObject *object);
void on_button_show_audioproperties_mini_clicked(GtkButton *button, gpointer data);

#endif /* HANDLERS_H_ */

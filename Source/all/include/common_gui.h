#ifndef COMMON_GUI_H_
#define COMMON_GUI_H_

#include <gtk/gtk.h>

void gtk_switchbutton_switch(GtkBuilder *builder, GtkButton *button, const char *container_name, const char *image_stock_show, const char *image_stock_hide);

#endif /* COMMON_GUI_H_ */

#ifndef BG_GUI_PROFILE_H_
#define BG_GUI_PROFILE_H_

#include "bg_common_basic.h"
#include "bg_data.h"
#include <gtk/gtk.h>

GtkWidget* bg_gui_profiles_box_new(BgStore *store, GtkWidget *window_root);

#endif /* BG_GUI_PROFILE_H_ */

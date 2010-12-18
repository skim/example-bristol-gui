#ifndef BG_GUI_H_
#define BG_GUI_H_

#include <gtk/gtk.h>
#include "bg_data.h"

void bg_combo_prepare(GtkComboBox *combo);
void bg_combo_set_profiles(GtkComboBox *combo, GtkLabel *label, BgData *data);

#endif /* BG_GUI_H_ */

#ifndef LTK_COMMON_H_
#define LTK_COMMON_H_

#include <gtk/gtk.h>
#include "llib.h"

void 		ltk_button_set_stock_image	(GtkButton *button, const char *stock_name, GtkIconSize size);
void		ltk_combo_box_fill			(GtkComboBox *combo_box, LValueList *values);

#endif /* LTK_COMMON_H_ */

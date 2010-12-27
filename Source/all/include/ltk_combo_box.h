#ifndef LTK_COMBO_BOX_H_
#define LTK_COMBO_BOX_H_

#include <gtk/gtk.h>
#include "llib.h"

void		ltk_combo_box_fill							(GtkComboBox *combo_box, LValueList *values);
void		ltk_combo_box_set_active_value				(GtkComboBox *combo_box, LValue *value);
LValue*		ltk_combo_box_get_active_value				(GtkComboBox *combo_box);
void		ltk_combo_box_set_active_value_from_option	(GtkComboBox *combo_box, LOptionList *options, const char *id);
void 		ltk_combo_box_connect_option				(GtkComboBox *combo_box, LOptionList *options, const char *id);


#endif /* LTK_COMBO_BOX_H_ */

#ifndef LTK_COMMON_H_
#define LTK_COMMON_H_

#include <gtk/gtk.h>
#include "llib.h"

#define	LTK_OBJECT_MARK_KEY	"LTK_OBJECT"

void 		ltk_button_set_stock_image					(GtkButton *button, const char *stock_name, GtkIconSize size);
void		ltk_combo_box_fill							(GtkComboBox *combo_box, LValueList *values);
void		ltk_combo_box_set_active_value				(GtkComboBox *combo_box, LValue *value);
LValue*		ltk_combo_box_get_active_value				(GtkComboBox *combo_box);
void		ltk_combo_box_set_active_value_from_option	(GtkComboBox *combo_box, LOptionList *options, const char *id);
void 		ltk_combo_box_connect_option				(GtkComboBox *combo_box, LOptionList *options, const char *id);
void		ltk_toggle_button_set_active_from_option	(GtkToggleButton *toggle, LOptionList *options, const char *id);
void		ltk_toggle_button_connect_option			(GtkToggleButton *toggle, LOptionList *options, const char *id);

#endif /* LTK_COMMON_H_ */

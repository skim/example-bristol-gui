#ifndef LTK_COMMON_H_
#define LTK_COMMON_H_

#include <gtk/gtk.h>
#include "llib.h"

#define	LTK_OBJECT_MARK_KEY			"LTK_OBJECT"
#define LTK_OBJECT_MARK_ONETIME_KEY	"LTK_OBJECT_ONETIME"

typedef struct {
	LOptionList *options;
	char *id;
} LtkPayload ;

LtkPayload* ltk_payload_new								(LOptionList *options, const char *id);
void 		ltk_object_mark								(GtkObject *object);
gboolean 	ltk_object_is_marked						(GtkObject *object);
void 		ltk_object_mark_onetime						(GtkObject *object);
gboolean	ltk_object_check_marked_onetime				(GtkObject *object);
void 		ltk_button_set_stock_image					(GtkButton *button, const char *stock_name, GtkIconSize size);
void		ltk_toggle_button_set_active_from_option	(GtkToggleButton *toggle, LOptionList *options, const char *id);
void		ltk_toggle_button_connect_to_option			(GtkToggleButton *toggle, LOptionList *options, const char *id);
void		ltk_adjustment_connect_to_option			(GtkAdjustment *adjustment, LOptionList *options, const char *id);

#endif /* LTK_COMMON_H_ */

#ifndef BG_GUI_H_
#define BG_GUI_H_

#include <gtk/gtk.h>
#include "bg_session.h"

typedef struct {
	GtkBuilder *builder;
	char *id;
} BgGuiPayload;

char*			bg_gui_name(const char *id, const char *widget);
GType			bg_gui_get_type(const char *widget_string);
BgGuiPayload*	bg_gui_payload_new(GtkBuilder *builder, const char *id);
void 			bg_adjustment_set_value(GtkBuilder *builder, const char *id, double value);
void 			bg_switch_check_button_init(GtkBuilder *builder, const char *id, gboolean active);
void 			bg_combo_box_init(GtkBuilder *builder, const char *id, BgEntryList *entries, int selected);
const char* 	bg_combo_box_get_active_value(GtkBuilder *builder, const char *id);
void 			bg_combo_box_set_active_value(GtkBuilder *builder, const char *id, const char *value);
void 			bg_switch_button_init(GtkBuilder *builder, const char *id);

#endif /* BG_GUI_H_ */

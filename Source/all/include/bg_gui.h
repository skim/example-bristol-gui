#ifndef BG_GUI_H_
#define BG_GUI_H_

#include <gtk/gtk.h>
#include "bg_session.h"

typedef struct {
	GtkBuilder *builder;
	char *id;
} BgGuiPayload;

char*			bg_gui_name(const char *id, const char *widget);
BgGuiPayload*	bg_gui_payload_new(GtkBuilder *builder, const char *id);
void 			bg_gui_adjust_set_value(GtkBuilder *builder, const char *id, double value);
void 			bg_gui_checkbox_prepare(GtkBuilder *builder, const char *id, gboolean active);
void 			bg_gui_combobox_prepare(GtkBuilder *builder, const char *id, BgEntryList *entries, int selected);
const char* 	bg_gui_combobox_get_active_value(GtkBuilder *builder, const char *id);
void 			bg_gui_combobox_set_active_value(GtkBuilder *builder, const char *id, const char *value);
void 			bg_gui_switch_prepare(GtkBuilder *builder, const char *id);

#endif /* BG_GUI_H_ */

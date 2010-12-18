#ifndef BG_GUI_H_
#define BG_GUI_H_

#include <gtk/gtk.h>

typedef struct {
	GtkBuilder *builder;
	char *id;
} BgGuiPayload;

char*			bg_gui_name_new(const char *id, const char *widget);
BgGuiPayload*	bg_gui_payload_new(GtkBuilder *builder, const char *id);
void 			bg_gui_prepare_check(GtkBuilder *builder, const char *id, gboolean active);
void 			bg_gui_prepare_combo(GtkBuilder *builder, const char *id);
void 			bg_gui_prepare_adjust(GtkBuilder *builder, const char *id, double value);
void 			bg_gui_prepare_switch(GtkBuilder *builder, const char *id);

#endif /* BG_GUI_H_ */
